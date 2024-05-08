
#include <filesystem>

#include "app/cli.h"
#include "compiler/reports/error.h"
#include "compiler/frontend/location.h"

#define CONFY_USE_UTILS
#include "app/vendor/confy/src/confy.hpp"

namespace snowball {
namespace cli {

CLI::CLI() {}

const Ctx CLI::parse(int argc, char** argv) {
  // TODO:
  Ctx ctx;
  ctx.build_mode = BuildMode::Build;
  ctx.input_file = "tests/main.sn";
  ctx.emit_type = EmitType::Llvm;
  get_package_config(ctx, "");
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
  static auto interface = confy::Interface::create({});
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
}

}
}
