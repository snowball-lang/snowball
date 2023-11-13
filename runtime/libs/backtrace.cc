
#include "backtrace.h"
#include "runtime.h"

namespace snowball {

static struct backtrace_state *state = nullptr;
static std::mutex stateLock;

void backtrace_callback(void *data, const char *msg, int errnum) {
  printf("[snowball internal error]: backtrace error: %s (%d)\n", msg, errnum);
  abort();
}

int backtrace_full_callback(void *data, uintptr_t pc, const char *filename,
                                int lineno, const char *function) {
  auto *bt = ((Backtrace *)data);
  bt->push(BacktraceFrame {function, filename, pc, lineno});
  return (bt->frame_count < SNOWBALL_BACKTRACE_LIMIT) ? 0 : 1;
}

void Backtrace::push(BacktraceFrame frame) {
    if (frame_count >= SNOWBALL_BACKTRACE_LIMIT) {
        return;
    }

    if (frame_count == 0) {
        frames = (BacktraceFrame*) malloc(sizeof(BacktraceFrame) * SNOWBALL_BACKTRACE_LIMIT);
    } 

    frames[frame_count++] = frame;
}

void Backtrace::push(uintptr_t address) {
    frames[frame_count++] = (BacktraceFrame) {
        .function = "????",
        .filename = "<invalid>",
        .address = address,
        .lineno = 0
    };
}

void Backtrace::pls_free() {
    free((void*)frames);
}

void print_backtrace(Backtrace backtrace, std::ostringstream &oss) {
  if (!(snowball::snowball_flags & SNOWBALL_FLAG_DEBUG)) 
    return;

    if (getenv("SN_BACKTRACE") == NULL) {
        oss << "\n\e[1;37mnote:\e[0m run with \e[1;37m`SN_BACKTRACE=1`\e[0m environment variable to get a backtrace";
        return;
    }

    oss << "\n";
    oss << "\n\033[1mBacktrace (most recent call first):\033[0m\n";

    if (backtrace.frame_count <= 1) {
        oss << "  (no backtrace available)\n";
        return;
    }
    
    for (int i = 1; i < backtrace.frame_count; i++) {
        BacktraceFrame frame = backtrace.frames[i];
        if (!frame.function || !frame.filename) {
            oss << "  (#" << i << "): \e[1;30m[" << (void*)frame.address << "]\e[0m - ????\n";
            continue;
        }
        // TODO: demangle function names
        oss << "  (#" << i << "): \e[1;30m[" << (void*)frame.address << "]\e[0m - " << frame.function << "\n";
        oss << "\t\tat \e[1;32m" << frame.filename << "\e[1;36m:" << frame.lineno << "\e[0m\n";
    }

    oss << "\e[0m\n";
    //backtrace.pls_free();
}

void get_backtrace(Backtrace &backtrace) {
  if (!(snowball::snowball_flags & SNOWBALL_FLAG_DEBUG))
    return;

  if (!snowball::state) {
    snowball::stateLock.lock();
    if (!snowball::state)
      snowball::state =
          backtrace_create_state(/*filename=*/nullptr, /*threaded=*/1,
                                  snowball::backtrace_callback, /*data=*/nullptr);
    snowball::stateLock.unlock();
  }
  backtrace_full(snowball::state, /*skip=*/1, snowball::backtrace_full_callback,
                  snowball::backtrace_callback, &backtrace);
}

}