
#ifndef _SNOWBALL_GARBAGE_COLLECTOR_H_
#define _SNOWBALL_GARBAGE_COLLECTOR_H_

extern void* sn_alloca(int bytes) __asm__("sn.alloca");
extern void* sn_realloc(void* object, int bytes) __asm__("sn.realloc");

#endif // _SNOWBALL_GARBAGE_COLLECTOR_H_
