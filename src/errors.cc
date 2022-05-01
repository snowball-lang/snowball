
#include "errors.h"

#define __RET_ERROR_IF_CODE(x, err) if (code == x) return err;

namespace snowball {
    const char* get_error(Error code) {
        __RET_ERROR_IF_CODE(Error::BUG,               "BUG")
        __RET_ERROR_IF_CODE(Error::TODO,              "TODO")
        __RET_ERROR_IF_CODE(Error::UNEXPECTED_EOF,    "Unexpected EOF")

        return "";
    }
}
