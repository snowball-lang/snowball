
#include "app/cli.h"
#include "compiler.h"
#include "constants.h"
#include "errors.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "vendor/toml.hpp"

#include <chrono>
#include <unistd.h>

using namespace std::chrono;

#ifndef __SNOWBALL_EXEC_BENCH_CMD_H_
#define __SNOWBALL_EXEC_BENCH_CMD_H_

namespace snowball {
namespace app {
namespace commands {
int bench(app::Options::BenchmarkOptions p_opts) {
  toml::parse_result parsed_config = Compiler::getConfiguration();

  std::string filename =
          (std::string)(parsed_config["package"]["main"].value_or<std::string>(fs::current_path() / "src" / "main.sn"));

  std::ifstream ifs(filename);
  if (ifs.fail()) {
    SNError(Error::IO_ERROR,
            FMT("Package main file not found in snowball "
                "project! \n\t(searching for: '%s')",
                filename.c_str()))
            .print_error();
    return EXIT_FAILURE;
  }

  std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

  // TODO: check for output
  std::string output = _SNOWBALL_OUT_DEFAULT("snowball-bench", Options::EmitType::EXECUTABLE, false);
  std::string build_type = "";

  filename = parsed_config["package"]["main"].value_or<std::string>((fs::current_path() / "src" / "main.sn"));
  std::string package_name = (std::string)(parsed_config["package"]["name"].value_or<std::string>("<anonnimus>"));
  std::string package_version = parsed_config["package"]["version"].value_or<std::string>("<unknown>");

  if (p_opts.opt == Options::Optimization::OPTIMIZE_O0) {
    build_type += "debug";
  } else {
    build_type += "optimized";
  }

  if (!p_opts.silent)
    Logger::message(
            "Project",
            FMT("%s v%s [%s%s%s]", package_name.c_str(), package_version.c_str(), BOLD, build_type.c_str(), RESET)
    );

  Compiler* compiler = new Compiler(content, filename);
  compiler->initialize();
  compiler->enable_benchmark();
  compiler->setOptimization(p_opts.opt);

  auto start = high_resolution_clock::now();

  // TODO: false if --no-output is passed
  compiler->compile(p_opts.no_progress || p_opts.silent);

  auto stop = high_resolution_clock::now();
  auto date = std::chrono::system_clock::now();

  compiler->emitBinary(output, false);
  compiler->cleanup();

  // Get duration. Substart timepoints to
  // get duration. To cast it to proper unit
  // use duration cast method
  auto duration = duration_cast<milliseconds>(stop - start).count();

  if (!p_opts.silent) {
    auto time = std::chrono::system_clock::to_time_t(date);
    char buffer[12]; // __DATE__ format requires 12 characters (including null terminator)
    std::strftime(buffer, sizeof(buffer), "%b %d %Y", std::localtime(&time));
    Logger::message("Finished", FMT("benchmark target(s) in %s%i%sms", BOLD, duration, RESET));
    Logger::compiling(FMT("version: %s%s%s\n", BOLD, _SNOWBALL_VERSION, RESET), "Snowball");
    Logger::compiling(FMT("Build date: %s%s%s\n", BOLD, buffer, RESET), "Date");
    Logger::message("Running", FMT("benchmarks (%s)", filename.c_str()));
  }

  char* args[] = {strdup(output.c_str()), NULL};
  int result = execvp(args[0], args);

  // This shoudnt be executed
  return result;
}
} // namespace commands
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_EXEC_BENCH_CMD_H_
