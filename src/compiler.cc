#include "compiler.h"

#include "builder/llvm/LLVMBuilder.h"
#include "ir/module/MainModule.h"
#include "ir/module/Module.h"
#include "ld_args.h"
#include "lexer.h"
#include "parser/Parser.h"
#include "utils/utils.h"
#include "visitors/Transformer.h"
#include "visitors/TypeChecker.h"

#include <filesystem>
#include <fstream>
#include <regex>
#include <stdio.h>
#include <string>
#include <unistd.h>

namespace fs = std::filesystem;
#define SN_MODULE_NAME "llvm_snowball_compile_mod_"

namespace snowball {
Compiler::Compiler(std::string p_code, std::string p_path) {
    _code = p_code;
    _path = fs::current_path() / p_path;

    _cwd = get_current_dir_name();
}

void Compiler::initialize() {
    _initialized = true;
    create_source_info();

    config_folder = fs::current_path() / ".sn";
    if (!fs::exists(config_folder)) fs::create_directory(config_folder);
    if (!fs::exists(config_folder / "bin"))
        fs::create_directory(config_folder / "bin");
}

void Compiler::compile(bool verbose) {
    if (!_initialized) {
        throw SNError(Error::COMPILER_ERROR,
                      "Compiler has not been initialized!");
    }

#define SHOW_STATUS(status)                                                    \
    if (verbose) status;

    chdir(((fs::path)_path).parent_path().c_str());
    SHOW_STATUS(Logger::compiling(Logger::progress(0)));

    /* ignore_goto_errors() */ {
        SHOW_STATUS(Logger::compiling(Logger::progress(0.30)))
        auto lexer = new Lexer(_source_info);
        lexer->tokenize();

        if (lexer->tokens.size() != 0) {
            SHOW_STATUS(Logger::compiling(Logger::progress(0.50)))

            auto parser = new parser::Parser(lexer->tokens, _source_info);
            auto ast    = parser->parse();

            SHOW_STATUS(Logger::compiling(Logger::progress(0.55)))
            auto mainModule = std::make_shared<ir::MainModule>();

            mainModule->setSourceInfo(_source_info);

            auto simplifier = new Syntax::Transformer(
                mainModule->downcasted_shared_from_this<ir::Module>(),
                _source_info);
            simplifier->visit(ast);

            SHOW_STATUS(Logger::compiling(Logger::progress(0.60)))

            auto typeChecker = new codegen::TypeChecker(mainModule);
            typeChecker->codegen();

            SHOW_STATUS(Logger::compiling(Logger::progress(0.70)))

            mainModule->setModules(simplifier->getModules());
            module = mainModule;

            SHOW_STATUS(Logger::compiling(Logger::progress(0.80)))
            SHOW_STATUS(Logger::compiling(Logger::progress(0.85)))

            SHOW_STATUS(Logger::reset_status())
        }

        chdir(_cwd.c_str());
    }

#undef SHOW_STATUS
}

toml::parse_result Compiler::get_config() {
    std::string name = fs::current_path() / "sn.toml";
    std::ifstream f(name.c_str());
    if (f.good()) {
        return toml::parse_file(name);
    }

    throw SNError(Error::IO_ERROR,
                  FMT("Project configuration not found (%s)\n%shelp%s: try "
                      "runing 'snowball init --cfg'",
                      name.c_str(), BGRN, RESET));
}

void Compiler::cleanup() {
#if _SNOWBALL_SYMTABLE_DEBUG
    PRINT_LINE("Enviroment:")
    PRINT_LINE(LINE_SEPARATOR)

    // TODO:
    PRINT_LINE(LINE_SEPARATOR)
#endif
}

int Compiler::emit_binary(std::string out, bool log) {
    auto builder = new codegen::LLVMBuilder(module);
    builder->codegen();

#if _SNOWBALL_BYTECODE_DEBUG
    builder->dump();
#endif

    return EXIT_SUCCESS;
}

void Compiler::create_source_info() {
    SourceInfo *source_info = new SourceInfo(_code, _path);
    _source_info            = source_info;
}
} // namespace snowball
