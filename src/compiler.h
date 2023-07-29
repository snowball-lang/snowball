
#include "../app/cli.h"
#include "common.h"
#include "ir/module/MainModule.h"
#include "ir/module/Module.h"
#include "lexer/lexer.h"
#include "source_info.h"
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
    std::string _code;
    fs::path _path;

    fs::path _cwd;
    app::Options::Optimization opt_level;

    GlobalContext* _globalContext;

    SourceInfo* _source_info;
    bool _initialized = false;
    bool _enabledTests = false;

    std::shared_ptr<ir::MainModule> module;

  public:
    Compiler(std::string p_code, std::string p_path);

    void initialize();
    void compile(bool verbose = true);

    void cleanup();

    static toml::parse_result get_config();
    void enable_tests() { _enabledTests = true; }

    // Get
    SourceInfo* getSource_info() const { return _source_info; }

    ~Compiler(){};

    std::vector<std::string> linked_libraries;
    fs::path config_folder;

    // TODO
    int emit_binary(std::string, bool = true);
    int emit_object(std::string, bool = true);
    int emit_llvmir(std::string, bool = true);
    int emit_assembly(std::string, bool = true);

    void set_optimization(app::Options::Optimization o) { opt_level = o; }

  private:
    // methods
    void create_source_info();
};
} // namespace snowball

#endif // __SNOWBALL_COMPILER_H_
