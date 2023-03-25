
#include "compiler.h"
#include "errors.h"
#include "exec/cli.h"
#include "logger.h"
#include "utils/utils.h"
#include "vendor/toml.hpp"

#ifndef __SNOWBALL_EXEC_RUN_CMD_H_
#define __SNOWBALL_EXEC_RUN_CMD_H_

namespace snowball {
namespace exec {
namespace commands {
int run(exec::Options::RunOptions p_opts) {

    toml::parse_result parsed_config = Compiler::get_config();

    std::string filename =
        (std::string)(parsed_config["package"]["main"].value_or<std::string>(
            fs::current_path() / "src" / "main.sn"));

    std::ifstream ifs(filename);
    if (ifs.fail()) {
        SNError(Error::IO_ERROR, FMT("Package main file not found in snowball "
                                     "project! \n\t(searching for: '%s')",
                                     filename.c_str()))
            .print_error();
        return EXIT_FAILURE;
    }

    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));

    // TODO: check for output
    std::string output = fs::current_path() / _SNOWBALL_OUT_DEFAULT;

    Compiler *compiler = new Compiler(content, filename);
    compiler->initialize();
    compiler->set_optimization(p_opts.opt);

    // TODO: false if --no-output is passed
    compiler->compile(!p_opts.silent);
    compiler->emit_binary(output, false);

    compiler->cleanup();

    int result = system(output.c_str());
    remove(output.c_str());

    return result;
}
} // namespace commands
} // namespace exec
} // namespace snowball

#endif // __SNOWBALL_EXEC_RUN_CMD_H_
