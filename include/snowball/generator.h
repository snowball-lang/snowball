
#include "parser.h"
#include "source_info.h"

#include <memory>

#ifndef __SNOWBALL_GENERATOR_H_
#define __SNOWBALL_GENERATOR_H_

namespace snowball {

    class Generator {

        public:
            Generator(Parser* p_parser, Enviroment* p_enviroment, SourceInfo* p_source_info) : _parser(p_parser), _enviroment(p_enviroment) {
                _source_info = p_source_info;
            };

            void generate();

            ~Generator() {};

        private:
            Parser* _parser;
            SourceInfo* _source_info;
            Enviroment* _enviroment;
    };

}

#endif // __SNOWBALL_GENERATOR_H_
