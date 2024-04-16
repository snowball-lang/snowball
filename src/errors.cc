
#include "errors.h"
#include "utils/utils.h"

#define RET_ERROR_IF_CODE(x, err) \
  if (code == x) return err;

namespace snowball {
namespace errors {

namespace {
/// @brief replace 'hello' with [white]'hello'[reset]
std::string highlight(std::string str) {
  std::string ret = "";
  bool in_highlight = false;
  for (size_t i = 0; i < str.size(); i++) {
    bool add = false;
    if (str[i] == '\'') {
      if (in_highlight) {
        add = true;
      } else {
        ret += BWHT;
        in_highlight = true;
      }
    }
    ret += str[i];
    if (add) {
      ret += RESET;
      in_highlight = false;
    }
  }
  return ret;
}
} // namespace

void NiceError::print_error(bool asTail) const {
  cb_dbg_info->prepare_for_error();
  if (!asTail) {
    Logger::log("");
    Logger::error(FMT("(%s%s%s) %s%s%s", BRED, get_error(error), RESET, BOLD, RESET, highlight(message).c_str()));
    Logger::elog(FMT("%s╚══╤══╝", BLK));
    Logger::elog(FMT("   ╰───╮%s", RESET));
    Logger::elog(
      FMT("%s       ├─[%s%s%s%s:%i:%i%s%s]%s",
          BLK,
          RESET,
          BBLU,
          cb_dbg_info->getSourceInfo()->getPath().c_str(),
          BBLK,
          cb_dbg_info->line,
          cb_dbg_info->pos.second,
          RESET,
          BLK,
          RESET)
    );
  } else {
    Logger::elog(
      FMT("%s       ├─[%s%s%s%s:%i:%i%s%s]%s",
          BLK,
          RESET,
          BBLU,
          cb_dbg_info->getSourceInfo()->getPath().c_str(),
          BBLK,
          cb_dbg_info->line,
          cb_dbg_info->pos.second,
          RESET,
          BLK,
          RESET)
    );
  }
  // Logger::elog(FMT("%s       │%s", BLK, RESET));
  Logger::elog(FMT("%s       │%s", BLK, RESET));
  if ((((int) cb_dbg_info->line) - 2) >= 1) // first line may not be available to log
    Logger::elog(FMT("  %s%4i%s │  %s", BBLK, cb_dbg_info->line - 2, BLK, cb_dbg_info->line_before_before.c_str()));
  if ((((int) cb_dbg_info->line) - 1) >= 1) // first line may not be available to log
    Logger::elog(FMT("  %s%4i%s │  %s", BBLK, cb_dbg_info->line - 1, BLK, cb_dbg_info->line_before.c_str()));
  // highlight line where the error is
  // e.g.  hello<String>(1, 2, 3)
  //       ~~~~~
  // converted to
  // [white]hello[gray]<string>(1, 2, 3)
  std::string line_str = "";
  for (size_t i = 0; i < cb_dbg_info->line_str.size(); i++) {
    if (i >= (size_t)cb_dbg_info->pos.second - 1 && i < cb_dbg_info->pos.second + cb_dbg_info->width - 1) {
      line_str += BWHT;
    } else if (i >= cb_dbg_info->pos.second + cb_dbg_info->width - 1) {
      line_str += BLK;
    }
    line_str += cb_dbg_info->line_str[i];
  }
  Logger::elog(
    FMT(" %s %4i%s >%s  %s\n       %s│%s  %s%s %s%s",
        BWHT,
        cb_dbg_info->line,
        BLK,
        BLK,
        line_str.c_str(),
        BLK,
        RESET,
        BRED,
        cb_dbg_info->get_pos_str().c_str(),
        info.info.c_str(),
        RESET)
  );
  if (!cb_dbg_info->line_after_after.empty() || !cb_dbg_info->line_after.empty())
    Logger::elog(FMT("  %s%4i%s │  %s", BBLK, cb_dbg_info->line + 1, BLK, cb_dbg_info->line_after.c_str()));
  if (!cb_dbg_info->line_after_after.empty())
    Logger::elog(FMT("  %s%4i%s │  %s", BBLK, cb_dbg_info->line + 2, BLK, cb_dbg_info->line_after_after.c_str()));
  if (!info.note.empty()) {
    Logger::elog(FMT("%s       │", BLK));
    Logger::elog(FMT("%s       │", BLK));
    auto lines = utils::split(highlight(info.note), "\n");
    Logger::elog(FMT("%s   note%s:%s %s", BCYN, BBLK, RESET, (*lines.begin()).c_str()));
    lines.pop_front();
    for (auto line : lines) { Logger::elog(FMT("%s       │  %s%s", BLK, RESET, line.c_str())); }
  }
  if (auto x = info.tail) {
    if (info.note.empty()) Logger::elog(FMT("%s       │", BLK));
    Logger::elog(FMT("%s       │", BLK));
    Logger::elog(FMT("%s       :", BLK));
    Logger::elog(FMT("%s       │", BLK));
    x->print_error(true);
  }
  if (!info.help.empty()) {
    // if (!info.note.empty())
    Logger::elog(FMT("%s       │", BLK));
    auto lines = utils::split(highlight(info.help), "\n");
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
  RET_ERROR_IF_CODE(Error::PM_ERROR, "Package Manager")
  return "Error";
}
} // namespace errors
} // namespace snowball
