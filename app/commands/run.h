
#include "cli.h"
#include "compiler.h"
#include "errors.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "vendor/toml.hpp"

#include <stddef.h>
#include <unistd.h>

#ifndef __SNOWBALL_EXEC_RUN_CMD_H_
#define __SNOWBALL_EXEC_RUN_CMD_H_

namespace snowball {
namespace app {
namespace commands {
int run(app::Options::RunOptions p_opts) {
  std::string filename = p_opts.file;
  if (p_opts.file.empty()) {
    toml::parse_result parsed_config = Compiler::getConfiguration();
    filename = p_opts.file.empty() ?
            (std::string
            )(parsed_config["package"]["main"].value_or<std::string>((fs::current_path() / "src" / "main.sn"))) :
            p_opts.file;
  }

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
  std::string output =
          fs::current_path() / _SNOWBALL_OUT_DEFAULT("snowball-output", Options::EmitType::EXECUTABLE, false);

  auto compiler = new Compiler(content, filename);
  compiler->initialize();
  compiler->setOptimization(p_opts.opt);

  // TODO: false if --no-output is passed
  compiler->enamblePackageManager(p_opts.file.empty());
  compiler->compile(p_opts.no_progress || p_opts.silent);
  compiler->emitBinary(output, false);

  compiler->cleanup();

  char* args[1024] = {strdup(output.c_str())};
  for (size_t i = 0; i < p_opts.progArgs.size(); i++) {
    args[i + 1] = strdup(p_opts.progArgs[i].c_str());
  }
  args[p_opts.progArgs.size() + 1] = NULL;
  int result = execvp(args[0], args);

  // This shoudnt be executed
  return result;
}
} // namespace commands
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_EXEC_RUN_CMD_H_
