
#ifndef _SNOWBALL_SYMBOLS_EXPORT_H_
#define _SNOWBALL_SYMBOLS_EXPORT_H_

#if defined(__MACOSX__) || defined(__APPLE__) || defined(__MACH__)
#define _SN_SYM(x) asm("_" x)
#else 
#define _SN_SYM(x) asm(x)
#endif

#endif // _SNOWBALL_SYMBOLS_EXPORT_H_
