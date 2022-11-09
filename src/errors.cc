
#include "snowball/errors.h"


namespace snowball {
    #define RET_ERROR_IF_CODE(x, err) if (code == x) return err;
    const char* get_error(Error code) {
        RET_ERROR_IF_CODE(Error::BUG,                 "BUG")
        RET_ERROR_IF_CODE(Error::TODO,                "TODO")
        RET_ERROR_IF_CODE(Error::WARNING,             "Warning")
        RET_ERROR_IF_CODE(Error::IO_ERROR,            "IO Error")
        RET_ERROR_IF_CODE(Error::TYPE_ERROR,          "Type Error")
        RET_ERROR_IF_CODE(Error::UNEXPECTED_EOF,      "Unexpected EOF")
        RET_ERROR_IF_CODE(Error::SYNTAX_ERROR,        "Syntax error")
        RET_ERROR_IF_CODE(Error::LLVM_INTERNAL,       "LLVM internal error")
        RET_ERROR_IF_CODE(Error::UNDEFINED_VARIABLE,  "Undefined Variable")
        RET_ERROR_IF_CODE(Error::VARIABLE_ERROR,      "Variable Error")
        RET_ERROR_IF_CODE(Error::COMPILER_ERROR,      "Compiler Error")
        RET_ERROR_IF_CODE(Error::ARGUMENT_ERROR,      "Argument Error")
        RET_ERROR_IF_CODE(Error::FUNCTION_RET_ERR,    "Function Return Error")
        RET_ERROR_IF_CODE(Error::CONFIGURATION_ERROR, "Configuration Error")
        RET_ERROR_IF_CODE(Error::LINKER_ERR,          "Linker Error")

        return "Error";
    }
    #undef RET_ERROR_IF_CODE
}
