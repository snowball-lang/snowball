
#include <string>

#ifndef __SNOWBALL_SOURCE_INFO_H_
#define __SNOWBALL_SOURCE_INFO_H_

namespace snowball {

    class SourceInfo {

        public:
            SourceInfo(std::string p_code = "", std::string p_path = "<anonymous>") {
                _code = p_code;
                _path = p_path;
            };

            std::string get_source() { return _code; };
            std::string get_path() { return _path; };

            ~SourceInfo() {};

        private:
            std::string _code;
            std::string _path;
    };
}

#endif // __SNOWBALL_SOURCE_INFO_H_
