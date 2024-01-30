
#include "sourceInfo/DBGSourceInfo.h"
#include "utils/colors.h"
#include "utils/logger.h"

#include <exception>
#include <optional>
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
  ATTRIBUTE_ERROR,
  ARGUMENT_ERROR,
  IMPORT_ERROR,
  PSEUDO_ERROR,
  DEREFERENCE_ERROR,
  FUNCTION_RET_ERR,
  PM_ERROR,
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
    Logger::error(FMT("(%s%s%s) %s%s%s", BRED, get_error(error), RESET, BOLD, message.c_str(), RESET));
  };

  virtual ~SNError() {};

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

/**
 * @brief A nice error is an error that is printed in a nice way.
 */
class NiceError : public SNError {
 protected:
  DBGSourceInfo* cb_dbg_info;

 public:
  ErrorInfo info;
  NiceError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
    : SNError(code, err), cb_dbg_info(p_cb_dbg_info), info(info) {};
  virtual void print_error(bool asTail = false) const override;
};

/**
 * @brief A lexer error is an error that occurs during lexing.
 */
class LexerError : public NiceError {
 public:
  LexerError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
    : NiceError(code, err, p_cb_dbg_info, info) {};

  virtual ~LexerError() {};
};

/**
 * @brief A parser error is an error that occurs during parsing.
 */
class ParserError : public NiceError {
 public:
  ParserError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
    : NiceError(code, err, p_cb_dbg_info, info) {};

  virtual ~ParserError() {};
};

/**
 * @brief A compiler error is an error that occurs during compilation.
 */
class CompilerError : public NiceError {
 public:
  CompilerError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
    : NiceError(code, err, p_cb_dbg_info, info) {};

  virtual ~CompilerError() {};
};

} // namespace errors

using LexerError = errors::LexerError;
using ParserError = errors::ParserError;
using CompilerError = errors::CompilerError;

using SNError = errors::SNError;
using ErrorInfo = errors::ErrorInfo;

} // namespace snowball

#endif // __SNOWBALL_ERRORS_H_
