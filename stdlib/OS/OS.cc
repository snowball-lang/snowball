#include "snowball/api.h"
#include "snowball/types.h"
#include "snowball/scopes.h"
#include "snowball/snowball.h"
#include "snowball/types/Bool.h"
#include "snowball/types/String.h"
#include "snowball/types.h"

#include "snowball/export.hpp"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <typeinfo>

#include "snowball/constants.h"
#include "snowball/utils/api.h"

#include "../_include/OS.h"

// == Exports

/**
 * Determination a platform of an operation system
 * Fully supported supported only GNU GCC/G++, partially on Clang/LLVM
 */

#if defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
    #define PLATFORM_NAME "windows" // Windows
#elif defined(__CYGWIN__) && !defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows (Cygwin POSIX under Microsoft Window)
#elif defined(__ANDROID__)
    #define PLATFORM_NAME "android" // Android (implies Linux, so it must come first)
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define PLATFORM_NAME "bsd" // FreeBSD, NetBSD, OpenBSD, DragonFly BSD
    #endif
#elif defined(__hpux)
    #define PLATFORM_NAME "hp-ux" // HP-UX
#elif defined(_AIX)
    #define PLATFORM_NAME "aix" // IBM AIX
#elif defined(__APPLE__) && defined(__MACH__) // Apple OSX and iOS (Darwin)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1
        #define PLATFORM_NAME "ios" // Apple iOS
    #elif TARGET_OS_IPHONE == 1
        #define PLATFORM_NAME "ios" // Apple iOS
    #elif TARGET_OS_MAC == 1
        #define PLATFORM_NAME "osx" // Apple OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define PLATFORM_NAME "solaris" // Oracle Solaris, Open Indiana
#else
    #define PLATFORM_NAME "error"
#endif

char* OS::name() {
    return (char*)PLATFORM_NAME;
}


// == Definitions
extern "C" snowball::ScopeValue* sn_export(snowball::SNAPI* API) {

    return API->create_module("OS", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {

        llvm::Type* void_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::VOID, API->compiler->builder);
        llvm::Type* float_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::FLOAT, API->compiler->builder);
        llvm::Type* bool_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::BOOL, API->compiler->builder);
        llvm::Type* string_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::STRING, API->compiler->builder);
        llvm::Type* double_type = snowball::get_llvm_type_from_sn_type(snowball::BuildinTypes::DOUBLE, API->compiler->builder);
        llvm::Type* int16_type = API->compiler->builder->getInt16Ty();
        llvm::Type* int32_type = API->compiler->builder->getInt32Ty();
        llvm::Type* int64_type = API->compiler->builder->getInt64Ty();

        METHOD("name", string_type, {},  "_ZN2OS4nameEv")
    });
}