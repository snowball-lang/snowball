
#ifndef LIBC_VERSION
#error "LIBC_VERSION not defined! (e.g. \"8\")"
#endif

#ifdef defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // TODO: test this
#define LD_ARGS()                                                              \
    {                                                                          \
        LD_PATH,                                                               \
            "-dynamic-linker"                                                  \
            "-L" STATICLIB_DIR,                                                \
            LLVM_LDFLAGS, "-L" STATICLIB_DIR "" _SNOWBALL_LIBRARY_DIR,         \
            p_input, "-lSnowballRuntime", "-lc", "-lm"                \
    }
#elif __APPLE__
#define LD_ARGS()                                                              \
    {                                                                          \
        LD_PATH, "-execute", \
            "-L/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/",               \
            "-L/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/",               \
            "-L" STATICLIB_DIR, LLVM_LDFLAGS,                                  \
            "-L" STATICLIB_DIR PATH_SEPARATOR _SNOWBALL_LIBRARY_DIR, p_input,              \
            "-lSnowballRuntime", "-lc",  "-lm"                         \
    }
#elif __linux__
#define LD_ARGS()                                                              \
    {                                                                          \
        LD_PATH, "-dynamic-linker", \
            "-L/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/",               \
            "-L/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/",               \
            "-L" STATICLIB_DIR, LLVM_LDFLAGS,                                  \
            "-L" STATICLIB_DIR PATH_SEPARATOR _SNOWBALL_LIBRARY_DIR, p_input,              \
            "-lSnowballRuntime", "-lc", "-lm"                         \
    }
#else
#error "Unknown compiler"
#endif