
#include "DBGSourceInfo.h"
#include "colors.h"
#include "logger.h"

#include <exception>
#include <optional>
#include <stdexcept>
#include <string>

#ifndef __SNOWBALL_ERRORS_H_
#define __SNOWBALL_ERRORS_H_

namespace snowball {
enum Error
{
    IO_ERROR,
    TYPE_ERROR,
    SYNTAX_ERROR,
    UNDEFINED_VARIABLE,
    UNEXPECTED_EOF,
    REFERENCE_ERROR,
    WARNING,
    VARIABLE_ERROR,
    CONFIGURATION_ERROR,
    ATTRIBUTE_ERROR,
    ARGUMENT_ERROR,
    PSEUDO_ERROR,
    FUNCTION_RET_ERR,
    COMPILER_ERROR, // note: not the same as "compile time error"

    LLVM_INTERNAL,
    LINKER_ERR,

    BUG,
    TODO
};

namespace errors {
const char* get_error(Error code);

class SNError {
  public:
    SNError(Error code, std::string err) {
        error = code;
        message = err;
    };

    virtual void print_error(bool _ = false) const {
        Logger::error(
                FMT("(%s%s%s) %s%s%s", RED, get_error(error), RESET, BOLD, message.c_str(), RESET));
    };

    virtual ~SNError(){};

    Error error;
    std::string message;
};

struct ErrorInfo {
    const std::string info = "";
    const std::string note = "";

    const std::string help = "";
    const std::string consider = "";

    SNError* tail = nullptr;
};

class NiceError : public SNError {
  protected:
    DBGSourceInfo* cb_dbg_info;

  public:
    ErrorInfo info;
    NiceError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
        : SNError(code, err), cb_dbg_info(p_cb_dbg_info), info(info){};
    virtual void print_error(bool asTail = false) const override;
};

class LexerError : public NiceError {
  public:
    LexerError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
        : NiceError(code, err, p_cb_dbg_info, info){};

    virtual ~LexerError(){};
};

class ParserError : public NiceError {
  public:
    ParserError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
        : NiceError(code, err, p_cb_dbg_info, info){};

    virtual ~ParserError(){};
};

class CompilerError : public NiceError {
  public:
    CompilerError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
        : NiceError(code, err, p_cb_dbg_info, info){};

    virtual ~CompilerError(){};
};

} // namespace errors

using LexerError = errors::LexerError;
using ParserError = errors::ParserError;
using CompilerError = errors::CompilerError;

using SNError = errors::SNError;
using ErrorInfo = errors::ErrorInfo;

} // namespace snowball

#endif // __SNOWBALL_ERRORS_H_
