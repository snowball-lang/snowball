
#include "cli.h"
#include "compiler.h"
#include "constants.h"
#include "ast/errors/error.h"
#include "utils/utils.h"
#include "vendor/toml.hpp"

#include <chrono>
#include <filesystem>
#include <string>

using namespace std::chrono;
namespace fs = std::filesystem;

#ifndef __SNOWBALL_DOC_BUILD_CMD_H_
#define __SNOWBALL_DOC_BUILD_CMD_H_

namespace snowball {
namespace app {
namespace commands {
int docgen(app::Options::DocsOptions p_opts) {
  std::string package_name = "file";
  std::string package_version = "<unknown version>";
  toml::parse_result parsed_config = Compiler::getConfiguration();
  package_name = (std::string)(parsed_config["package"]["name"].value_or<std::string>("<anonnimus>"));
  package_version = parsed_config["package"]["version"].value_or<std::string>("<unknown>");
  auto folder = parsed_config["documentation"]["entry"].value_or<std::string>("./src");
  auto baseURL = p_opts.base;
  if (baseURL.empty()) baseURL = parsed_config["documentation"]["base"].value_or<std::string>("/");
  if (package_name == "<anonnimus>") {
    Syntax::E<CONFIGURATION_ERROR>("No package name found in configuration file!\nPlease add a package name to your configuration file.\nPackage names are required for documentation generation.");
  }
  if (!p_opts.silent)
    Logger::message(
      "Project",
      FMT("%s v%s [%sdocumentation%s]", package_name.c_str(), package_version.c_str(), BOLD, RESET)
    );
  // TODO: check for output
  auto compiler = new Compiler("<invalid>", "<invalid>");
  compiler->initialize();
  auto start = high_resolution_clock::now();
  int status = compiler->emitDocs(folder, baseURL, {.name = package_name, .version = package_version}, p_opts.silent);
  auto stop = high_resolution_clock::now();
  // Get duration. Substart timepoints to
  // get duration. To cast it to proper unit
  // use duration cast method
  auto duration = duration_cast<milliseconds>(stop - start).count();
  if (!p_opts.silent) {
    Logger::message("Finished", FMT("build documentation page(s) in %s%ims%s", BOLD, duration, RESET));
    Logger::log("");
  }
  compiler->cleanup();
  return status;
}
} // namespace commands
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_DOC_BUILD_CMD_H_
