
#include "constants.h"
#include "exec/cli.h"
#include "exec/commands/build.h"
#include "exec/commands/init.h"
#include "exec/commands/run.h"
#include "exec/commands/test.h"
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

int _main(int argc, char **argv) {

    try {
        if (argc == 1) {
            exec::CLI::help();
            return EXIT_SUCCESS;
        }

        exec::CLI *cli     = new exec::CLI(argc, argv);
        exec::Options opts = cli->parse();

        if (opts.command == exec::Options::BUILD) {
            return exec::commands::build(opts.build_opts);
        } else if (opts.command == exec::Options::RUN) {
            return exec::commands::run(opts.run_opts);
        } else if (opts.command == exec::Options::TEST) {
            return exec::commands::test(opts.test_opts);
        } else if (opts.command == exec::Options::INIT) {
            return exec::commands::init(opts.init_opts);
        } else {
            throw SNError(
                Error::TODO,
                FMT("Command with type %i not yet supported", opts.command));
        }
    } catch (const SNError& error) {
        error.print_error();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
