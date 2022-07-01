
#include "snowball/errors.h"

#define __RET_ERROR_IF_CODE(x, err) if (code == x) return err;

namespace snowball {
    const char* get_error(Error code) {
        __RET_ERROR_IF_CODE(Error::BUG,               "BUG")
        __RET_ERROR_IF_CODE(Error::TODO,              "TODO")
        __RET_ERROR_IF_CODE(Error::WARNING,           "Warning")
        __RET_ERROR_IF_CODE(Error::IO_ERROR,          "IO Error")
        __RET_ERROR_IF_CODE(Error::UNEXPECTED_EOF,    "Unexpected EOF")
        __RET_ERROR_IF_CODE(Error::SYNTAX_ERROR,      "Syntax error")
        __RET_ERROR_IF_CODE(Error::LLVM_INTERNAL,     "LLVM internal error")
        __RET_ERROR_IF_CODE(Error::UNDEFINED_VARIABLE,"Undefined Variable")
        __RET_ERROR_IF_CODE(Error::VARIABLE_ERROR,    "Variable Error")
        __RET_ERROR_IF_CODE(Error::COMPILER_ERROR,    "Compiler Error")

        return "";
    }
}
