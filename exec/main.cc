
#include "snowball/snowball.h"
#include "snowball/constants.h"
#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"
#include "snowball/vendor/toml.hpp"

#include "exec/cli.h"
#include "exec/commands/build.h"
#include "exec/commands/run.h"
#include "exec/commands/test.h"

#include <string>
#include <vector>
#include <stdio.h>

#include <fstream>
#include <string.h>
#include <dirent.h>

#include <iostream>
#include <exception>
#include <stdexcept>

#include <filesystem>
#include <llvm/Support/FormattedStream.h>

using namespace snowball;
using namespace std::chrono;
using namespace snowball_utils;
namespace fs = std::filesystem;

int main(int argc, char** argv) {
    try {

        if (argc == 1) {
            exec::CLI::help();
            return EXIT_SUCCESS;
        }

        exec::CLI* cli = new exec::CLI(argc, argv);
        exec::Options opts = cli->parse();

        if (opts.command == exec::Options::BUILD) {
            return exec::commands::build(opts.build_opts);
        } else if (opts.command == exec::Options::RUN) {
            return exec::commands::run(opts.run_opts);
        } else if (opts.command == exec::Options::TEST) {
            return exec::commands::test(opts.test_opts);
        } else {
            throw SNError(Error::TODO, Logger::format("Command with type %i not yet supported", opts.command));
        }
    } catch(const SNError& error) {
        error.print_error();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
