
#include <iostream>
#include <filesystem>
#include <fstream>

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

  auto write_file = [&](const std::filesystem::path& path, const std::string& content) {
    std::ofstream file(path);
    file << content;
    file.close();
  };

  cl::OptionCategory category("Init Snowball Options");
  cl::opt<std::string> name("name", cl::desc("Name of the project"), cl::cat(category), cl::Required,
    cl::value_desc("name"), cl::Positional);
  cl::opt<std::string> version("lib-version", cl::desc("Version of the project"), cl::cat(category));
  cl::opt<std::string> description("description", cl::desc("Description of the project"), cl::cat(category));
  cl::opt<LibType> lib_type("lib-type", cl::desc("Type of the library"), cl::values(
    clEnumValN(LibType::Exe, "exe", "Executable"),
    clEnumValN(LibType::Lib, "lib", "Library"),
    clEnumValN(LibType::Both, "both", "Both")
  ), cl::cat(category), cl::init(LibType::Exe));
  cl::opt<std::string> path("path", cl::desc("Path to create the project in"), cl::cat(category));

  parse_args(args);
  if (name.empty()) {
    err("Name is required for the project!");
  }
  if (version.empty()) {
    version = "0.1.0";
  }
  if (description.empty()) {
    description = "A cool Snowball project!";
  }
  auto root_path = path.empty() ? std::filesystem::current_path() : std::filesystem::absolute(path.getValue());
  if (!std::filesystem::exists(root_path)) {
    err(F("Path '{}' does not exist!", root_path.string()));
  }

  auto dest_path = root_path / name.getValue();
  if (new_project) {
    Logger::status("Creating", fmt::format("Project at {}", dest_path.string()));
    if (!std::filesystem::exists(dest_path))
      std::filesystem::create_directory(dest_path);
    std::filesystem::current_path(dest_path);
  }

  if (!std::filesystem::is_empty(dest_path)) {
    Logger::warn("Directory is not empty. It is recommended to create a new project in an empty directory.");
    Logger::raw("Do you want to continue? [y/N] ");
    std::string response;
    std::getline(std::cin, response);
    if (response != "y" && response != "Y") {
      err("Aborted project creation.");
    }
    Logger::status("Deleting", "Existing files in the directory");
    for (auto& entry : std::filesystem::directory_iterator(dest_path)) {
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
  std::filesystem::create_directory(dest_path / "src");
  std::string entry = lib_type == LibType::Exe ? "main.sn" : "lib.sn";
  write_file(dest_path / "src" / entry, lib_type == LibType::Exe ? EXECUTABLE_MAIN : LIBRARY_MAIN);
  write_file(dest_path / "sn.confy", fmt::format(SN_CONFY, name, description, version, lib_type_str));
  write_file(dest_path / ".gitignore", _GITIGNORE);
  write_file(dest_path / "sn.reky", SN_REKY);

  Logger::status("Finished", "Project creation");
  exit(0);
}

}
}