
#include "../app/cli.h"
#include "SourceInfo.h"
#include "common.h"
#include "ir/module/MainModule.h"
#include "ir/module/Module.h"
#include "lexer/lexer.h"
#include "vendor/toml.hpp"
#include "./visitors/documentation/DocGen.h"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;
#ifndef __SNOWBALL_COMPILER_H_
#define __SNOWBALL_COMPILER_H_

#define SNOWBALL_PASS_EXECUTION_LIST \
  std::vector<Syntax::Analyzer> passes = { \
    Syntax::DefiniteAssigment(srcInfo)}; \
  for (auto pass : passes) \
    pass.run(ast); \

namespace snowball {

/**
 * @brief Global context for the compiler
 *
 * @details
 * This struct holds all the global context for the compiler. This is used to pass
 * information between different parts of the compiler.
 */
struct GlobalContext {
  bool isTest = false;
  bool isBench = false;
  bool withStd = true;
  bool withCXXStd = true;
  bool isThreaded = false;

  bool isDynamic = true;
  app::Options::Optimization opt = app::Options::Optimization::OPTIMIZE_O0;
};

/**
 * @brief snowball Compiler
 *
 * @details
 * Main class that handles all the compiling process of snowball. Note that it does not
 * actually compile, the llvm builder does the actual compilation. This class is more of
 * a wrapper around the whole compiler functionality.
 */
class Compiler {
  // variables
  std::string source;
  fs::path path;

  fs::path cwd;
  app::Options::Optimization opt_level;

  GlobalContext* globalContext;

  const SourceInfo* srcInfo = (snowball::SourceInfo*) nullptr;
  bool initialized = false;
  bool testsEnabled = false;
  bool benchmarkEnabled = false;

  std::shared_ptr<ir::MainModule> module;

public:
  Compiler(std::string p_code, std::string p_path);

  void initialize();
  void compile(bool verbose = true);

  void cleanup();

  static toml::parse_result getConfiguration();
  void enable_tests() { testsEnabled = true; }
  void enable_benchmark() { benchmarkEnabled = true; }

  // Get
  ~Compiler(){};

  std::vector<std::string> linkedLibraries;
  fs::path configFolder;

  struct BasicPackageInfo {
    std::string name;
    std::string version;
  };

  int emitBinary(std::string, bool = true);
  int emitObject(std::string, bool = true);
  int emitLLVMIr(std::string, bool = true);
  int emitASM(std::string, bool = true);
  int emitSnowballIr(std::string, bool = true);
  int emitDocs(std::string, std::string, BasicPackageInfo, bool = true);

  GlobalContext* getGlobalContext() { return globalContext; }

  void setOptimization(app::Options::Optimization o) {
    globalContext->opt = o;
    opt_level = o;
  }

private:
  // methods
  void createSourceInfo();
  void runPackageManager(bool silent);
};
} // namespace snowball

#endif // __SNOWBALL_COMPILER_H_
