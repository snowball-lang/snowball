
#ifndef __SNOWBALL_CONSTANTS_H_
#define __SNOWBALL_CONSTANTS_H_

#ifdef __cplusplus
extern "C" {
#endif

// breaking.feature.fix
#define _SNOWBALL_VERSION                   "1.1.1"
#define _SNOWBALL_VERSION_NUMBER            0x010101
#define _SNOWBALL_BUILD_DATE                __DATE__
#define _SNOWBALL_BUILD_TIME                __TIME__

// Function names
#define _SNOWBALL_FUNCTION_ENTRY            "main"

// Keywords
#define _SNOWBALL_KEYWORD__OR               "or"
#define _SNOWBALL_KEYWORD__IF               "if"
#define _SNOWBALL_KEYWORD__AND              "and"
#define _SNOWBALL_KEYWORD__NOT              "not"
#define _SNOWBALL_KEYWORD__FOR              "for"
#define _SNOWBALL_KEYWORD__CASE             "case"
#define _SNOWBALL_KEYWORD__THIS             "this"
#define _SNOWBALL_KEYWORD__ENUM             "enum"
#define _SNOWBALL_KEYWORD__NULL             "null"
#define _SNOWBALL_KEYWORD__TRUE             "true"
#define _SNOWBALL_KEYWORD__ELSE             "else"
#define _SNOWBALL_KEYWORD__CLASS            "class"
#define _SNOWBALL_KEYWORD__FALSE            "false"
#define _SNOWBALL_KEYWORD__WHILE            "while"
#define _SNOWBALL_KEYWORD__BREAK            "break"
#define _SNOWBALL_KEYWORD__SUPER            "super"
#define _SNOWBALL_KEYWORD__STATIC           "static"
#define _SNOWBALL_KEYWORD__IMPORT           "import"
#define _SNOWBALL_KEYWORD__RETURN           "return"
#define _SNOWBALL_KEYWORD__SWITCH           "switch"
#define _SNOWBALL_KEYWORD__DEFAULT          "default"
#define _SNOWBALL_KEYWORD__CONTINUE         "continue"
#define _SNOWBALL_KEYWORD__FUNCTION         "func"
#define _SNOWBALL_KEYWORD__VARIABLE         "var"
#define _SNOWBALL_KEYWORD__CONSTANT         "const"
#define _SNOWBALL_KEYWORD__UNDEFINED        "undefined"

// Debug
#ifndef NDEBUG
// Production builds should set NDEBUG=1
#define NDEBUG false
#else
#define NDEBUG true
#endif

#ifndef DEBUG
#define DEBUG !NDEBUG
#endif

#ifdef NDEBUG
    #define _SNOWBALL_BUILD_TYPE "Debug"
#else
    #define _SNOWBALL_BUILD_TYPE "Default"
#endif

// Compiler lines
#define _SNOWBALL_COMPILER_ENTRY            "Snowball " _SNOWBALL_VERSION " (" _SNOWBALL_BUILD_TYPE ": " _SNOWBALL_BUILD_DATE ", " _SNOWBALL_BUILD_TIME ")"
#define _SNOWBALL_COMPILER_ENTRY_BK         "\
Snowball " _SNOWBALL_VERSION " (" _SNOWBALL_BUILD_TYPE ": " _SNOWBALL_BUILD_DATE ", " _SNOWBALL_BUILD_TIME ")\n\
Type \"help\", \"copyright\", \"credits\" or \"license\" for more information.\
"

// Licenses
#define _SNOWBALL_LICENSE_NAME              "MIT"
#define _SNOWBALL_LICENSE_TEXT              "\
The MIT License (MIT)\n\
\n\
Copyright (c) 2022 mauro-balades <mauro.balades@tutanota.com>\n\
\n\
Permission is hereby granted, free of charge, to any person obtaining a copy\n\
of this software and associated documentation files (the \"Software\"), to deal\n\
in the Software without restriction, including without limitation the rights\n\
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n\
copies of the Software, and to permit persons to whom the Software is\n\
furnished to do so, subject to the following conditions:\n\
\n\
The above copyright notice and this permission notice shall be included in\n\
all copies or substantial portions of the Software.\n\
\n\
THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n\
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n\
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n\
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n\
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n\
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN\n\
THE SOFTWARE."

#ifdef __cplusplus
}
#endif

#endif // __SNOWBALL_CONSTANTS_H_
