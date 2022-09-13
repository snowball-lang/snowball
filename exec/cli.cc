
#include "exec/cli.h"
#include "snowball/logger.h"
#include "snowball/errors.h"

#define IF_ANY_ARG(arg1, arg2) current_arg == arg1 || current_arg == arg2
#define IF_ARG(arg) current_arg == arg
#define CHECK_ARG(expectation) if (current_index == args.size()-1) { throw SNError(Error::ARGUMENT_ERROR, "Expected " expectation " as argument"); }
#define NEXT_ARGUMENT() \
    this->current_index++; \
    this->current_arg = this->args[this->current_index];

namespace snowball {
    namespace exec {
        CLI::CLI(int argc, char** argv) {

            // Start the index with 1 to ignore "snowball"
            for (int i = 1; i < argc; i++) {
                args.push_back(argv[i]);
            }
        }

        Options CLI::parse() {
            Options opts;

            current_arg = args[0];

            if (current_arg == "build") {
                opts.command = Options::Command::BUILD;

                while (current_index < args.size() - 1) {
                    NEXT_ARGUMENT();

                    if (IF_ANY_ARG("--test", "-t")) {
                        opts.build_opts.is_test = true;
                    } else if (IF_ARG("--emit_type")) {
                        CHECK_ARG("an output type")
                        NEXT_ARGUMENT()

                        if (current_arg == "exec") {
                            opts.build_opts.emit_type = Options::EmitType::EXECUTABLE;
                        } else if (current_arg == "lib") {
                            opts.build_opts.emit_type = Options::EmitType::OBJECT;
                        } else if (current_arg == "llvm-ir") {
                            opts.build_opts.emit_type = Options::EmitType::LLVM_IR;
                        } else {
                            throw SNError(Error::ARGUMENT_ERROR, "Valid build output types are: exec, lib, llvm-ir");
                        }
                    } else {
                        throw SNError(Error::ARGUMENT_ERROR, Logger::format("Unexpected argument for the build command: %s", current_arg.c_str()));
                    }
                }
            } else if (current_arg == "run") {
                opts.command = Options::Command::RUN;
                // TODO?
            } else if (current_arg == "test") {
                opts.command = Options::Command::TEST;
                // TODO
            } else if (current_arg == "init") {
                opts.command = Options::Command::INIT;

                while (current_index < args.size() - 1) {
                    NEXT_ARGUMENT();

                    if (IF_ANY_ARG("--yes", "-y")) {
                        opts.init_opts.yes = true;
                    } else if (IF_ANY_ARG("--lib", "-l")) {
                        opts.init_opts.lib = true;
                    } else if (IF_ANY_ARG("--cfg", "-c")) {
                        opts.init_opts.cfg = true;
                    } else if (IF_ARG("--skip-cfg")) {
                        if (opts.init_opts.cfg == true) {
                            throw SNError(Error::ARGUMENT_ERROR, "Can't have argument `--skip-cfg` if argument `--cfg` has been passed");
                        }

                        opts.init_opts.skip_cfg = true;
                    } else {
                        throw SNError(Error::ARGUMENT_ERROR, Logger::format("Unexpected argument for the init command: %s", current_arg.c_str()));
                    }
                }
            } else {
                throw SNError(Error::ARGUMENT_ERROR, Logger::format("Unknown command found: %s", current_arg.c_str()));
            }

            return opts;
        }

        void CLI::help() {
            Logger::log("Snowball (C) MIT");
            Logger::log("Usage: snowball [command] [options]\n");
            Logger::log("Snowball Commands:");
            Logger::log("  build            - builds the current snowball project");
            Logger::log("  run              - build and execute the current snowball project");
            Logger::log("  test             - execute tests");
            Logger::log("  init             - create a new snowball project (in current directory)");
            Logger::log("  explain          - explain a snowball error");
            Logger::log("  help             - prints out help");
            Logger::log("");
            Logger::log("Try `snowball help [command]` for more information.");
        }
    }
}

#undef IF_ANY_ARG
#undef IF_ARG
#undef CHECK_ARG
#undef NEXT_ARGUMENT