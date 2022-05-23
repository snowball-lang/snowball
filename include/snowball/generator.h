
#include "parser.h"

#include <memory>

#ifndef __SNOWBALL_GENERATOR_H_
#define __SNOWBALL_GENERATOR_H_

namespace snowball {

    class Generator {

        public:
            Generator(Parser* p_parser, SourceInfo* p_source_info) : _parser(p_parser) {
                _source_info = p_source_info;
            };

            void generate();

            ~Generator() {};

        private:
            Parser* _parser;
            SourceInfo* _source_info;
    };

}

#endif // __SNOWBALL_GENERATOR_H_
