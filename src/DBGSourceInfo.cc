
#include "DBGSourceInfo.h"

#include "SourcedObject.h"

#include <sstream>
#include <string>

namespace snowball {
DBGSourceInfo::DBGSourceInfo(ptr<SourceInfo> p_source_info, uint32_t p_line)
    : SrcObject(p_source_info), line(p_line) {}

DBGSourceInfo::DBGSourceInfo(ptr<SourceInfo> p_source_info,
                             std::pair<int, int> p_pos, uint32_t p_width)
    : pos(p_pos), line((uint32_t)p_pos.first), width(p_width),
      SrcObject(p_source_info) {
    uint64_t cur_line  = 1;
    const auto& source = m_srci->getSource();

    for (auto c : source) {
        if (c == '\n') {
            if (cur_line >= line + 2) break;
            cur_line++;
        } else if (cur_line == line - 1) {
            line_before += c;
        } else if (cur_line == line) {
            line_str += c;
        } else if (cur_line == line + 1) {
            line_after += c;
        }
    }
}

std::string DBGSourceInfo::get_pos_str() const {
    // var x = blabla;
    //         ^^^^^^

    std::stringstream ss_pos;
    size_t cur_col = 0;
    bool done      = false;
    for (size_t i = 0; i < line_str.size(); i++) {
        cur_col++;
        if (cur_col == pos.second) {
            for (uint32_t i = 0; i < width; i++) {
                ss_pos << '~';
            }
            done = true;
            break;
        } else if (line_str[i] != '\t') {
            ss_pos << ' ';
        } else {
            ss_pos << '\t';
        }
    }
    if (!done) ss_pos << '^';

    auto ret = ss_pos.str();
    return ret;
}

DBGObject::DBGObject() { /* noop */
}
ptr<DBGSourceInfo> DBGObject::getDBGInfo() { return dbg; }
void DBGObject::setDBGInfo(ptr<DBGSourceInfo> i) {
    dbg = i;
    // auto _src = i->getSourceInfo();
}
} // namespace snowball