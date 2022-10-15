
#include <string>

#ifndef __SNOWBALL_SOURCE_INFO_H_
#define __SNOWBALL_SOURCE_INFO_H_

namespace snowball {

    class SourceInfo {

        public:
            SourceInfo(std::string p_code = "", std::string p_path = "<anonimus>") {
                _code = p_code;
                _path = p_path;

                source_length = _code.size();
            };

            std::string get_source() { return _code; };
            std::string get_path() { return _path; };

            ~SourceInfo() {};

            int source_length;

        private:
            std::string _code;
            std::string _path;
    };
}

#endif // __SNOWBALL_SOURCE_INFO_H_
