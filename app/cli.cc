
#include "cli.h"

#include "errors.h"
#include "utils/logger.h"

#include <llvm/Support/CommandLine.h>
#include <iostream>
#include <map>

namespace snowball {
namespace app {

using namespace llvm;

CLI::CLI(int argc, char** argv) : argc(argc), argv(argv) {}

namespace cli {
namespace modes {

using EmitType = Options::EmitType;
using Optimization = Options::Optimization;

void parse_args(argsVector& args) {
  cl::ParseCommandLineOptions(args.size(), args.data(), "Snowball Compiler", nullptr, nullptr, true);
}

void hide_args() {
  auto args = cl::getRegisteredOptions();
  for (auto& arg : args) {
    arg.getValue()->setHiddenFlag(cl::ReallyHidden);
  }
}

void register_build_opts(Options::BuildOptions& options, std::string mode, argsVector& args) {
  cl::OptionCategory buildCategory(mode == "build" ? "Build Options" : "Run Options");
  cl::opt<Optimization> opt(
    cl::desc("optimization mode"),
    cl::values(
      clEnumValN(Optimization::OPTIMIZE_O0, "O0", "No optimization"),
      clEnumValN(Optimization::OPTIMIZE_O1, "O1", "Optimization level 1"),
      clEnumValN(Optimization::OPTIMIZE_O2, "O2", "Optimization level 2"),
      clEnumValN(Optimization::OPTIMIZE_O3, "O3", "Optimization level 3"),
      clEnumValN(Optimization::OPTIMIZE_Os, "Os", "Optimization for size"),
      clEnumValN(Optimization::OPTIMIZE_Oz, "Oz", "Optimization for size (aggressive)")),
    cl::init(Optimization::OPTIMIZE_O1),
    cl::cat(buildCategory),
    cl::AlwaysPrefix);
  cl::opt<bool> silent("silent", cl::desc("Silent mode"), cl::cat(buildCategory));
  cl::opt<std::string> file("file", cl::desc("File to compile"), cl::cat(buildCategory));
  cl::opt<bool> no_progress("no-progress", cl::desc("Disable progress bar"), cl::cat(buildCategory));
  cl::alias _silent("s", cl::aliasopt(silent), cl::desc("Alias for -silent"), cl::cat(buildCategory));
  cl::alias _no_progress("np", cl::aliasopt(no_progress), cl::desc("Alias for -no-progress"), cl::cat(buildCategory));
  cl::alias _file("f", cl::aliasopt(file), cl::desc("Alias for -file"), cl::cat(buildCategory));
  if (mode == "build") {
    auto test = cl::opt<bool>("test", cl::desc("Builds the project for testing"), cl::cat(buildCategory));
    auto bench = cl::opt<bool>("bench", cl::desc("Builds the project for benchmarking"), cl::cat(buildCategory));
    auto output = cl::opt<std::string>("output", cl::desc("Output file"), cl::cat(buildCategory));
    auto emit = cl::opt<EmitType>("emit", 
      cl::desc("Output type"),
      cl::values(
        clEnumValN(EmitType::EXECUTABLE, "exe", "Executable"),
        clEnumValN(EmitType::OBJECT, "obj", "Object file"),
        clEnumValN(EmitType::LLVM_IR, "llvm-ir", "LLVM IR"),
        clEnumValN(EmitType::ASSEMBLY, "asm", "Assembly"),
        clEnumValN(EmitType::SNOWBALL_IR, "snowball-ir", "Snowball IR")),
      cl::init(EmitType::EXECUTABLE), cl::cat(buildCategory));
    cl::alias _test("t", cl::aliasopt(test), cl::desc("Alias for -test"), cl::cat(buildCategory));
    cl::alias _bench("b", cl::aliasopt(bench), cl::desc("Alias for -bench"), cl::cat(buildCategory));
    cl::alias _output("o", cl::aliasopt(output), cl::desc("Alias for -output"), cl::cat(buildCategory));
    cl::alias _emit("e", cl::aliasopt(emit), cl::desc("Alias for -emit"), cl::cat(buildCategory));
    parse_args(args);
    options.opt = opt;
    options.silent = silent;
    options.file = file;
    options.no_progress = no_progress;
    options.is_test = test;
    options.is_bench = bench;
    options.output = output;
    options.emit_type = emit;
    return;
  }
  parse_args(args);
  options.opt = opt;
  options.silent = silent;
  options.file = file;
  options.no_progress = no_progress;
}

void run(Options& opts, argsVector& args) {
  auto& runOpts = opts.run_opts;
  cl::OptionCategory runCategory("Extra run Options");
  cl::opt<bool> jit("jit", cl::desc("Run the program in JIT mode"), cl::cat(runCategory));
  
  std::vector<std::string> progArgs;
  bool addToArgs = false;
  size_t argIndex = 0;
  argsVector usedArgs;
  for (auto& arg : args) {
    if (addToArgs) {
      progArgs.push_back(arg);
    } else {
      usedArgs.push_back(arg);
    }
    if (addToArgs || (std::string)arg == "--") {
      addToArgs = true;
    }
    argIndex++;
  }

  register_build_opts(runOpts, "run", usedArgs);
  runOpts.jit = jit;
  runOpts.progArgs = progArgs;
}

void build(Options& opts, argsVector& args) {
  auto& buildOpts = opts.build_opts;
  register_build_opts(buildOpts, "build", args);
}

void test(Options& opts, argsVector& args) {
  cl::OptionCategory buildCategory("Test Options");
  cl::opt<Optimization> opt(
    cl::desc("optimization mode"),
    cl::values(
      clEnumValN(Optimization::OPTIMIZE_O0, "O0", "No optimization"),
      clEnumValN(Optimization::OPTIMIZE_O1, "O1", "Optimization level 1"),
      clEnumValN(Optimization::OPTIMIZE_O2, "O2", "Optimization level 2"),
      clEnumValN(Optimization::OPTIMIZE_O3, "O3", "Optimization level 3"),
      clEnumValN(Optimization::OPTIMIZE_Os, "Os", "Optimization for size"),
      clEnumValN(Optimization::OPTIMIZE_Oz, "Oz", "Optimization for size (aggressive)"),
      clEnumValN(Optimization::OPTIMIZE_O0, "Debug", "Debug mode (no optimization)"),
      clEnumValN(Optimization::OPTIMIZE_O3, "Release", "Release mode (optimization level 3)")
      ),
    cl::init(Optimization::OPTIMIZE_O3),
    cl::cat(buildCategory), cl::AlwaysPrefix);
  cl::opt<bool> silent("silent", cl::desc("Silent mode"), cl::cat(buildCategory));
  cl::opt<bool> no_progress("no-progress", cl::desc("Disable progress bar"), cl::cat(buildCategory));
  cl::alias _silent("s", cl::aliasopt(silent), cl::desc("Alias for -silent"), cl::cat(buildCategory));
  cl::alias _no_progress("np", cl::aliasopt(no_progress), cl::desc("Alias for -no-progress"), cl::cat(buildCategory));
  parse_args(args);
  opts.test_opts.opt = opt;
  opts.test_opts.silent = silent;
  opts.test_opts.no_progress = no_progress;
}

void init(Options& opts, argsVector& args) {
  hide_args();
  cl::OptionCategory initCategory("Init Options");
  cl::opt<bool> cfg("cfg", cl::desc("Create a snowball configuration file"), cl::cat(initCategory));
  cl::opt<bool> lib("lib", cl::desc("Create a snowball library"), cl::cat(initCategory));
  cl::opt<bool> yes("yes", cl::desc("Skip confirmation"), cl::cat(initCategory));
  cl::opt<bool> skip_cfg("skip-cfg", cl::desc("Skip configuration"), cl::cat(initCategory));
  cl::opt<std::string> name("name", cl::desc("Project name"), cl::cat(initCategory), cl::Required);
  cl::alias _yes("y", cl::aliasopt(yes), cl::desc("Alias for -yes"), cl::cat(initCategory));
  parse_args(args);
  opts.init_opts.cfg = cfg;
  opts.init_opts.lib = lib;
  opts.init_opts.yes = yes;
  opts.init_opts.skip_cfg = skip_cfg;
  opts.init_opts.name = name;
}

void docs(Options& opts, argsVector& args) {
  hide_args();
  cl::OptionCategory docsCategory("Docs Options");
  cl::opt<bool> silent("silent", cl::desc("Silent mode"), cl::cat(docsCategory));
  cl::opt<bool> no_progress("no-progress", cl::desc("Disable progress bar"), cl::cat(docsCategory));
  cl::opt<std::string> base("base", cl::desc("Base URL"), cl::cat(docsCategory));
  cl::alias _silent("s", cl::aliasopt(silent), cl::desc("Alias for -silent"), cl::cat(docsCategory));
  cl::alias _no_progress("np", cl::aliasopt(no_progress), cl::desc("Alias for -no-progress"), cl::cat(docsCategory));
  cl::alias _base("b", cl::aliasopt(base), cl::desc("Alias for -base"), cl::cat(docsCategory));
  parse_args(args);
  opts.docs_opts.silent = silent;
  opts.docs_opts.no_progress = no_progress;
  opts.docs_opts.base = base;
}

void bench(Options& opts, argsVector& args) {
  cl::OptionCategory benchCategory("Benchmark Options");
  cl::opt<Optimization> opt(
    cl::desc("optimization mode"),
    cl::values(
      clEnumValN(Optimization::OPTIMIZE_O0, "O0", "No optimization"),
      clEnumValN(Optimization::OPTIMIZE_O1, "O1", "Optimization level 1"),
      clEnumValN(Optimization::OPTIMIZE_O2, "O2", "Optimization level 2"),
      clEnumValN(Optimization::OPTIMIZE_O3, "O3", "Optimization level 3"),
      clEnumValN(Optimization::OPTIMIZE_Os, "Os", "Optimization for size"),
      clEnumValN(Optimization::OPTIMIZE_Oz, "Oz", "Optimization for size (aggressive)"),
      clEnumValN(Optimization::OPTIMIZE_O0, "Debug", "Debug mode (no optimization)"),
      clEnumValN(Optimization::OPTIMIZE_O3, "Release", "Release mode (optimization level 3)")
      ),
    cl::init(Optimization::OPTIMIZE_O3),
    cl::cat(benchCategory), cl::AlwaysPrefix);
  cl::opt<bool> silent("silent", cl::desc("Silent mode"), cl::cat(benchCategory));
  cl::opt<bool> no_progress("no-progress", cl::desc("Disable progress bar"), cl::cat(benchCategory));
  cl::alias _silent("s", cl::aliasopt(silent), cl::desc("Alias for -silent"), cl::cat(benchCategory));
  cl::alias _no_progress("np", cl::aliasopt(no_progress), cl::desc("Alias for -no-progress"), cl::cat(benchCategory));
  parse_args(args);
  opts.bench_opts.opt = opt;
  opts.bench_opts.silent = silent;
  opts.bench_opts.no_progress = no_progress;
}

void clean(Options& opts, argsVector& args) {
  hide_args();
  cl::OptionCategory cleanCategory("Clean Options");
  parse_args(args);
}

} // namespace modes
} // namespace cli

#define SNOWBALL_PRINT_MESSAGE << "Snowball Compiler " << _SNOWBALL_VERSION << " (" << _SNOWBALL_BUILD_TYPE << " build)" << "\n";

Options CLI::parse() {
  Options opts;
  cl::SetVersionPrinter([](raw_ostream& OS) {
    OS SNOWBALL_PRINT_MESSAGE;
  });
  std::vector<const char *> args{argv[0]};
  std::string mode;
  if (argc < 2) {
    args.push_back("--help");
    mode = "--help";
  } else {
    for (int i = 2; i < argc; i++)
      args.push_back(argv[i]);
    mode = argv[1];
  }
  std::string argv0 = std::string(args[0]) + " " + mode;
  args[0] = argv0.data();
  static std::unordered_map<std::string, std::pair<Options::Command, std::function<void(Options&, argsVector&)>>> modes = {
    {"run", {Options::RUN, cli::modes::run}},
    {"build", {Options::BUILD, cli::modes::build}},
    {"test", {Options::TEST, cli::modes::test}},
    {"init", {Options::INIT, cli::modes::init}},
    {"new", {Options::INIT, cli::modes::init}},
    {"docs", {Options::DOCS, cli::modes::docs}},
    {"bench", {Options::BENCH, cli::modes::bench}},
    {"clean", {Options::CLEAN, cli::modes::clean}},
  };
  if (mode == "--version" || mode == "-v") {
    std::cout SNOWBALL_PRINT_MESSAGE;
    exit(EXIT_SUCCESS);
  } else if (mode == "--help" || mode == "-h") {
    cli::modes::hide_args();
    cl::OptionCategory helpCategory("Help Options");
    cl::SubCommand run("run", "Run a Snowball program");
    cl::SubCommand build("build", "Build a Snowball program");
    cl::SubCommand test("test", "Test a Snowball program");
    cl::SubCommand init("init", "Initialize a Snowball project");
    cl::SubCommand docs("docs", "Generate documentation for a Snowball project");
    cl::SubCommand bench("bench", "Benchmark a Snowball program");
    cl::SubCommand clean("clean", "Clean a Snowball project");
    cli::modes::parse_args(args);
    cl::PrintHelpMessage();
    exit(EXIT_SUCCESS);
  } else {
    if (modes.find(mode) == modes.end()) {
      std::cout << "Unknown command '" << mode << "'\n";
      exit(EXIT_FAILURE);
    }
    auto& modePair = modes[mode];
    opts.command = modePair.first;
    modePair.second(opts, args);
    opts.init_opts.create_dir = mode == "new";
  }
  return opts;
}
} // namespace app
} // namespace snowball

#undef IF_ANY_ARG
#undef IF_ARG
#undef CHECK_ARG
#undef NEXT_ARGUMENT