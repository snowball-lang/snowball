#include "compiler.h"

#include "builder/llvm/LLVMBuilder.h"
#include "ir/module/MainModule.h"
#include "ir/module/Module.h"
#include "ld_args.h"
#include "lexer.h"
#include "parser/Parser.h"
#include "utils/utils.h"
#include "visitors/Analyzer.h"
#include "visitors/Transformer.h"
#include "visitors/TypeChecker.h"
#include "visitors/analyzers/DefinitveAssigment.h"

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
    _cwd = fs::current_path();
    _path = _path / p_path;
}

void Compiler::initialize() {
    _initialized = true;
    create_source_info();

    config_folder = _cwd / ".sn";
    if (!fs::exists(config_folder)) fs::create_directory(config_folder);
    if (!fs::exists(config_folder / "bin")) fs::create_directory(config_folder / "bin");
}

void Compiler::compile(bool verbose) {
    if (!_initialized) {
        throw SNError(Error::COMPILER_ERROR, "Compiler has not been initialized!");
    }
#if _SNOWBALL_TIMERS_DEBUG == 0
#define SHOW_STATUS(status)                                                            \
    if (!verbose) status;
#else
#define SHOW_STATUS(_)
#endif

    chdir(((fs::path)_path).parent_path().c_str());
    SHOW_STATUS(Logger::compiling(Logger::progress(0)));

    /* ignore_goto_errors() */ {
        SHOW_STATUS(Logger::compiling(Logger::progress(0.30)))
        auto lexer = new Lexer(_source_info);

#if _SNOWBALL_TIMERS_DEBUG
        std::vector<Token> tokens;
        DEBUG_TIMER("Lexer: %fs", utils::_timer([&] {
                        lexer->tokenize();
                        tokens = lexer->tokens;
                    }));
#else
        lexer->tokenize();
        auto tokens = lexer->tokens;
#endif

        if (tokens.size() != 0) {
            SHOW_STATUS(Logger::compiling(Logger::progress(0.50)))

            auto parser = new parser::Parser(tokens, _source_info);
#if _SNOWBALL_TIMERS_DEBUG
            parser::Parser::NodeVec ast;
            DEBUG_TIMER("Parser: %fs", utils::_timer([&] { ast = parser->parse(); }));
#else
            auto ast = parser->parse();
#endif

            SHOW_STATUS(Logger::compiling(Logger::progress(0.55)))
            auto mainModule = std::make_shared<ir::MainModule>();

            mainModule->setSourceInfo(_source_info);

            auto simplifier = new Syntax::Transformer(
                mainModule->downcasted_shared_from_this<ir::Module>(), _source_info);
#if _SNOWBALL_TIMERS_DEBUG
            DEBUG_TIMER("Simplifier: %fs",
                        utils::_timer([&] { simplifier->visit(ast); }));
#else
            simplifier->visit(ast);
#endif

            SHOW_STATUS(Logger::compiling(Logger::progress(0.60)))
            std::vector<Syntax::Analyzer *> passes = {
                new Syntax::DefiniteAssigment(_source_info)};

#if _SNOWBALL_TIMERS_DEBUG
            DEBUG_TIMER("Passes: %fs", utils::_timer([&] {
                            for (auto pass : passes) pass->run(ast);
                        }));
#else
            for (auto pass : passes) {
                pass->run(ast);
            }
#endif

            SHOW_STATUS(Logger::compiling(Logger::progress(0.70)))

            auto typeChecker = new codegen::TypeChecker(mainModule);

#if _SNOWBALL_TIMERS_DEBUG
            DEBUG_TIMER("TypeChecker: %fs",
                        utils::_timer([&] { typeChecker->codegen(); }));
#else
            typeChecker->codegen();
#endif

            SHOW_STATUS(Logger::compiling(Logger::progress(0.80)))

            mainModule->setModules(simplifier->getModules());
            module = mainModule;

            SHOW_STATUS(Logger::compiling(Logger::progress(0.90)))

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

void Compiler::cleanup() {}

int Compiler::emit_object(std::string out, bool log) {
    auto builder = new codegen::LLVMBuilder(module);
    builder->codegen();
    builder->optimizeModule(opt_level);

#if _SNOWBALL_BYTECODE_DEBUG
    builder->dump();
#endif

    return builder->emitObjectFile(out, log);
}

int Compiler::emit_binary(std::string out, bool log) {
    std::string objfile = Logger::format("%s.so", out.c_str());
    DEBUG_CODEGEN("Emitting object file... (%s)", objfile.c_str());
    int objstatus = emit_object(objfile, false);
    if (objstatus != EXIT_SUCCESS) return objstatus;

    // object file written, now invoke llc
    // int ldstatus = execl(LD_PATH, "", NULL);
    std::string ldcommand;
    std::string p_input = Logger::format("%s.so", out.c_str());
    std::vector<std::string> ld_args = LD_ARGS();

    for (int i = 0; i < ld_args.size(); i++) {
        ldcommand += ld_args[i];
        ldcommand += " ";
    }
    for (int i = 0; i < linked_libraries.size(); i++) {
        ldcommand += "-l:" + linked_libraries[i] + " ";
        DEBUG_CODEGEN("Linking library: %s", linked_libraries[i].c_str());
    }

#if _SNOWBALL_CODEGEN_DEBUG
    ldcommand += "--verbose ";
#endif

    ldcommand += " -o";
    ldcommand += out;

    DEBUG_CODEGEN("Invoking linker (" LD_PATH " with stdlib at " STATICLIB_DIR ")");
    DEBUG_CODEGEN("Linker command: %s", ldcommand.c_str());

    int ldstatus = system(ldcommand.c_str());
    if (ldstatus) {
        remove(objfile.c_str());
        throw SNError(
            LINKER_ERR,
            Logger::format("Linking with " LD_PATH " failed with code %d", ldstatus));
    }

    if (log)
        Logger::success(Logger::format("Snowball project successfully compiled! 🥳",
                                       BGRN, RESET, out.c_str()));

    // clean up
    DEBUG_CODEGEN("Cleaning up object file... (%s)", objfile.c_str());
    remove(objfile.c_str());

    return EXIT_SUCCESS;
}

void Compiler::create_source_info() {
    SourceInfo *source_info = new SourceInfo(_code, _path);
    _source_info = source_info;
}
} // namespace snowball
