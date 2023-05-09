
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
            p_input, "-lSnowballRuntime", "-lc", "-lgcc", "-lm"                \
    }
#elif __APPLE__
#define LD_ARGS()                                                              \
    {                                                                          \
        LD_PATH, "-execute", "/lib64/ld-linux-x86-64.so.2",             \
            "/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/crtbegin.o",       \
            "/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/crtend.o",         \
            "/usr/lib/x86_64-linux-gnu/crt1.o",                                \
            "/usr/lib/x86_64-linux-gnu/crti.o",                                \
            "/usr/lib/x86_64-linux-gnu/crtn.o",                                \
            "-L/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/",               \
            "-L/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/",               \
            "-L" STATICLIB_DIR, LLVM_LDFLAGS,                                  \
            "-L" STATICLIB_DIR PATH_SEPARATOR _SNOWBALL_LIBRARY_DIR, p_input,              \
            "-lSnowballRuntime", "-lc", "-lgcc", "-lm"                         \
    }
#elif __linux__
#define LD_ARGS()                                                              \
    {                                                                          \
        LD_PATH, "-dynamic-linker", "/lib64/ld-linux-x86-64.so.2",             \
            "/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/crtbegin.o",       \
            "/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/crtend.o",         \
            "/usr/lib/x86_64-linux-gnu/crt1.o",                                \
            "/usr/lib/x86_64-linux-gnu/crti.o",                                \
            "/usr/lib/x86_64-linux-gnu/crtn.o",                                \
            "-L/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/",               \
            "-L/usr/lib/gcc/x86_64-linux-gnu/" LIBC_VERSION "/",               \
            "-L" STATICLIB_DIR, LLVM_LDFLAGS,                                  \
            "-L" STATICLIB_DIR PATH_SEPARATOR _SNOWBALL_LIBRARY_DIR, p_input,              \
            "-lSnowballRuntime", "-lc", "-lgcc", "-lm"                         \
    }
#else
#error "Unknown compiler"
#endif