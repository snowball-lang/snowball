
#include "lexer.h"
#include "types.h"
#include "parser.h"
#include "snowball.h"
#include "generator.h"
#include "enviroment.h"
#include "source_info.h"

#include "../exec/cli.h"

#include "vendor/toml.hpp"

#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include <llvm/ExecutionEngine/GenericValue.h>

#include <string>
#include <filesystem>

namespace fs = std::filesystem;
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

            static toml::parse_result get_config();

            int emit_binary(std::string p_output, bool p_pmessage = true);
            int emit_object(std::string p_output, bool p_pmessage = true);

            int emit_llvmir(std::string p_output, bool p_pmessage = true);
            void enable_tests() { _enabledTests = true; }
            void set_optimization(exec::Options::Optimization p_level) { _opt_level = p_level; }

            // Get
            SourceInfo* get_source_info() const { return _source_info; }
            Enviroment* get_enviroment() const { return _enviroment; }
            Generator* get_generator() const { return _generator; }
            llvm::Module* get_module() const { return _module.get(); }

            ~Compiler() {};

            std::vector<std::string> linked_libraries;

            llvm::LLVMContext global_context;
            std::shared_ptr<llvm::IRBuilder<>> builder;
            SNAPI* API;

            fs::path config_folder;

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

            exec::Options::Optimization _opt_level = exec::Options::Optimization::OPTIMIZE_O0;

            // methods
            void link_std_classes();
            void create_source_info();
            std::string prepare_module_name();

    };
}

#endif // __SNOWBALL_COMPILER_H_
