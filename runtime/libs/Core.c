

#include <stdlib.h>
#include "../gc/gc.h"

// Make it always be equal to the definition in snowball Core runtime
typedef struct UniversalArray {
    void** data;
} UniversalArray_T;

extern UniversalArray_T* ua_allocate(int size) __asm__("sn.ua.alloc");
extern UniversalArray_T* ua_resize(UniversalArray_T* ua, int size) __asm__("sn.ua.resize");
extern void* ua_get(UniversalArray_T* ua, int index) __asm__("sn.ua.get");
extern void* ua_set(UniversalArray_T* ua, int index, void* value) __asm__("sn.ua.set");

UniversalArray_T* ua_allocate(int size) {
    return (UniversalArray_T*)sn_alloca(size);
}

UniversalArray_T* ua_resize(UniversalArray_T* ua, int size) {
    return (UniversalArray_T*)sn_realloc(ua, size);
}

void* ua_get(UniversalArray_T* ua, int index) {
    return (void*)ua->data[index];
}

void* ua_set(UniversalArray_T* ua, int index, void* value) {
    ua->data[index] = value;
    return value;
}
