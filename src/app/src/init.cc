
#include <iostream>
#include <filesystem>

#include <llvm/Support/CommandLine.h>

#include "app/cli.h"
#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"
#include "compiler/reports/error.h"
#include "compiler/frontend/location.h"

#include "app/src/files/assets.h"

namespace snowball {
namespace cli {
using namespace llvm;
using namespace utils;

enum class LibType {
  Exe,
  Lib,
  Both
};

#define LIBRARY_MAIN std::string((const char*)LIBRARY_MAIN, LIBRARY_MAIN_len)
#define EXECUTABLE_MAIN std::string((const char*)EXECUTABLE_MAIN, EXECUTABLE_MAIN_len)
#define _GITIGNORE std::string((const char*)_GITIGNORE, _GITIGNORE_len)
#define SN_REKY std::string((const char*)SN_REKY, SN_REKY_len)
#define SN_CONFY std::string((const char*)SN_CONFY, SN_CONFY_len)
#define LIBRARY_TEST std::string((const char*)LIBRARY_TEST, LIBRARY_TEST_len)

void CLI::make_init(Ctx& ctx, Args& args, bool new_project) {
  auto loc = frontend::SourceLocation(0,0,0,std::make_shared<frontend::SourceFile>());

  auto err = [&](const std::string& message) {
    auto e = E(message, loc);
    e.print();
    exit(1);
  };

  auto write_file = [&](const std::string& path, const std::string& content) {
    std::ofstream file(path);
    file << content;
    file.close();
  };

  cl::OptionCategory category("Init Snowball Options");
  cl::opt<std::string> name("name", cl::desc("Name of the project"), cl::cat(category));
  cl::opt<std::string> version("version", cl::desc("Version of the project"), cl::cat(category));
  cl::opt<std::string> description("description", cl::desc("Description of the project"), cl::cat(category));
  cl::opt<LibType> lib_type("lib-type", cl::desc("Type of the library"), cl::values(
    clEnumValN(LibType::Exe, "exe", "Executable"),
    clEnumValN(LibType::Lib, "lib", "Library"),
    clEnumValN(LibType::Both, "both", "Both")
  ), cl::cat(category), cl::init(LibType::Exe));

  parse_args(args);
  if (name.empty()) {
    err("Name is required for the project!");
  }
  if (version.empty()) {
    err("Version is required for the project!");
  }

  if (new_project) {
    auto path = std::filesystem::current_path() / name;
    Logger::status("Creating", fmt::format("Project at {}", path.string()));
    if (!std::filesystem::exists(path))
      std::filesystem::create_directory(path);
    std::filesystem::current_path(path);
  }

  auto current_path = std::filesystem::current_path();
  if (!std::filesystem::is_empty(current_path)) {
    Logger::warn("Directory is not empty. It is recommended to create a new project in an empty directory.");
    Logger::raw("Do you want to continue? [y/N] ");
    std::string response;
    std::getline(std::cin, response);
    if (response != "y" && response != "Y") {
      err("Aborted project creation.");
    }
    Logger::status("Deleting", "Existing files in the directory");
    for (auto& entry : std::filesystem::directory_iterator(current_path)) {
      std::filesystem::remove_all(entry);
    }
  }

  std::string lib_type_str;
  switch (lib_type) {
    case LibType::Exe: lib_type_str = "exe"; break;
    case LibType::Lib: lib_type_str = "lib"; break;
    case LibType::Both: lib_type_str = "both"; break;
  }

  Logger::status("Creating", "Project files");
  std::filesystem::create_directory("src");
  write_file("src/main.sn", lib_type == LibType::Exe ? EXECUTABLE_MAIN : LIBRARY_MAIN);
  write_file("sn.confy", fmt::format(SN_CONFY, name, version, description, lib_type_str));
  write_file(".gitignore", _GITIGNORE);
  write_file("sn.reky", SN_REKY);

  Logger::status("Finished", "Project creation");
}

}
}