
#include "dbg_info.h"

#include <string>
#include <sstream>

namespace snowball {
    DBGSourceInfo::DBGSourceInfo() {}
    DBGSourceInfo::DBGSourceInfo(SourceInfo* p_source_info, uint32_t p_line) : source_info(p_source_info), line(p_line) {}
    DBGSourceInfo::DBGSourceInfo(SourceInfo* p_source_info, std::pair<int, int> p_pos, uint32_t p_width)
        : pos(p_pos), line((uint32_t)p_pos.first), width(p_width), source_info(p_source_info) {

        uint64_t cur_line = 1;
        std::stringstream ss_src(((const std::string&)source_info->get_source()).c_str());

        char c;
        while (ss_src >> c) {
            printf("L: %c\n", c);
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
        bool done = false;
        for (size_t i = 0; i < line_str.size(); i++) {
            cur_col++;
            if (cur_col == pos.second) {
                for (uint32_t i = 0; i < width; i++) {
                    ss_pos << '^';
                }
                done = true;
                break;
            } else if (line_str[i] != '\t') {
                ss_pos << '_';
            } else {
                ss_pos << '\t';
            }
        }
        if (!done) ss_pos << '^';
        return ss_pos.str();
    }
}