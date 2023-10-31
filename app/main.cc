
#include "app/cli.h"
#include "app/commands/bench.h"
#include "app/commands/build.h"
#include "app/commands/init.h"
#include "app/commands/run.h"
#include "app/commands/test.h"
#include "app/commands/docgen.h"
#include "constants.h"
#include "utils/utils.h"
#include "vendor/toml.hpp"

#include <dirent.h>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#define SNOWBALL_INCLUDE_CRASH_HANDLER_MAIN
#define SNOWBALL_CRASH_HANDLER_IMPLEMENTATION
#include "crash_handler.h"

using namespace snowball;
using namespace std::chrono;
using namespace snowball::utils;

int _main(int argc, char** argv) {
  srand((unsigned) time(NULL) * getpid());

  try {
    if (argc == 1) {
      app::CLI::help();
      return EXIT_SUCCESS;
    }

    app::CLI* cli = new app::CLI(argc, argv);
    app::Options opts = cli->parse();

    switch (opts.command) {
      case app::Options::BUILD:
        return app::commands::build(opts.build_opts);
      case app::Options::RUN:
        return app::commands::run(opts.run_opts);
      case app::Options::TEST:
        return app::commands::test(opts.test_opts);
      case app::Options::INIT:
        return app::commands::init(opts.init_opts);
      case app::Options::BENCH:
        return app::commands::bench(opts.bench_opts);
      case app::Options::DOCS:
        return app::commands::docgen(opts.docs_opts);
      default:
        throw SNError(Error::TODO, FMT("Command with type %i not yet supported", opts.command));
    }
  } catch (const SNError& error) {
    error.print_error();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
