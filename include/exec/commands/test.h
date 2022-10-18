
#include "exec/cli.h"
#include "snowball/snowball.h"
#include "snowball/snowball.h"
#include "snowball/constants.h"
#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"
#include "snowball/vendor/toml.hpp"

#include <chrono>

using namespace std::chrono;

#ifndef __SNOWBALL_EXEC_TEST_CMD_H_
#define __SNOWBALL_EXEC_TEST_CMD_H_

namespace snowball {
    namespace exec {
        namespace commands {
            int test(exec::Options::TestOptions p_opts) {

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

                Logger::message("Compiling", Logger::format("%s v%s",
                    ((std::string)(parsed_config["package"]["name"].value_or<std::string>("<anonnimus>"))).c_str(),
                    ((std::string)(parsed_config["package"]["version"].value_or<std::string>("<unknown>"))).c_str()));

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

                Logger::message("Finished", Logger::format("test target(s) in %ims", duration));
                Logger::message("Running", Logger::format("unittests (%s)", filename.c_str()));

                return system(output.c_str());
            }
        }
    }
}

#endif // __SNOWBALL_EXEC_TEST_CMD_H_
