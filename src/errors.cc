
#include "errors.h"
#define RET_ERROR_IF_CODE(x, err)                                              \
    if (code == x) return err;

namespace snowball {
namespace errors {

void NiceError::print_error() const {
    Logger::log("");
    Logger::elog(FMT("%s     ╭─[%s%s%s%s:%i:%i%s%s]%s", BLK, RESET, BBLU,
                     cb_dbg_info->getSourceInfo()->getPath().c_str(), BBLK,
                     cb_dbg_info->line, cb_dbg_info->pos.second, RESET, BLK,
                     RESET));
    Logger::elog(FMT("%s     │%s", BLK, RESET));
    if (cb_dbg_info->line - 1 >= 1) // first line may not be available to log
        Logger::elog(FMT("  %s%2i%s │ %s%s", BBLK, cb_dbg_info->line - 1, BLK,
                         BWHT, cb_dbg_info->line_before.c_str()));
    Logger::elog(FMT(" %s>%2i%s │ %s%s\n     %s│%s %s%s %s%s", BBLK,
                     cb_dbg_info->line, BLK, BWHT,
                     cb_dbg_info->line_str.c_str(), BLK, RESET, BRED,
                     cb_dbg_info->get_pos_str().c_str(), info.c_str(), RESET));
    Logger::elog(FMT("  %s%2i%s │ %s%s", BBLK, cb_dbg_info->line + 1, BLK, BWHT,
                     cb_dbg_info->line_after.c_str()));
    Logger::elog(FMT("%s     │", BLK));
    Logger::elog(FMT("   ──╯%s", RESET));

    Logger::error(FMT("(%s%s%s) %s%s%s", RED, get_error(error), RESET, BOLD,
                      message.c_str(), RESET));
};

ptr<const char> get_error(Error code) {
    RET_ERROR_IF_CODE(Error::BUG, "BUG")
    RET_ERROR_IF_CODE(Error::TODO, "TODO")
    RET_ERROR_IF_CODE(Error::WARNING, "Warning")
    RET_ERROR_IF_CODE(Error::IO_ERROR, "IO Error")
    RET_ERROR_IF_CODE(Error::TYPE_ERROR, "Type Error")
    RET_ERROR_IF_CODE(Error::UNEXPECTED_EOF, "Unexpected EOF")
    RET_ERROR_IF_CODE(Error::SYNTAX_ERROR, "Syntax error")
    RET_ERROR_IF_CODE(Error::LLVM_INTERNAL, "LLVM internal error")
    RET_ERROR_IF_CODE(Error::UNDEFINED_VARIABLE, "Undefined Variable")
    RET_ERROR_IF_CODE(Error::VARIABLE_ERROR, "Variable Error")
    RET_ERROR_IF_CODE(Error::COMPILER_ERROR, "Compiler Error")
    RET_ERROR_IF_CODE(Error::ARGUMENT_ERROR, "Argument Error")
    RET_ERROR_IF_CODE(Error::FUNCTION_RET_ERR, "Function Return Error")
    RET_ERROR_IF_CODE(Error::CONFIGURATION_ERROR, "Configuration Error")
    RET_ERROR_IF_CODE(Error::LINKER_ERR, "Linker Error")

    return "Error";
}
} // namespace errors
} // namespace snowball
