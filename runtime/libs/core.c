

#include <stdlib.h>
#include "../gc/gc.h"
#include "sym.h"

// Make it always be equal to the definition in snowball Core runtime
typedef struct UniversalArray {
    void** data;
} UniversalArray_T;

extern UniversalArray_T* ua_allocate(int size) _SN_SYM("sn.ua.alloc");
extern UniversalArray_T* ua_resize(UniversalArray_T* ua, int size) _SN_SYM("sn.ua.resize");
extern void* ua_get(UniversalArray_T* ua, int index) _SN_SYM("sn.ua.get");
extern void ua_set(UniversalArray_T* ua, int index, void* value) _SN_SYM("sn.ua.set");

UniversalArray_T* ua_allocate(int size) {
    UniversalArray_T* array = (UniversalArray_T*)sn_alloca(size);
    array->data = sn_alloca(size * sizeof(void*));
    return array;
}

UniversalArray_T* ua_resize(UniversalArray_T* ua, int size) {
    ua->data = sn_realloc(ua->data, size * sizeof(void*));
    return ua;
}

void* ua_get(UniversalArray_T* ua, int index) {
    return (void*)&ua->data[index];
}

void ua_set(UniversalArray_T* ua, int index, void* value) {
    ua->data[index] = value;
}
