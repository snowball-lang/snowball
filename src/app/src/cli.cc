
#include <iostream>
#include <filesystem>

#include <llvm/Support/CommandLine.h>

#include "app/cli.h"
#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"
#include "compiler/reports/error.h"
#include "compiler/frontend/location.h"

#include "compiler/globals.h"

#include <lld/Common/Driver.h>

#define CONFY_USE_UTILS
#include "app/vendor/confy/src/confy.hpp"

#define SNOWBALL_PRINT_MESSAGE \
  << "Snowball Compiler " << _SNOWBALL_VERSION << " (" << SNOWBALL_BUILD_TYPE << " build)" << "\n";

namespace snowball {
namespace cli {
using namespace llvm;
using namespace utils;

CLI::CLI() {}

void rename_duplicate_options() {
  using namespace llvm;
  llvm::StringMap<cl::Option *> &map = cl::getRegisteredOptions();

  auto rename = [&map](const char *from, const char *to) {
    auto i = map.find(from);
    if (i != map.end()) {
      cl::Option *opt = i->getValue();
      map.erase(i);
      if (to) {
        opt->setArgStr(to);
        opt->setHiddenFlag(cl::Hidden);
        map[to] = opt;
      }
    }
  };

  auto hide_opt = [&map](const char* name) {
    auto i = map.find(name);
    if (i != map.end()) {
      cl::Option *opt = i->getValue();
      opt->setHiddenFlag(cl::Hidden);
    }
  };

  rename("float-abi", "llvm-float-abi");
  rename("opaque-pointers", nullptr);

  hide_opt("basic-block-sections");

  new cl::opt<FloatABI, true> ("float-abi", cl::desc("Floating point ABI"), cl::values(
    clEnumValN(FloatABI::Hard, "hard", "Hardware floating point ABI"),
    clEnumValN(FloatABI::SoftFP, "softfp", "Soft floating point ABI but with hardware floating point instructions"),
    clEnumValN(FloatABI::Soft, "soft", "Soft floating point ABI")
  ), cl::location(global.float_abi), cl::init(FloatABI::Default));
}

Ctx CLI::parse(int argc, char** argv) {
  // TODO:
  Ctx ctx;
  rename_duplicate_options();
  cl::SetVersionPrinter([](raw_ostream & OS) {
      OS SNOWBALL_PRINT_MESSAGE;
    });
  std::vector<const char*> args{argv[0]};
  if (argc < 2)
    print_help(args);
  for (int i = 2; i < argc; i++)
    args.push_back(argv[i]);
  std::string mode = argv[1];

  cl::OptionCategory category("General Snowball Options");
  static cl::opt<std::string> config("config", cl::desc("Path to the configuration file"), cl::cat(category));
  if (mode == "build") {
    make_build(ctx, args);
  } else if (mode == "run") {
    make_build(ctx, args, true);
    global.emit_type = EmitType::Executable;
  } else if (mode == "init" || mode == "new") {
    make_init(ctx, args, mode == "new");
  } else if (mode == "reky") {
    make_reky(ctx, args);
  } else if (mode == "--version" || mode == "-v") {
    cl::PrintVersionMessage();
    exit(EXIT_SUCCESS);
  } else {
    Logger::error(F("Unknown mode '{}'", mode));
    print_help(args);
  }
  if (!config.empty())
    ctx.config_path = config;
  return ctx;
}

// CLI COMMANDS

void CLI::print_help(Args& args) {
  hide_args();
  cl::OptionCategory helpCategory("Help Options");
  cl::SubCommand run("run", "Run a Snowball program");
  cl::SubCommand build("build", "Build a Snowball program");
  cl::SubCommand reky("reky", "Run snowball's package manager");
  cl::SubCommand init("init", "Initialize a new Snowball project");
  cl::SubCommand new_("new", "Initialize a new Snowball project");
  parse_args(args);
  cl::PrintHelpMessage();
  exit(EXIT_SUCCESS);
}

void CLI::parse_args(Args& args) {
  cl::ParseCommandLineOptions(args.size(), args.data(), "Snowball Compiler", nullptr, nullptr, false);
}

void CLI::make_build(Ctx& ctx, Args& args, bool for_run) {
  ctx.build_mode = for_run ? BuildMode::Run : BuildMode::Build;
  parse_args(args);
  if (for_run && global.emit_type != EmitType::Executable) {
    Logger::error("Run mode only supports executable output");
    exit(EXIT_FAILURE);
  }
}

void CLI::hide_args() {
  auto args = cl::getRegisteredOptions();
  for (auto& arg : args) {
    arg.getValue()->setHiddenFlag(cl::ReallyHidden);
  }
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
      {"src", confy::Type::String}
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
  auto default_path = path.empty() ? "." : path;
  ctx.package_config = PackageConfigBase{
    .project = {
      .name = config.get_string_or("project.name", "<unnamed>"),
      .version = config.get_string_or("project.version", "0.1.0"),
      .description = config.get_string_or("project.description", "<no description>"),
      .type = config.get_string_or("project.type", "lib"),
      .authors = authors,
      .license = config.get_string_or("project.license", "<no license>"),
      .path = std::filesystem::absolute(default_path).lexically_normal(),
      .src = std::filesystem::relative(config.get_string_or("project.src", "./src")).lexically_normal(),
    },
    .build = {
      .linkage_libs = {} // TODO: Implement linkage libs
    }
  };
}

}
}
