
#include "app/cli.h"
#include "compiler.h"
#include "constants.h"
#include "errors.h"
#include "utils/utils.h"
#include "vendor/toml.hpp"

#include <chrono>
#include <filesystem>
#include <string>

using namespace std::chrono;
namespace fs = std::filesystem;

#ifndef __SNOWBALL_EXEC_BUILD_CMD_H_
#define __SNOWBALL_EXEC_BUILD_CMD_H_

namespace snowball {
namespace app {
namespace commands {
int build(app::Options::BuildOptions p_opts) {
    std::string filename = p_opts.file;
    std::string package_name = "<single file>";
    std::string package_version = "<unknown version>";

    if (p_opts.file.empty()) {
        toml::parse_result parsed_config = Compiler::get_config();
        filename = p_opts.file.empty()
                ? (std::string)(parsed_config["package"]["main"].value_or<std::string>(
                          (fs::current_path() / "src" / "main.sn")))
                : p_opts.file;
        package_name = (std::string)(
                parsed_config["package"]["name"].value_or<std::string>("<anonnimus>"));
        package_version = parsed_config["package"]["version"].value_or<std::string>("<unknown>");
    }

    std::ifstream ifs(filename);
    if (ifs.fail()) {
        SNError(Error::IO_ERROR,
                FMT("Package main file not found in snowball "
                    "project! \n\t(searching for: '%s')",
                    filename.c_str()))
                .print_error();
        return EXIT_FAILURE;
    }

    std::string build_type;
    if (p_opts.is_test) {
        build_type = "test";
    } else if (p_opts.emit_type == Options::EmitType::EXECUTABLE) {
        build_type = "executable";
    } else if (p_opts.emit_type == Options::EmitType::LLVM_IR) {
        build_type = "llvm-ir";
    } else if (p_opts.emit_type == Options::EmitType::OBJECT) {
        build_type = "library";
    } else {
        throw SNError(BUG, FMT("Unhandled emit type for build process ('%i')", p_opts.emit_type));
    }

    Logger::message("Compiling",
                    FMT("%s v%s [%s]",
                        package_name.c_str(),
                        package_version.c_str(),
                        (build_type.c_str())));

    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    // TODO: check for output
    std::string output = p_opts.emit_type == app::Options::EmitType::LLVM_IR
            ? _SNOWBALL_LLIR_OUT_DEFAULT
            : _SNOWBALL_OUT_DEFAULT;

    Compiler* compiler = new Compiler(content, filename);
    compiler->initialize();
    compiler->set_optimization(p_opts.opt);

    if (p_opts.is_test) { compiler->enable_tests(); }

    auto start = high_resolution_clock::now();

    // TODO: false if --no-output is passed
    compiler->compile(p_opts.silent);
    auto stop = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<milliseconds>(stop - start).count();

    Logger::message("Finished", FMT("build target(s) in %ims", duration));
    Logger::log("");

    int status;
    if (p_opts.emit_type == app::Options::EmitType::OBJECT) {
        status = compiler->emit_object(output);
    } else if (p_opts.emit_type == app::Options::EmitType::LLVM_IR) {
        status = compiler->emit_llvmir(output);
    } else {
        status = compiler->emit_binary(output);
    }

    compiler->cleanup();

    return status;
}
} // namespace commands
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_EXEC_BUILD_CMD_H_