
#include <string>

#ifndef __SNOWBALL_COMPILER_H_
#define __SNOWBALL_COMPILER_H_

namespace snowball {

    class Compiler {

        public:
            Compiler(std::string p_code, std::string p_path);
            Compiler(const char* p_code, std::string p_path);
            Compiler(std::string p_code, const char* p_path);
            Compiler(const char* p_code, const char* p_path);

            ~Compiler() {};

        private:
            std::string _code;
            std::string _path;
    };
}

#endif // __SNOWBALL_COMPILER_H_
