
#include <filesystem>

#include "app/cli.h"
#include "compiler/reports/error.h"
#include "compiler/frontend/location.h"

#define CONFY_USE_UTILS
#include "app/vendor/confy/src/confy.hpp"

namespace snowball {
namespace cli {

CLI::CLI() {}

Ctx CLI::parse(int argc, char** argv) {
  // TODO:
  Ctx ctx;
  ctx.build_mode = BuildMode::Build;
  ctx.emit_type = EmitType::Llvm;
  return ctx;
}

// CONFY IMPLEMENTATION

class ConfyPackageType final : public confy::StringType {
public:
  std::optional<std::string> validate(const std::string& value) const override {
    if (value != "lib" && value != "exe" && value != "both") {
      return "Invalid package type. Must be one of 'lib', 'exe' or 'both'";
    }
    return std::nullopt;
  }
  static std::shared_ptr<ConfyPackageType> create() {
    return std::make_shared<ConfyPackageType>();
  }
}; 

void CLI::get_package_config(Ctx& ctx, const std::string& path) {
  static auto interface = confy::Interface::create({
    {"project", confy::Type::Object({
        {"name", confy::Type::String},
        {"version", confy::Type::String},
        {"authors", confy::Type::Array(confy::Type::String)},
        {"description", confy::Type::String},
        {"license", confy::Type::String},
        {"type", ConfyPackageType::create()},
        {"main", confy::Type::String},
    })},
    {"build", confy::Type::Object({
        {"linkage_libs", confy::Type::Array(confy::Type::String)}
    })}
  });
  std::string config_path = path.empty() ? "sn.confy" : path;
  auto config = confy::parse_file(interface, config_path);
  bool hasError = false;
  for (const auto& error : config.get_errors()) {
    hasError = true;
    auto err_loc = error.get_position();
    auto loc = frontend::SourceLocation(err_loc.line, err_loc.column, 1, std::make_shared<frontend::SourceFile>(config_path));
    auto e = E(error.get_message(), loc);
    e.print();
  } 
  if (hasError) {
    exit(1);
  }
  std::vector<std::string> authors;
  if (auto a = config.get_array("project.authors")) {
    for (const auto& author : a.value()) {
      authors.push_back(author->as_string());
    }
  }
  ctx.package_config = PackageConfigBase{
    .project = {
      .name = config.get_string_or("project.name", "<unnamed>"),
      .version = config.get_string_or("project.version", "0.1.0"),
      .description = config.get_string_or("project.description", "<no description>"),
      .main = config.get_string_or("project.main", "src/main.sn"),
      .type = config.get_string_or("project.type", "lib"),
      .authors = authors,
      .license = config.get_string_or("project.license", "<no license>"),
      .path = std::filesystem::absolute(path.empty() ? "." : path).lexically_normal()
    },
    .build = {
      .linkage_libs = {} // TODO: Implement linkage libs
    }
  };
}

}
}
