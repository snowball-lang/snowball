
#include "exec/cli.h"
#include "snowball/snowball.h"
#include "snowball/snowball.h"
#include "snowball/constants.h"
#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"
#include "snowball/vendor/toml.hpp"


#ifndef __SNOWBALL_EXEC_RUN_CMD_H_
#define __SNOWBALL_EXEC_RUN_CMD_H_

namespace snowball {
    namespace exec {
        namespace commands {
            int run(exec::Options::RunOptions p_opts) {

                toml::parse_result parsed_config = Compiler::get_config();

                std::string filename = (std::string)(parsed_config["package"]["main"].value_or<std::string>(""));
                if (filename.empty()) {
                    throw SNError(Error::CONFIGURATION_ERROR, "Package main file not found in project configuration.");
                }

                std::ifstream ifs(filename);
                if(ifs.fail()){
                    SNError(Error::IO_ERROR, Logger::format("filename '%s' not found.", filename.c_str())).print_error();
                    return EXIT_FAILURE;
                }

                std::string content( (std::istreambuf_iterator<char>(ifs) ),
                    (std::istreambuf_iterator<char>()    ) );

                // TODO: check for output
                std::string output = _SNOWBALL_OUT_DEFAULT;

                Compiler* compiler = new Compiler(content, filename);
                compiler->initialize();

                // TODO: false if --no-output is passed
                compiler->compile(true);
                compiler->emit_binary(output, false);

                compiler->cleanup();

                system(output.c_str());
            }
        }
    }
}

#endif // __SNOWBALL_EXEC_RUN_CMD_H_
