
#include "app/cli.h"
#include "compiler.h"
#include "errors.h"
#include "logger.h"
#include "utils/utils.h"
#include "vendor/toml.hpp"

#include <chrono>

using namespace std::chrono;

#ifndef __SNOWBALL_EXEC_TEST_CMD_H_
#define __SNOWBALL_EXEC_TEST_CMD_H_

namespace snowball {
namespace app {
namespace commands {
int
test(app::Options::TestOptions p_opts) {
    toml::parse_result parsed_config = Compiler::get_config();

    std::string filename = (std::string)(parsed_config["package"]["main"].value_or<std::string>(
            fs::current_path() / "src" / "main.sn"));

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
    std::string output = _SNOWBALL_OUT_DEFAULT;

    Logger::message("Compiling",
                    FMT("%s v%s",
                        ((std::string)(parsed_config["package"]["name"].value_or<std::string>(
                                 "<anonnimus>")))
                                .c_str(),
                        ((std::string)(parsed_config["package"]["version"].value_or<std::string>(
                                 "<unknown>")))
                                .c_str()));

    Compiler* compiler = new Compiler(content, filename);
    compiler->initialize();
    compiler->enable_tests();

    auto start = high_resolution_clock::now();

    // TODO: false if --no-output is passed
    compiler->compile(!p_opts.silent);

    auto stop = high_resolution_clock::now();

    compiler->emit_binary(output, false);
    compiler->cleanup();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<milliseconds>(stop - start).count();

    Logger::message("Finished", FMT("test target(s) in %ims", duration));
    Logger::message("Running", FMT("unittests (%s)", filename.c_str()));

    return system(output.c_str());
}
} // namespace commands
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_EXEC_TEST_CMD_H_
