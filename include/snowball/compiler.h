
#include <string>


#include "lexer.h"
#include "types.h"
#include "parser.h"
#include "snowball.h"
#include "generator.h"
#include "enviroment.h"
#include "source_info.h"

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include <llvm/ExecutionEngine/GenericValue.h>


#ifndef __SNOWBALL_COMPILER_H_
#define __SNOWBALL_COMPILER_H_

namespace snowball {
    class SNAPI;
    class Generator;

    class Compiler {

        public:
            Compiler(std::string p_code, std::string p_path);

            void initialize();
            void compile(bool verbose = true);

            void cleanup();
            void optimize();

            int emit_binary(std::string p_output);
            int emit_object(std::string p_output, bool p_for_executable = false);

            int execute();
            void enable_tests() { _enabledTests = true; }

            // Get
            SourceInfo* get_source_info() { return _source_info; }
            Enviroment* get_enviroment() { return _enviroment; }
            llvm::Module* get_module() { return _module.get(); }

            ~Compiler() {};

            std::vector<std::string> linked_libraries;

            llvm::LLVMContext global_context;
            std::shared_ptr<llvm::IRBuilder<>> builder;
            SNAPI* API;

        private:
            // llvm
            std::unique_ptr<llvm::Module> _module;

            // variables
            std::string _code;
            std::string _path;

            SourceInfo* _source_info;
            bool _initialized = false;
            bool _enabledTests = false;

            llvm::TargetMachine* _target_machine;

            Lexer* _lexer;
            Parser* _parser;
            Generator* _generator;

            Enviroment* _enviroment;

            // methods
            void link_std_classes();
            void create_source_info();
            std::string prepare_module_name();

    };
}

#endif // __SNOWBALL_COMPILER_H_
