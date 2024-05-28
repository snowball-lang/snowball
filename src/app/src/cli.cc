
#include <iostream>
#include <filesystem>

#include <llvm/Support/CommandLine.h>

#include "app/cli.h"
#include "compiler/utils/utils.h"
#include "compiler/utils/logger.h"
#include "compiler/reports/error.h"
#include "compiler/frontend/location.h"

#define CONFY_USE_UTILS
#include "app/vendor/confy/src/confy.hpp"

#define SNOWBALL_PRINT_MESSAGE \
  << "Snowball Compiler " << _SNOWBALL_VERSION << " (" << SNOWBALL_BUILD_TYPE << " build)" << "\n";

namespace snowball {
namespace cli {
using namespace llvm;
using namespace utils;

CLI::CLI() {}

Ctx CLI::parse(int argc, char** argv) {
  // TODO:
  Ctx ctx;
  ctx.build_mode = BuildMode::Build;
  ctx.emit_type = EmitType::Llvm;
#ifdef SN_WIN
  ctx.target = Target::Windows;
#elif defined(SN_LIN)
  ctx.target = Target::Linux;
#elif defined(SN_MAC)
  ctx.target = Target::MacOS;
#elif defined(SN_UNK)
  ctx.target = Target::Unknown;
#else
#error "Unknown target compiler"
#endif
#ifdef SN_X86_64
  ctx.arch = Arch::X86_64;
#elif defined(SN_ARM64)
  ctx.arch = Arch::Arm64;
#endif
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
  cl::opt<std::string> config("config", cl::desc("Path to the configuration file"), cl::cat(category));
  if (mode == "build") {
    make_build(ctx, args);
  } else if (mode == "run") {
    make_build(ctx, args, true);
    ctx.emit_type = EmitType::Executable;
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
  parse_args(args);
  cl::PrintHelpMessage();
  exit(EXIT_SUCCESS);
}

void CLI::parse_args(Args& args) {
  cl::ParseCommandLineOptions(args.size(), args.data(), "Snowball Compiler", nullptr, nullptr, true);
}

void CLI::make_build(Ctx& ctx, Args& args, bool for_run) {
  ctx.build_mode = for_run ? BuildMode::Run : BuildMode::Build;
  cl::OptionCategory category(for_run ? "Run Options" : "Build Options");
  cl::opt<OptLevel> opt_level("O", cl::desc("Optimisation level"), cl::values(
    clEnumValN(OptLevel::Release, "release", "Release build"),
    clEnumValN(OptLevel::Debug, "debug", "Debug build"),
    clEnumValN(OptLevel::ReleaseWithDebug, "release-with-debug", "Release build with debug info"),
    clEnumValN(OptLevel::ReleaseFast, "release-fast", "Release build with fast optimisations")
  ), cl::init(OptLevel::Debug), cl::cat(category));
  cl::opt<std::string> cc("cc", cl::desc("Custom C compiler"), cl::cat(category));
  cl::opt<std::string> ld("ld", cl::desc("Custom linker"), cl::cat(category));
  cl::opt<LinkerType> linker_type("linker", cl::desc("Linker type"), cl::values(
    clEnumValN(LinkerType::Lld, "lld", "LLD"),
    clEnumValN(LinkerType::Mold, "mold", "Mold"),
    clEnumValN(LinkerType::Detect, "detect", "Detect")
  ), cl::init(LinkerType::Detect), cl::cat(category));
  cl::opt<bool> verbose("verbose", cl::desc("Verbose output"), cl::cat(category));
  cl::opt<EmitType>* emit_type = nullptr;
  cl::opt<Arch>* arch = nullptr;
  cl::opt<Target>* target = nullptr;
  cl::opt<bool>* static_link = nullptr;
  if (!for_run) {
    emit_type = new cl::opt<EmitType>("emit", cl::desc("Emit type"), cl::values(
      clEnumValN(EmitType::Llvm, "llvm-ir", "LLVM IR"),
      clEnumValN(EmitType::Asm, "asm", "Assembly"),
      clEnumValN(EmitType::Object, "obj", "Object file"),
      clEnumValN(EmitType::Executable, "exec", "Executable file"),
      clEnumValN(EmitType::Ast, "ast", "Abstract Syntax Tree"),
      clEnumValN(EmitType::Sil, "sil", "Snowball Intermediate Language"),
      clEnumValN(EmitType::LlvmBc, "llvm-bc", "LLVM Bitcode")
    ), cl::init(EmitType::Executable), cl::cat(category));
    target = new cl::opt<Target>("target", cl::desc("Target OS"), cl::values(
      clEnumValN(Target::Windows, "windows", "Windows"),
      clEnumValN(Target::Linux, "linux", "Linux"),
      clEnumValN(Target::MacOS, "macos", "macOS")
    ), cl::init(Target::Unknown), cl::cat(category));
    arch = new cl::opt<Arch>("arch", cl::desc("Architecture"), cl::values(
      clEnumValN(Arch::X86_64, "x86_64", "x86_64"),
      clEnumValN(Arch::Arm64, "arm64", "Arm64")
    ), cl::init(Arch::Unknown), cl::cat(category));
    static_link = new cl::opt<bool>("static", cl::desc("Static linkage"), cl::cat(category));
  }
  parse_args(args);
  ctx.opt_level = opt_level;
  ctx.custom_cc = cc;
  ctx.custom_linker = ld;
  ctx.linker_type = linker_type;  
  ctx.verbose = verbose;
  if (emit_type) {
    ctx.emit_type = *emit_type;
    delete emit_type;
  }
  if (target && *target != Target::Unknown) {
    ctx.target = *target;
    delete target;
  }
  if (arch && *arch != Arch::Unknown) {
    ctx.arch = *arch;
    delete arch;
  }
  if (static_link) {
    ctx.static_lib = *static_link;
    delete static_link;
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
