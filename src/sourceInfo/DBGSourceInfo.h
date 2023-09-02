

#include "../SourceInfo.h"
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "../utils/logger.h"
#include "SourcedObject.h"

#ifndef __SNOWBALL_DBG_INFO_H_
#define __SNOWBALL_DBG_INFO_H_

#define NO_DBGINFO (DBGSourceInfo*)nullptr

namespace snowball {

/**
 * DBGSource info is used by the error handling
 * system. It basically get's the line and some
 * offset lines from a source file depending on
 * the possition.
 *
 * This is usefull to do pretty errors that can
 * display the contents of a line.
 */
class DBGSourceInfo : public SrcObject {
 public:
  DBGSourceInfo(const SourceInfo* source_info, uint32_t p_line);
  DBGSourceInfo(const SourceInfo* source_info, std::pair<int, int> p_pos, uint32_t p_width);

  uint32_t width = 0;
  uint32_t line = 0;
  std::pair<int, int> pos;

  std::string line_before;
  std::string line_str;
  std::string line_after;

 public:
  std::string get_pos_str() const;
  void prepare_for_error();
  friend SrcObject;

  auto getDBGInfo() { return this; }

  /**
   * @brief Create a new instance  of dbg source info
   * using a token as reference.
   */
  static auto fromToken(const SourceInfo* i, Token tk) { return new DBGSourceInfo(i, tk.get_pos(), tk.get_width()); }
};

/**
 * This class is used as a parent so that objects can
 * inherit from it.
 *
 * It's used as a wrapper for `DBGSourceInfo` so that
 * objects can contain dbg information instead of
 * passing it into each function that needs into in.
 * This just saves some messy code.
 */
class DBGObject : public SrcObject {
 protected:
  DBGSourceInfo* dbg = nullptr;

 public:
  /// @brief Contruct a new DBGObject
  DBGObject();

  /// @return Debug information
  virtual DBGSourceInfo* getDBGInfo();
  /// @brief Set a new dbg object
  virtual void setDBGInfo(DBGSourceInfo* i);
};
} // namespace snowball

#endif // __SNOWBALL_DBG_INFO_H_
