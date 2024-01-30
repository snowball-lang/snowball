
#include "cli.h"
#include "utils/logger.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std::chrono;

#ifndef __SNOWBALL_EXEC_INIT_CMD_H_
#define __SNOWBALL_EXEC_INIT_CMD_H_

#define STRINGIFY(...) #__VA_ARGS__

#define LIBRARY_ENTRY "src/lib.sn"
#define EXECUTABLE_ENTRY "src/main.sn"

#define CONFIGURATION_FILE "sn.toml"

#include "files/assets.h"

namespace snowball {
namespace app {
namespace commands {

void init_create_cfg(bool yes, std::string entry, app::Options::InitOptions p_opts) {
  std::ofstream outfile(CONFIGURATION_FILE);
  std::string version = "0.0.1";
  // TODO: ask questions if p_opts.yes is false
  std::string toml_result;
  std::stringstream toml(toml_result);
  toml << "\n[package]";
  toml << FMT("\nname = \"%s\"", p_opts.name.c_str());
  toml << FMT("\nmain = \"%s\"", entry.c_str());
  toml << FMT("\nversion = \"%s\"", version.c_str());
  outfile << toml.str() << std::endl;
  outfile.close();
  Logger::message("Configuration", FMT("Configured project file (%s)", CONFIGURATION_FILE));
}

// TODO: Output messages
int init(app::Options::InitOptions p_opts) {
  auto start = high_resolution_clock::now();
  if (p_opts.create_dir) {
    Logger::message("Creating", FMT("Snowball project at directory %s", p_opts.name.c_str()));
    if (!fs::exists(p_opts.name)) fs::create_directory(p_opts.name);
    fs::current_path(p_opts.name);
  }
  // If the folder is not empty, ask the user if he wants to continue
  // if the user accepts, delete all files and continue
  if (!fs::is_empty(fs::current_path())) {
    Logger::rlog(FMT("%s[warning]%s: The current directory is not empty, do you want to continue? [y/N] ", BYEL, RESET));
    std::string answer;
    std::getline(std::cin, answer);
    if (answer != "y" && answer != "Y") {
      Logger::message("Aborted", "Snowball project creation");
      return 0;
    }
    Logger::message("Deleting", "All files in the current directory");
    for (auto& p : fs::directory_iterator(fs::current_path())) {
      fs::remove_all(p);
    }
  }
  if (p_opts.cfg) {
    init_create_cfg(p_opts.yes, EXECUTABLE_ENTRY, p_opts);
    return 0;
  } else if (p_opts.lib) {
    Logger::message("Initalizing", FMT("Current project [library]", CONFIGURATION_FILE));
    if (!fs::exists("src")) fs::create_directory("src");
    if (!p_opts.skip_cfg) init_create_cfg(p_opts.yes, LIBRARY_ENTRY, p_opts);
    std::ofstream outfile(LIBRARY_ENTRY);
    auto libFile = std::string((const char*)LIBRARY_MAIN, LIBRARY_MAIN_len);
    outfile << libFile << std::endl;
    outfile.close();
    if (!fs::exists("tests")) fs::create_directory("tests");
    if (!fs::exists("tests/main.sn")) {
      std::ofstream outfile("tests/main.sn");
      auto testFile = std::string((const char*)LIBRARY_TEST, LIBRARY_TEST_len);
      outfile << testFile << std::endl;
      outfile.close();
    }
  } else {
    Logger::message("Initalizing", FMT("Current project [executable]", CONFIGURATION_FILE));
    if (!fs::exists("src")) fs::create_directory("src");
    if (!p_opts.skip_cfg) init_create_cfg(p_opts.yes, EXECUTABLE_ENTRY, p_opts);
    std::ofstream outfile(EXECUTABLE_ENTRY);
    auto mainFile = std::string((const char*)EXECUTABLE_MAIN, EXECUTABLE_MAIN_len);
    outfile << mainFile << std::endl;
    outfile.close();
  }
  auto gitignore = std::string((const char*)_GITIGNORE, _GITIGNORE_len);
  std::ofstream outfile(".gitignore");
  outfile << gitignore << std::endl;
  outfile.close();
  auto stop = high_resolution_clock::now();
  // Get duration. Substart timepoints to
  // get duration. To cast it to proper unit
  // use duration cast method
  auto duration = duration_cast<milliseconds>(stop - start).count();
  Logger::message("Finished", FMT("snowball project in %ims 🐱", duration));
  Logger::rlog("\n");
  Logger::info("Execute `snowball --help` to get a manual about "
               "the project.");
  return 0;
}
} // namespace commands
} // namespace app
} // namespace snowball

#undef LIBRARY_MAIN
#undef LIBRARY_ENTRY

#undef EXECUTABLE_MAIN
#undef EXECUTABLE_ENTRY

#undef CONFIGURATION_FILE

#undef STRINGIFY

#endif // __SNOWBALL_EXEC_INIT_CMD_H_
