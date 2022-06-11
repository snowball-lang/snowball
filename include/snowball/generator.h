
#include "types.h"
#include "parser.h"
#include "enviroment.h"
#include "source_info.h"

#include <memory>

#include <llvm/IR/IRBuilder.h>

#ifndef __SNOWBALL_GENERATOR_H_
#define __SNOWBALL_GENERATOR_H_

namespace snowball {

    class Generator {

        public:
            Generator(Parser* p_parser,
                      Enviroment* p_enviroment,
                      SourceInfo* p_source_info,
                      llvm::IRBuilder<> p_builder,
                      llvm::Module* p_module,
                      SnowballBuildinTypes p_buildin_types)
                      :
                        _module(p_module),
                        _parser(p_parser),
                        _enviroment(p_enviroment),
                        _builder(std::move(p_builder)),
                        _buildin_types(p_buildin_types) {
                _source_info = p_source_info;
            };

            llvm::Value* generate(Node p_node);

            ~Generator() {};

        private:
            Parser* _parser;
            llvm::Module* _module;
            Enviroment* _enviroment;
            SourceInfo* _source_info;
            llvm::IRBuilder<> _builder;
            SnowballBuildinTypes _buildin_types;

            // methods
            llvm::Value* generate_function(Node p_node);
            llvm::Value* generate_const_value(Node p_node);
            llvm::Value* generate_variable_decl(Node p_node);
    };
}

#endif // __SNOWBALL_GENERATOR_H_
