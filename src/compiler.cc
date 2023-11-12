#include "compiler.h"

#include "builder/linker/Linker.h"
#include "builder/llvm/LLVMBuilder.h"
#include "builder/sn-ir/SnowballIREmitter.h"
#include "ir/module/MainModule.h"
#include "ir/module/Module.h"
#include "lexer/lexer.h"
#include "parser/Parser.h"
#include "utils/utils.h"
#include "visitors/Analyzer.h"
#include "visitors/Transformer.h"
#include "visitors/TypeChecker.h"
#include "visitors/analyzers/DefinitveAssigment.h"
#include "visitors/documentation/DocGen.h"

#include <filesystem>
#include <fstream>
#include <regex>
#include <stdio.h>
#include <string>
#include <unistd.h>

namespace fs = std::filesystem;

namespace snowball {
Compiler::Compiler(std::string p_code, std::string p_path) {
  source = p_code;
  cwd = fs::current_path();
  path = path / p_path;
  srcInfo = nullptr;
}

void Compiler::initialize() {
  initialized = true;
  createSourceInfo();

  globalContext = new GlobalContext();
  globalContext->isTest = testsEnabled;
  globalContext->isBench = benchmarkEnabled;

  configFolder = cwd / ".sn";
  if (!fs::exists(configFolder)) fs::create_directory(configFolder);
  if (!fs::exists(configFolder / "bin")) fs::create_directory(configFolder / "bin");
  if (!fs::exists(configFolder / "docs")) fs::create_directory(configFolder / "docs");
}

void Compiler::compile(bool silent) {
  if (!initialized) { throw SNError(Error::COMPILER_ERROR, "Compiler has not been initialized!"); }
#if _SNOWBALL_TIMERS_DEBUG == 0
#define SHOW_STATUS(status)                                                                                            \
  if (!silent) status;
#else
#define SHOW_STATUS(_)
#endif

  chdir(((fs::path) path).parent_path().c_str());
  SHOW_STATUS(Logger::compiling(Logger::progress(0)));

  /* ignore_goto_errors() */ {
    SHOW_STATUS(Logger::compiling(Logger::progress(0.30)))
    auto lexer = new Lexer(srcInfo);

#if _SNOWBALL_TIMERS_DEBUG
    DEBUG_TIMER("Lexer: %fs", utils::_timer([&] { lexer->tokenize(); }));
#else
    lexer->tokenize();
#endif
    auto tokens = lexer->tokens;
    if (tokens.size() != 0) {
      SHOW_STATUS(Logger::compiling(Logger::progress(0.50)))

      auto parser = new parser::Parser(tokens, srcInfo);
#if _SNOWBALL_TIMERS_DEBUG
      parser::Parser::NodeVec ast;
      DEBUG_TIMER("Parser: %fs", utils::_timer([&] { ast = parser->parse(); }));
#else
      auto ast = parser->parse();
#endif

      SHOW_STATUS(Logger::compiling(Logger::progress(0.55)))
      auto mainModule = std::make_shared<ir::MainModule>();

      mainModule->setSourceInfo(srcInfo);

      auto simplifier = new Syntax::Transformer(
              mainModule->downcasted_shared_from_this<ir::Module>(), srcInfo, testsEnabled, benchmarkEnabled
      );
#if _SNOWBALL_TIMERS_DEBUG
      DEBUG_TIMER("Simplifier: %fs", utils::_timer([&] { simplifier->visitGlobal(ast); }));
#else
      ([&] { simplifier->visitGlobal(ast); })();
      // TODO: why does this segfault if not called from a function?
//      simplifier->visitGlobal(ast);
#endif

      SHOW_STATUS(Logger::compiling(Logger::progress(0.70)))
      std::vector<Syntax::Analyzer*> passes = {new Syntax::DefiniteAssigment(srcInfo)};

      mainModule->setModules(simplifier->getModules());
      module = mainModule;

#if _SNOWBALL_TIMERS_DEBUG
      DEBUG_TIMER("Passes: %fs", utils::_timer([&] {
                    for (auto pass : passes) pass->run(ast);
                  }));
#else
      for (auto pass : passes) { pass->run(ast); }
#endif

      SHOW_STATUS(Logger::compiling(Logger::progress(0.90)))

      auto typeCheckModules = mainModule->getModules();
      typeCheckModules.push_back(mainModule);
      for (auto module : typeCheckModules) {
        auto typeChecker = new codegen::TypeChecker(module);
#if _SNOWBALL_TIMERS_DEBUG
        DEBUG_TIMER("TypeChecker: %fs (%s)", utils::_timer([&] { typeChecker->codegen(); }), module->getName().c_str());
#else
        typeChecker->codegen();
#endif
      }

      SHOW_STATUS(Logger::compiling(Logger::progress(1)))

      SHOW_STATUS(Logger::reset_status())
    }

    chdir(cwd.c_str());
  }
}

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

int Compiler::emitDocs(std::string folder, std::string baseURL, bool silent) {
  auto path = cwd / folder;
  auto outputFolder = configFolder / "docs";

  fs::remove_all(outputFolder);

  for (const auto& dirEntry : recursive_directory_iterator(path)) {
    if (utils::endsWith(dirEntry.path().string(), ".sn")) {

      auto relative = dirEntry.path().lexically_relative(cwd).lexically_normal();
      size_t lastindex = relative.string().find_last_of("."); 
      relative = relative.string().substr(0, lastindex); 

      std::string moduleName = relative.string();
      utils::replaceAll(moduleName, "/", "::");

      if (!silent)
        Logger::message("Generating", " " + relative.string() + ".sn");

      std::ifstream ifs(dirEntry.path().string());
      std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

      srcInfo = new SourceInfo(content, dirEntry.path().string());
      auto lexer = new Lexer(srcInfo);
      lexer->tokenize();
      auto tokens = lexer->tokens;
      if (tokens.size() != 0) {
        auto parser = new parser::Parser(tokens, srcInfo, true);
        auto ast = parser->parse();
        Syntax::DocGenContext context {
          .currentModule = moduleName,
          .currentModulePath = relative.string(),

          .baseURL = baseURL,
        };
        auto docGen = new Syntax::DocGen(context);
        docGen->run(ast);
        auto result = docGen->getResult();

        for (auto& page : result.pages) {
          auto htmlPath = outputFolder / page.path;
          if (!fs::exists(htmlPath.parent_path())) fs::create_directories(htmlPath.parent_path());

          std::ofstream file(htmlPath);
          file << page.html;
          file.close();
        }
      }
    }
  }
    
  return EXIT_SUCCESS;
}
#undef SHOW_STATUS

toml::parse_result Compiler::getConfiguration() {
  std::string name = fs::current_path() / "sn.toml";
  std::ifstream f(name.c_str());
  if (f.good()) { return toml::parse_file(name); }

  throw SNError(
          Error::IO_ERROR,
          FMT("Project configuration not found (%s)\n%shelp%s: try "
              "runing 'snowball init --cfg'",
              name.c_str(),
              BGRN,
              RESET)
  );
}

void Compiler::cleanup() { }

int Compiler::emitObject(std::string out, bool log) {
  auto builder = new codegen::LLVMBuilder(module, opt_level, testsEnabled, benchmarkEnabled);
  builder->codegen();
  builder->optimizeModule();

#if _SNOWBALL_BYTECODE_DEBUG
  builder->dump();
#endif

  return builder->emitObjectFile(out, log);
}

int Compiler::emitLLVMIr(std::string p_output, bool p_pmessage) {
  auto builder = new codegen::LLVMBuilder(module, opt_level, testsEnabled, benchmarkEnabled);
  builder->codegen();
  builder->optimizeModule();

  std::error_code EC;
  llvm::raw_fd_ostream dest(p_output, EC);
  if (EC) throw SNError(Error::IO_ERROR, Logger::format("Could not open file: %s", EC.message().c_str()));
  builder->print(dest);
  if (p_pmessage) Logger::success("Snowball project transpiled to llvm IR code! 🎉\n");
  return EXIT_SUCCESS;
}

int Compiler::emitASM(std::string p_output, bool p_pmessage) {
  auto builder = new codegen::LLVMBuilder(module, opt_level, testsEnabled, benchmarkEnabled);
  builder->codegen();
  builder->optimizeModule();

  auto res = builder->emitObjectFile(p_output, false, false);
  if (p_pmessage) Logger::success("Snowball project transpiled to assembly code! 🎉\n");
  return res;
}

int Compiler::emitBinary(std::string out, bool log) {
  std::vector<std::string> extraLinkerArgs = {};
  auto objfile = linker::Linker::getSharedLibraryName(out);
  DEBUG_CODEGEN("Emitting object file... (%s)", objfile.c_str());
  int objstatus = emitObject(objfile, false);
  if (objstatus != EXIT_SUCCESS) return objstatus;
  auto linker = linker::Linker(globalContext, LD_PATH);
  for (auto lib : linkedLibraries) { linker.addLibrary(lib); }
  // TODO: add user-defined extra ld args
  linker.link(objfile, out, extraLinkerArgs);
  if (log) Logger::success(Logger::format("Snowball project successfully compiled! 🥳", BGRN, RESET, out.c_str()));

  // clean up
  DEBUG_CODEGEN("Cleaning up object file... (%s)", objfile.c_str());
  remove(objfile.c_str());
  return EXIT_SUCCESS;
}

int Compiler::emitSnowballIr(std::string p_output, bool p_pmessage) {
  auto builder = new codegen::SnowballIREmitter(module);
  builder->codegen(p_output);
  if (p_pmessage) Logger::success("Snowball project transpiled to snowball IR code! 🎉\n");
  return EXIT_SUCCESS;
}

void Compiler::createSourceInfo() { srcInfo = new SourceInfo(source, path); }
} // namespace snowball
