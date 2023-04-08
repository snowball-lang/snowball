
#include "DBGSourceInfo.h"
#include "colors.h"
#include "logger.h"

#include <exception>
#include <stdexcept>
#include <string>

#ifndef __SNOWBALL_ERRORS_H_
#define __SNOWBALL_ERRORS_H_

namespace snowball {
enum Error {
    IO_ERROR,
    TYPE_ERROR,
    SYNTAX_ERROR,
    UNDEFINED_VARIABLE,
    UNEXPECTED_EOF,
    REFERENCE_ERROR,
    WARNING,
    VARIABLE_ERROR,
    CONFIGURATION_ERROR,
    ARGUMENT_ERROR,
    FUNCTION_RET_ERR,
    COMPILER_ERROR, // note: not the same as "compile time error"

    LLVM_INTERNAL,
    LINKER_ERR,

    BUG,
    TODO
};

namespace errors {
const char *get_error(Error code);

class SNError {
  public:
    SNError(Error code, std::string err) {
        error   = code;
        message = err;
    };

    virtual void print_error() const {
        Logger::error(FMT("(%s%s%s) %s%s%s", RED, get_error(error), RESET, BOLD,
                          message.c_str(), RESET));
    };

    virtual ~SNError(){};

    Error error;
    std::string message;
};

class NiceError : public SNError {
  protected:
    ptr<DBGSourceInfo> cb_dbg_info;
    const std::string info;

  public:
    NiceError(Error code, std::string err, DBGSourceInfo *p_cb_dbg_info,
              const std::string& info = "")
        : SNError(code, err), cb_dbg_info(p_cb_dbg_info), info(info){};
    virtual void print_error() const override;
};

class LexerError : public NiceError {
  public:
    LexerError(Error code, std::string err, DBGSourceInfo *p_cb_dbg_info,
               const std::string& info = "")
        : NiceError(code, err, p_cb_dbg_info, info){};

    virtual ~LexerError(){};
};

class ParserError : public NiceError {
  public:
    ParserError(Error code, std::string err, DBGSourceInfo *p_cb_dbg_info,
                const std::string& info = "")
        : NiceError(code, err, p_cb_dbg_info, info){};

    virtual ~ParserError(){};
};

class Warning : public SNError {
  public:
    Warning(std::string warn, DBGSourceInfo *p_cb_dbg_info)
        : SNError(Error::WARNING, warn) {
        cb_dbg_info = p_cb_dbg_info;
    };

    virtual void print_error() const {
        Logger::warning(FMT("%s%s%s", BOLD, message.c_str(), RESET));
        Logger::elog(FMT("  %s-->%s %s:[%i:%i]", BBLU, RESET,
                         cb_dbg_info->getSourceInfo()->getPath().c_str(),
                         cb_dbg_info->line, cb_dbg_info->pos.second, WHT));
        Logger::elog(FMT("%s    |%s", BBLU, RESET));

        if (cb_dbg_info->line - 1 >=
            1) // first line may not be available to log
            Logger::elog(FMT("%s %2i | %s%s", BBLU, cb_dbg_info->line - 1,
                             RESET, cb_dbg_info->line_before.c_str()));
        Logger::elog(FMT("%s %2i | %s%s/%s %s\n   %s|%s %s|_%s%s%s%s", BBLU,
                         cb_dbg_info->line, RESET, BYEL, RESET,
                         cb_dbg_info->line_str.c_str(), BBLU, RESET, BYEL,
                         RESET, BYEL, cb_dbg_info->get_pos_str().c_str(),
                         RESET));
        Logger::elog(FMT("%s %2i | %s%s\n", BBLU, cb_dbg_info->line + 1, RESET,
                         cb_dbg_info->line_after.c_str()));
    };

    virtual ~Warning(){};

  private:
    DBGSourceInfo *cb_dbg_info;
};

class CompilerError : public NiceError {
  public:
    CompilerError(Error code, std::string err, DBGSourceInfo *p_cb_dbg_info,
                  const std::string& info = "")
        : NiceError(code, err, p_cb_dbg_info, info){};

    virtual ~CompilerError(){};
};
} // namespace errors

using LexerError    = errors::LexerError;
using ParserError   = errors::ParserError;
using CompilerError = errors::CompilerError;
using Warning       = errors::Warning;

using SNError = errors::SNError;

} // namespace snowball

#endif // __SNOWBALL_ERRORS_H_
