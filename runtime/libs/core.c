

#include <stdlib.h>
#include "../gc/gc.h"

// Make it always be equal to the definition in snowball Core runtime
typedef struct UniversalArray {
    void** data;
} UniversalArray_T;

extern UniversalArray_T* ua_allocate(int size) __asm__("sn.ua.alloc");
extern UniversalArray_T* ua_resize(UniversalArray_T* ua, int size) __asm__("sn.ua.resize");
extern void* ua_get(UniversalArray_T* ua, int index) __asm__("sn.ua.get");
extern void ua_set(UniversalArray_T* ua, int index, void* value) __asm__("sn.ua.set");

UniversalArray_T* ua_allocate(int size) {
    UniversalArray_T* array = sn_alloca(size);
    array->data = sn_alloca(size * sizeof(void*));
    return array;
}

UniversalArray_T* ua_resize(UniversalArray_T* ua, int size) {
    ua->data = sn_realloc(ua->data, size * sizeof(void*));
    return ua;
}

void* ua_get(UniversalArray_T* ua, int index) {
    return (void*)ua->data[index];
}

void ua_set(UniversalArray_T* ua, int index, void* value) {
    ua->data[index] = value;
}
