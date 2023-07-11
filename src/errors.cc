
#include "errors.h"

#include "utils/utils.h"

#define RET_ERROR_IF_CODE(x, err)                                                                  \
    if (code == x) return err;

namespace snowball {
namespace errors {

void NiceError::print_error(bool asTail) const {
    cb_dbg_info->prepare_for_error();

    if (!asTail) {
        Logger::log("");
        Logger::error(FMT(
                "(%s%s%s) %s%s%s", BRED, get_error(error), RESET, BOLD, message.c_str(), RESET));
        Logger::elog(FMT("%s       ╭─[%s%s%s%s:%i:%i%s%s]%s",
                         BLK,
                         RESET,
                         BBLU,
                         cb_dbg_info->getSourceInfo()->getPath().c_str(),
                         BBLK,
                         cb_dbg_info->line,
                         cb_dbg_info->pos.second,
                         RESET,
                         BLK,
                         RESET));
    } else {
        Logger::elog(FMT("%s       ├─[%s%s%s%s:%i:%i%s%s]%s",
                         BLK,
                         RESET,
                         BBLU,
                         cb_dbg_info->getSourceInfo()->getPath().c_str(),
                         BBLK,
                         cb_dbg_info->line,
                         cb_dbg_info->pos.second,
                         RESET,
                         BLK,
                         RESET));
    }

    Logger::elog(FMT("%s       │%s", BLK, RESET));
    Logger::elog(FMT("%s       │%s", BLK, RESET));
    if (cb_dbg_info->line - 1 >= 1) // first line may not be available to log
        Logger::elog(FMT("  %s%4i%s │ %s%s",
                         BBLK,
                         cb_dbg_info->line - 1,
                         BLK,
                         BWHT,
                         cb_dbg_info->line_before.c_str()));
    Logger::elog(FMT(" %s %4i >%s %s%s\n       %s│%s %s%s %s%s",
                     BBLK,
                     cb_dbg_info->line,
                     BLK,
                     BWHT,
                     cb_dbg_info->line_str.c_str(),
                     BLK,
                     RESET,
                     BRED,
                     cb_dbg_info->get_pos_str().c_str(),
                     info.info.c_str(),
                     RESET));
    Logger::elog(FMT("  %s%4i%s │ %s%s",
                     BBLK,
                     cb_dbg_info->line + 1,
                     BLK,
                     BWHT,
                     cb_dbg_info->line_after.c_str()));

    if (!info.note.empty()) {
        Logger::elog(FMT("%s       │", BLK));

        auto lines = utils::split(info.note, "\n");

        Logger::elog(FMT("%s   note%s:%s %s", BCYN, BBLK, RESET, (*lines.begin()).c_str()));

        lines.pop_front();
        for (auto line : lines) { Logger::elog(FMT("%s     │  %s%s", BLK, RESET, line.c_str())); }
    }

    if (auto x = info.tail) {
        if (info.note.empty()) Logger::elog(FMT("%s       │", BLK));
        Logger::elog(FMT("%s       │", BLK));
        Logger::elog(FMT("%s       :", BLK));
        Logger::elog(FMT("%s       │", BLK));

        x->print_error(true);
    }

    if (!info.help.empty()) {
        Logger::elog(FMT("%s       │", BLK));

        auto lines = utils::split(info.help, "\n");

        Logger::elog(FMT("%s   help%s:%s %s", BGRN, BBLK, RESET, (*lines.begin()).c_str()));

        lines.pop_front();
        for (auto line : lines) { Logger::elog(FMT("%s       │  %s%s", BLK, RESET, line.c_str())); }
    }

    Logger::elog(FMT("%s       │", BLK));

    if (!asTail) {
        Logger::elog(FMT("   ────╯%s", RESET));
        Logger::log("\n");
    }
};

const char* get_error(Error code) {
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
    RET_ERROR_IF_CODE(Error::REFERENCE_ERROR, "Reference Error")
    RET_ERROR_IF_CODE(Error::ATTRIBUTE_ERROR, "Attribute Error")
    RET_ERROR_IF_CODE(Error::PSEUDO_ERROR, "Pseudo-code Error")
    RET_ERROR_IF_CODE(Error::IMPORT_ERROR, "Import Error")
    RET_ERROR_IF_CODE(Error::DEREFERENCE_ERROR, "Dereference Error")

    return "Error";
}
} // namespace errors
} // namespace snowball
