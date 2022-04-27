
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

            void initialize();
            void compile();

            ~Compiler() {};

        private:
            std::string _code;
            std::string _path;

            bool _initialized = false;
    };
}

#endif // __SNOWBALL_COMPILER_H_
