
#include <iostream>
#include <filesystem>

#include <llvm/Support/CommandLine.h>

#include "app/cli.h"
#include "compiler/compiler.h"
#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"
#include "compiler/reports/error.h"
#include "compiler/frontend/location.h"

#include "app/vendor/reky/src/reky.hpp"

namespace snowball {
namespace cli {
using namespace llvm;
using namespace utils;

#define REKY_MODE(x) \
  if (reky_mode == #x)

namespace {
void print_reky_help(CLI::Args& args) {
  CLI::hide_args();
  cl::SubCommand freeze("freeze", "Freeze the current project's dependencies");
  cl::SubCommand run("run", "Run the current project");
  cl::SubCommand dot("dot", "Export the dependency graph to a dot file");
  CLI::parse_args(args);
  cl::PrintHelpMessage();
  exit(EXIT_SUCCESS);
}
}

void CLI::make_reky(Ctx& ctx, Args& args) {
  cl::OptionCategory category("Reky Options");
  
  if (args.size() < 2) {
    Logger::error("Not enough arguments provided for reky");
    print_reky_help(args);
  }
  auto reky_mode = (std::string)args.at(1);
  REKY_MODE(freeze) {
    auto file = driver::get_workspace_path(ctx, driver::WorkSpaceType::Reky) / REKY_CACHE_FILE;
    std::ifstream ifs(file);
    if (!ifs.is_open()) {
      Logger::error(F("Could not open reky's cache file ({}). Try runing `reky run` and come back!", file.string()));
    }
    std::cout << ifs.rdbuf();
  } else REKY_MODE(run) {
    auto start = std::chrono::high_resolution_clock::now();
    Logger::status("Status", "Running reky for the current project");
    (void)Compiler::prepare_context(ctx);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    Logger::raw("\n");
    Logger::success(F("Reky ran successfully in {}ms", duration.count()));
  } else REKY_MODE(dot) {
    Logger::warn("The `dot` mode needs to execute `reky run` first");
    reky::RekyManager* manager;
    (void)Compiler::prepare_context(ctx, &manager);
    auto relative_path = driver::get_workspace_path(ctx, driver::WorkSpaceType::Reky) / "deps.dot";
    auto abs_path = std::filesystem::absolute(relative_path);
    std::ofstream ofs(abs_path);
    manager->export_dot(ofs);
    Logger::raw("\n");
    Logger::success(F("Exported the dependency graph to {}", abs_path.string()));
    delete manager;
  } else {
    Logger::error(F("Unknown reky mode: {}", reky_mode));
    print_reky_help(args);
  }
  exit(EXIT_SUCCESS);
}

}
}
