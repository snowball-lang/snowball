

#include "token.h"
#include "logger.h"
#include "source_info.h"

#ifndef __SNOWBALL_DBG_INFO_H_
#define __SNOWBALL_DBG_INFO_H_

namespace snowball {

    class DBGSourceInfo {
        public:
            SourceInfo* source_info;
            uint32_t line = 0;

            std::string line_before;
            std::string line_str;
            std::string line_after;

            std::pair<int, int> pos;
            uint32_t width = 0;

            DBGSourceInfo();
            DBGSourceInfo(SourceInfo* source_info, uint32_t p_line);
            DBGSourceInfo(SourceInfo* source_info, std::pair<int, int> p_pos, uint32_t p_width);
            std::string get_pos_str() const;
    };
}

#endif // __SNOWBALL_DBG_INFO_H_
