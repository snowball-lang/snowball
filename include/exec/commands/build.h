
#include "exec/cli.h"
#include "snowball/snowball.h"
#include "snowball/snowball.h"
#include "snowball/constants.h"
#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"
#include "snowball/vendor/toml.hpp"

#include <chrono>

using namespace std::chrono;

#ifndef __SNOWBALL_EXEC_BUILD_CMD_H_
#define __SNOWBALL_EXEC_BUILD_CMD_H_

namespace snowball {
    namespace exec {
        namespace commands {
            int build(exec::Options::BuildOptions p_opts) {

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

                std::string build_type;
                if (p_opts.is_test) {
                    build_type = "test";
                } else if (p_opts.emit_type == Options::EmitType::EXECUTABLE) {
                    build_type = "executable";
                } else if (p_opts.emit_type == Options::EmitType::LLVM_IR) {
                    build_type = "llvm-ir";
                } else if (p_opts.emit_type == Options::EmitType::OBJECT) {
                    build_type = "library";
                } else {
                    throw SNError(BUG, Logger::format("Unhandled emit type for build process ('%i')", p_opts.emit_type));
                }

                Logger::message("Compiling", Logger::format("%s v%s [%s]",
                    ((std::string)(parsed_config["package"]["name"].value_or<std::string>("<anonnimus>"))).c_str(),
                    ((std::string)(parsed_config["package"]["version"].value_or<std::string>("<unknown>"))).c_str(),
                    (build_type.c_str())));

                std::string content( (std::istreambuf_iterator<char>(ifs) ),
                    (std::istreambuf_iterator<char>()    ) );

                // TODO: check for output
                std::string output = p_opts.emit_type == exec::Options::EmitType::LLVM_IR
                    ? _SNOWBALL_LLIR_OUT_DEFAULT
                    : _SNOWBALL_OUT_DEFAULT;

                Compiler* compiler = new Compiler(content, filename);
                compiler->initialize();
                compiler->set_optimization(p_opts.opt);

                if (p_opts.is_test) {
                    compiler->enable_tests();
                }

                auto start = high_resolution_clock::now();

                // TODO: false if --no-output is passed
                compiler->compile(!p_opts.silent);
                auto stop = high_resolution_clock::now();

                // Get duration. Substart timepoints to
                // get duration. To cast it to proper unit
                // use duration cast method
                auto duration = duration_cast<milliseconds>(stop - start).count();

                Logger::message("Finished", Logger::format("build target(s) in %ims", duration));
                Logger::log("");

                int status;
                if (p_opts.emit_type == exec::Options::EmitType::OBJECT) {
                    status = compiler->emit_object(output);
                } else if (p_opts.emit_type == exec::Options::EmitType::LLVM_IR) {
                    status = compiler->emit_llvmir(output);
                } else {
                    status = compiler->emit_binary(output);
                }

                compiler->cleanup();

                return status;
            }
        }
    }
}

#endif // __SNOWBALL_EXEC_BUILD_CMD_H_
