
#include "app/cli.h"
#include "app/commands/build.h"
#include "app/commands/init.h"
#include "app/commands/run.h"
#include "app/commands/test.h"
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

int
_main(int argc, char** argv) {
    try {
        if (argc == 1) {
            app::CLI::help();
            return EXIT_SUCCESS;
        }

        app::CLI* cli = new app::CLI(argc, argv);
        app::Options opts = cli->parse();

        if (opts.command == app::Options::BUILD) {
            return app::commands::build(opts.build_opts);
        } else if (opts.command == app::Options::RUN) {
            return app::commands::run(opts.run_opts);
        } else if (opts.command == app::Options::TEST) {
            return app::commands::test(opts.test_opts);
        } else if (opts.command == app::Options::INIT) {
            return app::commands::init(opts.init_opts);
        } else {
            throw SNError(Error::TODO, FMT("Command with type %i not yet supported", opts.command));
        }
    } catch (const SNError& error) {
        error.print_error();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
