/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/
/*************************************************************************/
/*                       This file is part of:                           */
/*                           CARBON LANGUAGE                             */
/*https://github.com/ThakeeNathees/carbon/blob/master/src/main/crash_handler.h*/
/*************************************************************************/
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

// This file is heavily modified version of the Godot's crahs_handler
// It's also heavily modified modified from:
// Usage:
//   #define SNOWBALL_INCLUDE_CRASH_HANDLER_MAIN
//   #define SNOWBALL_CRASH_HANDLER_IMPLEMENTATION
//   #include "crash_handler.h"

#if defined(_WIN32)

#include <Windows.h>
// #pragma comment(lib, "psapi.lib")
// #pragma comment(lib, "dbghelp.lib")

// Crash handler exception only enabled with MSVC
#if (defined(_DEBUG) || defined(_SN_DEBUG)) && defined(_MSC_VER)
#define CRASH_HANDLER_EXCEPTION 1
extern DWORD CrashHandlerException(EXCEPTION_POINTERS *ep);
#endif

#elif defined(linux)

#ifndef CRASH_HANDLER_X11_H
#define CRASH_HANDLER_X11_H

// LINK: 'dl'

class CrashHandler {

    bool disabled;

  public:
    void initialize();

    void disable();
    bool is_disabled() const { return disabled; };

    CrashHandler();
    ~CrashHandler();
};

#endif // CRASH_HANDLER_X11_H

#endif

#ifdef SNOWBALL_INCLUDE_CRASH_HANDLER_MAIN

/***************************************************************************************************************************/
/*                                                CRASH HANDLER MAIN */
/***************************************************************************************************************************/

int _main(int, char **);

#if defined(_WIN32)

int main(int argc, char **argv) {
#ifdef CRASH_HANDLER_EXCEPTION
    __try {
        return _main(argc, argv);
    } __except (CrashHandlerException(GetExceptionInformation())) {
        return 1;
    }
#else
    return _main(argc, argv);
#endif
}

#elif defined(linux)

int main(int argc, char **argv) {
    CrashHandler crash_handler;
    crash_handler.initialize();
    _main(argc, argv);

    return 0;
}

#else
#define _main main

#endif

#endif // SNOWBALL_INCLUDE_CRASH_HANDLER_MAIN

#if defined(SNOWBALL_CRASH_HANDLER_IMPLEMENTATION) ||                          \
    (defined(SNOWBALL_INCLUDE_CRASH_HANDLER_MAIN) &&                           \
     defined(SNOWBALL_IMPLEMENTATION))
/***************************************************************************************************************************/
/*                                                CRASH HANDLER WINDOWS */
/***************************************************************************************************************************/

#if defined(_WIN32)

#ifdef CRASH_HANDLER_EXCEPTION

#include <windows.h>

// Backtrace code code based on:
// https://stackoverflow.com/questions/6205981/windows-c-stack-trace-from-a-running-app

#include <algorithm>
#include <iterator>
#include <psapi.h>
#include <vector>

// Some versions of imagehlp.dll lack the proper packing directives themselves
// so we need to do it.
#pragma pack(push, before_imagehlp, 8)
#include <imagehlp.h>
#pragma pack(pop, before_imagehlp)

struct module_data {
    std::string image_name;
    std::string module_name;
    void *base_address;
    DWORD load_size;
};

class symbol {
    typedef IMAGEHLP_SYMBOL64 sym_type;
    sym_type *sym;
    static const int max_name_len = 1024;

  public:
    symbol(HANDLE process, DWORD64 address)
        : sym((sym_type *)::operator new(sizeof(*sym) + max_name_len)) {
        memset(sym, '\0', sizeof(*sym) + max_name_len);
        sym->SizeOfStruct  = sizeof(*sym);
        sym->MaxNameLength = max_name_len;
        DWORD64 displacement;

        SymGetSymFromAddr64(process, address, &displacement, sym);
    }

    std::string name() { return std::string(sym->Name); }
    std::string undecorated_name() {
        if (*sym->Name == '\0') return "<couldn't map PC to fn name>";
        std::vector<char> und_name(max_name_len);
        UnDecorateSymbolName(sym->Name, &und_name[0], max_name_len,
                             UNDNAME_COMPLETE);
        return std::string(&und_name[0], strlen(&und_name[0]));
    }
};

class get_mod_info {
    HANDLE process;

  public:
    get_mod_info(HANDLE h) : process(h) {}

    module_data operator()(HMODULE module) {
        module_data ret;
        char temp[4096];
        MODULEINFO mi;

        GetModuleInformation(process, module, &mi, sizeof(mi));
        ret.base_address = mi.lpBaseOfDll;
        ret.load_size    = mi.SizeOfImage;

        GetModuleFileNameEx(process, module, temp, sizeof(temp));
        ret.image_name = temp;
        GetModuleBaseName(process, module, temp, sizeof(temp));
        ret.module_name = temp;
        std::vector<char> img(ret.image_name.begin(), ret.image_name.end());
        std::vector<char> mod(ret.module_name.begin(), ret.module_name.end());
        SymLoadModule64(process, 0, &img[0], &mod[0], (DWORD64)ret.base_address,
                        ret.load_size);
        return ret;
    }
};

DWORD CrashHandlerException(EXCEPTION_POINTERS *ep) {
    HANDLE process           = GetCurrentProcess();
    HANDLE hThread           = GetCurrentThread();
    DWORD offset_from_symbol = 0;
    IMAGEHLP_LINE64 line     = {0};
    std::vector<module_data> modules;
    DWORD cbNeeded;
    std::vector<HMODULE> module_handles(1);

    if (IsDebuggerPresent()) {
        return EXCEPTION_CONTINUE_SEARCH;
    }

    fprintf(stderr, "%s: Program crashed\n", __FUNCTION__);

    // Load the symbols:
    if (!SymInitialize(process, nullptr, false))
        return EXCEPTION_CONTINUE_SEARCH;

    SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
    EnumProcessModules(process, &module_handles[0],
                       (DWORD)module_handles.size() * sizeof(HMODULE),
                       &cbNeeded);
    module_handles.resize(cbNeeded / sizeof(HMODULE));
    EnumProcessModules(process, &module_handles[0],
                       (DWORD)module_handles.size() * sizeof(HMODULE),
                       &cbNeeded);
    std::transform(module_handles.begin(), module_handles.end(),
                   std::back_inserter(modules), get_mod_info(process));
    void *base = modules[0].base_address;

    // Setup stuff:
    CONTEXT *context = ep->ContextRecord;
    STACKFRAME64 frame;
    bool skip_first = false;

    frame.AddrPC.Mode    = AddrModeFlat;
    frame.AddrStack.Mode = AddrModeFlat;
    frame.AddrFrame.Mode = AddrModeFlat;

#ifdef _M_X64
    frame.AddrPC.Offset    = context->Rip;
    frame.AddrStack.Offset = context->Rsp;
    frame.AddrFrame.Offset = context->Rbp;
#else
    frame.AddrPC.Offset    = context->Eip;
    frame.AddrStack.Offset = context->Esp;
    frame.AddrFrame.Offset = context->Ebp;

    // Skip the first one to avoid a duplicate on 32-bit mode
    skip_first = true;
#endif

    line.SizeOfStruct   = sizeof(line);
    IMAGE_NT_HEADERS *h = ImageNtHeader(base);
    DWORD image_type    = h->FileHeader.Machine;

    fprintf(stderr, "Dumping the backtrace.\n");

    int n = 0;
    do {
        if (skip_first) {
            skip_first = false;
        } else {
            if (frame.AddrPC.Offset != 0) {
                std::string fnName =
                    symbol(process, frame.AddrPC.Offset).undecorated_name();

                if (SymGetLineFromAddr64(process, frame.AddrPC.Offset,
                                         &offset_from_symbol, &line))
                    fprintf(stderr, "[%d] %s (%s:%d)\n", n, fnName.c_str(),
                            line.FileName, line.LineNumber);
                else
                    fprintf(stderr, "[%d] %s\n", n, fnName.c_str());
            } else
                fprintf(stderr, "[%d] ???\n", n);

            n++;
        }

        if (!StackWalk64(image_type, process, hThread, &frame, context, nullptr,
                         SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
            break;
    } while (frame.AddrReturn.Offset != 0 && n < 256);

    fprintf(stderr, "-- END OF BACKTRACE --\n");

    SymCleanup(process);

    // Pass the exception to the OS
    return EXCEPTION_CONTINUE_SEARCH;
}
#endif

/***************************************************************************************************************************/
/*                                                CRASH HANDLER LINUX */
/***************************************************************************************************************************/

#elif defined(linux)

#if _SN_DEBUG
#include <cxxabi.h>
#include <dlfcn.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

// TODO: move this to os related place
std::string _get_exec_path() {
    int len = 1024;
    char pBuf[len];
#ifdef _WIN32
    int bytes = GetModuleFileName(NULL, pBuf, sizeof pBuf);
    // TODO:  assert bytes > 0
#elif __linux__
    char szTmp[32];
    sprintf(szTmp, "/proc/%d/exe", getpid());

    // int bytes = min(readlink(szTmp, pBuf, len), len - 1);
    int bytes = readlink(szTmp, pBuf, len);
    if (bytes > len - 1) bytes = len - 1;

    if (bytes >= 0) pBuf[bytes] = '\0';
#endif
    return pBuf;
}

int _execute(const std::string& p_path,
             const std::vector<std::string>& p_arguments, bool p_blocking,
             int *r_child_id, std::string *r_pipe, int *r_exitcode,
             bool read_stderr = true /*,Mutex *p_pipe_mutex*/) {

#ifdef __EMSCRIPTEN__
    // Don't compile this code at all to avoid undefined references.
    // Actual virtual call goes to OS_JavaScript.
    ERR_FAIL_V(ERR_BUG);
#else
    if (p_blocking && r_pipe) {

        std::string argss;
        argss = "\"" + p_path + "\"";

        for (int i = 0; i < p_arguments.size(); i++) {

            argss += std::string(" \"") + p_arguments[i] + "\"";
        }

        if (read_stderr) {
            argss += " 2>&1";        // Read stderr too
        } else {
            argss += " 2>/dev/null"; // silence stderr
        }
        FILE *f = popen(argss.c_str(), "r");

        if (!f) {
            printf("ERR_CANT_OPEN, Cannot pipe stream from process running "
                   "with following arguments\n\t%s.\n",
                   argss.c_str());
            return -1;
        }

        char buf[65535];

        while (fgets(buf, 65535, f)) {
            (*r_pipe) += std::string(buf);
        }
        int rv = pclose(f);
        if (r_exitcode) *r_exitcode = rv;

        return 0;
    }

    pid_t pid = fork();
    if (pid < 0) {
        printf("ERR_CANT_FORK\n");
        return -1;
    }

    if (pid == 0) {
        // is child

        if (!p_blocking) {
            // For non blocking calls, create a new session-ID so parent won't
            // wait for it. This ensures the process won't go zombie at end.
            setsid();
        }

        std::vector<std::string> cs;

        cs.push_back(p_path);
        for (int i = 0; i < p_arguments.size(); i++)
            cs.push_back(p_arguments[i]);

        std::vector<char *> args;
        for (int i = 0; i < cs.size(); i++)
            args.push_back((char *)cs[i].c_str());
        args.push_back(0);

        execvp(p_path.c_str(), &args[0]);
        // still alive? something failed..
        fprintf(stderr,
                "**ERROR** OS_Unix::execute - Could not create child process "
                "while executing: %s\n",
                p_path.c_str());
        abort();
    }

    if (p_blocking) {

        int status;
        waitpid(pid, &status, 0);
        if (r_exitcode) *r_exitcode = status;

    } else {

        if (r_child_id) *r_child_id = pid;
    }

    return 0;
#endif
}

// FIXME: chage it to string split
std::string _func_offset(const char *string_symbol) {

    // the backtrace_symbol output:
    // /home/thakeenathees/dev/SNOWBALL/bin/SNOWBALL.x11.debug.64(+0x2801)
    // [0x55c5aa0a2801] from that it'll extract the offset (0x2801) and feed to
    // addr2line

    size_t i  = 0;
    bool copy = false;
    std::string offset;
    while (char c = string_symbol[i++]) {
        if (c == ')') break;
        if (copy) offset += c;
        if (c == '+') copy = true;
    }
    return offset;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////

static void handle_crash(int sig) {

    void *bt_buffer[256];
    size_t size           = backtrace(bt_buffer, 256);
    std::string _execpath = _get_exec_path();

    // Dump the backtrace to stderr with a message to the user
    fprintf(stderr, "%s: Snowball crashed!\n", __FUNCTION__);
    fprintf(
        stderr,
        "%s: Oh no! Fluffy got into the code and caused an error! /ᐠ.ᆽ.ᐟ \\∫\n",
        __FUNCTION__);
    fprintf(stderr, "%s: Program crashed with signal %d\n", __FUNCTION__, sig);

    fprintf(stderr, "Dumping the backtrace.\n");
    char **strings = backtrace_symbols(bt_buffer, size);
    if (strings) {
        for (size_t i = 1; i < size; i++) {

            /* fname not working like it works in godot!! using backtrace_symbol
               string instead to get method char fname[1024]; Dl_info info;
                        snprintf(fname, 1024, "%s", strings[i]);
                        // Try to demangle the function name to provide a more
               readable one if (dladdr(bt_buffer[i], &info) && info.dli_sname) {
                            if (info.dli_sname[0] == '_') {
                                int status;
                                char *demangled =
               abi::__cxa_demangle(info.dli_sname, nullptr, nullptr, &status);
                                if (status == 0 && demangled) {
                                    snprintf(fname, 1024, "%s", demangled);
                                }
                                if (demangled)
                                    free(demangled);
                            }
                        }
            */
            std::vector<std::string> args;

            // char str[1024];
            // snprintf(str, 1024, "%p", bt_buffer[i]);
            //  godot using this but It's not working for some reason
            //  but the offset from the backtrace_symbols working, why?
            //  using args.push_back(_func_offset(strings[i])); instead

            args.push_back(_func_offset(strings[i]));
            args.push_back("-e");
            args.push_back(_execpath);
            args.push_back("-f");
            args.push_back("--demangle");
            args.push_back("-p");

            std::string output = "";

            // Try to get the file/line number using addr2line
            int ret;
            int err = _execute("addr2line", args, true, nullptr, &output, &ret);
            if (err == 0) {
                output.erase(output.length() - 1, 1);
            }

            if (output.find(" ??:") !=
                std::string::npos) { // _start at ??:0 no symbol found
                fprintf(stderr, "[%ld] <<unresolved symbols>> at %s\n",
                        (long int)i, /*fname,*/ strings[i]);
            } else {
                fprintf(stderr, "[%ld] %s\n", (long int)i,
                        /*fname,*/ output.c_str());
            }
        }

        free(strings);
    }
    fprintf(stderr, "-- END OF BACKTRACE --\n");

    // Abort to pass the error to the OS
    abort();
}
#endif

CrashHandler::CrashHandler() { disabled = false; }

CrashHandler::~CrashHandler() { disable(); }

void CrashHandler::disable() {
    if (disabled) return;

#if _SN_DEBUG
    signal(SIGSEGV, nullptr);
    signal(SIGFPE, nullptr);
    signal(SIGILL, nullptr);
#endif

    disabled = true;
}

void CrashHandler::initialize() {
#if _SN_DEBUG
    signal(SIGSEGV, handle_crash);
    signal(SIGFPE, handle_crash);
    signal(SIGILL, handle_crash);
#endif
}

#endif
#endif // SNOWBALL_CRASH_HANDLER_IMPLEMENTATION
