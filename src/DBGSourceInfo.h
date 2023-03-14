

#include "SourcedObject.h"
#include "common.h"
#include "logger.h"
#include "source_info.h"
#include "token.h"

#ifndef __SNOWBALL_DBG_INFO_H_
#define __SNOWBALL_DBG_INFO_H_

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
    DBGSourceInfo(ptr<SourceInfo> source_info, uint32_t p_line);
    DBGSourceInfo(ptr<SourceInfo> source_info, std::pair<int, int> p_pos,
                  uint32_t p_width);

    uint32_t width = 0;
    uint32_t line  = 0;
    std::pair<int, int> pos;

    std::string line_before;
    std::string line_str;
    std::string line_after;

  public:
    std::string get_pos_str() const;
    friend SrcObject;

    ptr<DBGSourceInfo> getDBGInfo() { return this; }

    /**
     * @brief Create a new instance  of dbg source info
     * using a token as reference.
     */
    static ptr<DBGSourceInfo> fromToken(ptr<SourceInfo> i, Token tk) {
        return new DBGSourceInfo(i, tk.get_pos(), tk.get_width());
    }
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
    ptr<DBGSourceInfo> dbg = nullptr;

  public:
    /// @brief Contruct a new DBGObject
    DBGObject();

    /// @return Debug information
    virtual ptr<DBGSourceInfo> getDBGInfo();
    /// @brief Set a new dbg object
    virtual void setDBGInfo(ptr<DBGSourceInfo> i);
};
} // namespace snowball

#endif // __SNOWBALL_DBG_INFO_H_