
#include "cli.h"
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
  std::string package_name = "file";
  std::string package_version = "<unknown version>";
  //bool isStaticLib = false; // TODO: implement static library support

  if (p_opts.file.empty()) {
    toml::parse_result parsed_config = Compiler::getConfiguration();
    filename = parsed_config["package"]["main"].value_or<std::string>((fs::current_path() / "src" / "main.sn"));
    package_name = (std::string)(parsed_config["package"]["name"].value_or<std::string>("<anonnimus>"));
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
  if (p_opts.is_test) { build_type = "test + "; }

  if (p_opts.emit_type == Options::EmitType::EXECUTABLE) {
    build_type += "executable";
  } else if (p_opts.emit_type == Options::EmitType::SNOWBALL_IR) {
    build_type += "snowball-ir";
  } else if (p_opts.emit_type == Options::EmitType::LLVM_IR) {
    build_type += "llvm-ir";
  } else if (p_opts.emit_type == Options::EmitType::OBJECT) {
    build_type += "library";
  } else if (p_opts.emit_type == Options::EmitType::ASSEMBLY) {
    build_type += "assembly";
  } else {
    throw SNError(BUG, FMT("Unhandled emit type for build process ('%i')", p_opts.emit_type));
  }

  if (p_opts.opt == Options::Optimization::OPTIMIZE_O0) {
    build_type += " + debug";
  } else {
    build_type += " + optimized";
  }

  if (!p_opts.silent)
    Logger::message(
            "Project",
            FMT("%s v%s [%s%s%s]", package_name.c_str(), package_version.c_str(), BOLD, build_type.c_str(), RESET)
    );

  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  // TODO: check for output
  Compiler* compiler = new Compiler(content, filename);
  compiler->initialize();
  std::string output = _SNOWBALL_OUT_DEFAULT(package_name, p_opts.emit_type, !compiler->getGlobalContext().isDynamic);
  if (!p_opts.output.empty()) { output = p_opts.output; }
  compiler->setOptimization(p_opts.opt);
  if (p_opts.is_test) { compiler->enable_tests(); }

  auto start = high_resolution_clock::now();
  compiler->enamblePackageManager(p_opts.file.empty());
  compiler->compile(p_opts.no_progress || p_opts.silent);
  auto stop = high_resolution_clock::now();

  // Get duration. Substart timepoints to
  // get duration. To cast it to proper unit
  // use duration cast method
  auto duration = duration_cast<milliseconds>(stop - start).count();

  if (!p_opts.silent) {
    Logger::message("Finished", FMT("build target(s) in %s%ims%s", BOLD, duration, RESET));
    Logger::message("Generating", FMT("Generating output at `%s%s%s`", BOLD, output.c_str(), RESET));
    Logger::log("");
  }

  int status;
  if (p_opts.emit_type == app::Options::EmitType::OBJECT) {
    status = compiler->emitObject(output, !p_opts.silent);
  } else if (p_opts.emit_type == app::Options::EmitType::SNOWBALL_IR) {
    status = compiler->emitSnowballIr(output, !p_opts.silent);
  } else if (p_opts.emit_type == app::Options::EmitType::LLVM_IR) {
    status = compiler->emitLLVMIr(output, !p_opts.silent);
  } else if (p_opts.emit_type == app::Options::EmitType::ASSEMBLY) {
    status = compiler->emitASM(output, !p_opts.silent);
  } else {
    status = compiler->emitBinary(output, !p_opts.silent);
  }

  compiler->cleanup();

  return status;
}
} // namespace commands
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_EXEC_BUILD_CMD_H_
