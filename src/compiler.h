
#include "../app/cli.h"
#include "common.h"
#include "ir/module/MainModule.h"
#include "ir/module/Module.h"
#include "lexer/lexer.h"
#include "SourceInfo.h"
#include "vendor/toml.hpp"

#include <filesystem>
#include <string>

namespace fs = std::filesystem;
#ifndef __SNOWBALL_COMPILER_H_
#define __SNOWBALL_COMPILER_H_

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
  bool withStd = true;
  bool withCXXStd = true;
  bool isThreaded = false;

  bool isDynamic = true;
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

  SourceInfo* srcInfo;
  bool initialized = false;
  bool testsEnabled = false;

  std::shared_ptr<ir::MainModule> module;

public:
  Compiler(std::string p_code, std::string p_path);

  void initialize();
  void compile(bool verbose = true);

  void cleanup();

  static toml::parse_result getConfiguration();
  void enable_tests() { testsEnabled = true; }

  // Get
  ~Compiler(){};

  std::vector<std::string> linkedLibraries;
  fs::path configFolder;

  // TODO
  int emitBinary(std::string, bool = true);
  int emitObject(std::string, bool = true);
  int emitLLVMIr(std::string, bool = true);
  int emitASM(std::string, bool = true);

  void setOptimization(app::Options::Optimization o) { opt_level = o; }

private:
  // methods
  void createSourceInfo();
};
} // namespace snowball

#endif // __SNOWBALL_COMPILER_H_
