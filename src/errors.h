
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
/**
 * @brief Enumerated type Error represents various error types in the system.
 * 
 * The Error enum provides a set of predefined error types that can occur during
 * the execution of a program. These error types can be used to categorize and
 * handle different types of errors in a consistent manner.
 * 
 * The following error types are defined in the Error enum:
 * 
 * - IO_ERROR: Represents an input/output error.
 * - TYPE_ERROR: Represents a type-related error.
 * - SYNTAX_ERROR: Represents a syntax error.
 * - UNDEFINED_VARIABLE: Represents an error due to an undefined variable.
 * - UNEXPECTED_EOF: Represents an error indicating an unexpected end of file.
 * - REFERENCE_ERROR: Represents an error related to referencing an invalid or inaccessible value.
 * - WARNING: Represents a warning message.
 * - VARIABLE_ERROR: Represents an error related to variables.
 * - CONFIGURATION_ERROR: Represents an error in the system configuration.
 * - ATTRIBUTE_ERROR: Represents an error related to attributes.
 * - ARGUMENT_ERROR: Represents an error related to function arguments.
 * - IMPORT_ERROR: Represents an error related to importing modules or libraries.
 * - PSEUDO_ERROR: Represents a pseudo error or a placeholder for errors not yet defined.
 * - FUNCTION_RET_ERR: Represents an error related to function return values.
 * - COMPILER_ERROR: Represents an error specific to the compiler (different from compile time errors).
 * - LLVM_INTERNAL: Represents an error specific to LLVM internals.
 * - LINKER_ERR: Represents an error related to the linker.
 * - BUG: Represents a known bug or an unexpected behavior in the system.
 * - TODO: Represents a placeholder for incomplete or unfinished code sections.
 * 
 * This enum provides a convenient way to classify and handle different types of errors
 * that can occur during program execution. It allows for consistent error handling and
 * can be used to define error codes or messages associated with each error type.
 */
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
    IMPORT_ERROR,
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

/**
 * @brief A nice error is an error that is printed in a nice way.
 */
class NiceError : public SNError {
  protected:
    DBGSourceInfo* cb_dbg_info;

  public:
    ErrorInfo info;
    NiceError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
        : SNError(code, err), cb_dbg_info(p_cb_dbg_info), info(info){};
    virtual void print_error(bool asTail = false) const override;
};

/**
 * @brief A lexer error is an error that occurs during lexing.
 */
class LexerError : public NiceError {
  public:
    LexerError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
        : NiceError(code, err, p_cb_dbg_info, info){};

    virtual ~LexerError(){};
};

/**
 * @brief A parser error is an error that occurs during parsing.
 */
class ParserError : public NiceError {
  public:
    ParserError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info, ErrorInfo info = {})
        : NiceError(code, err, p_cb_dbg_info, info){};

    virtual ~ParserError(){};
};

/**
 * @brief A compiler error is an error that occurs during compilation.
 */
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
