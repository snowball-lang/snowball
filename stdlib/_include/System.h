#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct System {
    static void println(char*   __msg);
    static void println(bool    __msg);
    static void println(int16_t __msg);
    static void println(int32_t __msg);
    static void println(int64_t __msg);
    static void println(float   __msg);
    static void println(double  __msg);

    static void print(char*   __msg);
    static void print(bool    __msg);
    static void print(int16_t __msg);
    static void print(int32_t __msg);
    static void print(int64_t __msg);
    static void print(float   __msg);
    static void print(double  __msg);

    static char* input();
    static void exit(int code);
};