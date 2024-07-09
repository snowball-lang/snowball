
#ifndef SNOWBALL_EXPORT_H
#define SNOWBALL_EXPORT_H

#ifdef SNOWBALL_STATIC
#  define SNOWBALL_EXPORT
#  define SNOWBALL_NO_EXPORT
#else
#  ifndef SNOWBALL_EXPORT
#    ifdef snowball_EXPORTS
        /* We are building this library */
#      define SNOWBALL_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SNOWBALL_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef SNOWBALL_NO_EXPORT
#    define SNOWBALL_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef SNOWBALL_DEPRECATED
#  define SNOWBALL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef SNOWBALL_DEPRECATED_EXPORT
#  define SNOWBALL_DEPRECATED_EXPORT SNOWBALL_EXPORT SNOWBALL_DEPRECATED
#endif

#ifndef SNOWBALL_DEPRECATED_NO_EXPORT
#  define SNOWBALL_DEPRECATED_NO_EXPORT SNOWBALL_NO_EXPORT SNOWBALL_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef SNOWBALL_NO_DEPRECATED
#    define SNOWBALL_NO_DEPRECATED
#  endif
#endif

#endif /* SNOWBALL_EXPORT_H */
