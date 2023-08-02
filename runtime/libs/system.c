
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "sym.h"

extern const char* f() _SN_SYM("sn.core.libs.System.input");
const char* f() {
    int size = 10;
    char *str;
    int ch;
    size_t len = 0;

    str = (char*)realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(stdin)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = (char*)realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return (const char*)realloc(str, sizeof(*str)*len);
}
