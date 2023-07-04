
#include "app/cli.h"

#include "errors.h"
#include "logger.h"

#define IF_ANY_ARG(arg1, arg2) current_arg == arg1 || current_arg == arg2
#define IF_ARG(arg)            current_arg == arg
#define CHECK_ARG(expectation)                                                                     \
    if (current_index == args.size() - 1) {                                                        \
        throw SNError(Error::ARGUMENT_ERROR, "Expected " expectation " as argument");              \
    }
#define NEXT_ARGUMENT()                                                                            \
    this->current_index++;                                                                         \
    this->current_arg = this->args[this->current_index];

namespace snowball {
namespace app {
CLI::CLI(int argc, char** argv) {
    // Start the index with 1 to ignore "snowball"
    for (int i = 1; i < argc; i++) { args.push_back(argv[i]); }
}

Options CLI::parse() {
    Options opts;

    current_arg = args[0];

    if (current_arg == "help") {
        if (current_index < args.size() - 1) {
            NEXT_ARGUMENT();

            if (IF_ARG("build")) {
                Logger::log("Snowball (C) MIT");
                Logger::log("Usage: snowball build [options]\n");
                Logger::log("Help:");
                Logger::log("  Build your snowball project\n");
                Logger::log("Options:");
                Logger::log("  --emit_type {type}        - Select the "
                            "output format");
                Logger::log("  --test [-t]               - Build "
                            "project as it was for "
                            "testing");
                Logger::log("  --optimization [-o] {opt} - Optimize "
                            "your project at a "
                            "certain level");
                Logger::log("");
                Logger::log("Emit types:");
                Logger::log("  exec                      - Build your "
                            "project as an "
                            "executable");
                Logger::log("  lib                       - Build a "
                            "shared library from "
                            "your project");
                Logger::log("  llvm-ir                   - Emit the "
                            "llvm-ir code to "
                            "file");
                Logger::log("");
                Logger::log("Optimization levels:");
                Logger::log("  O0                        - Disable as many "
                            "optimizations as possible");
                Logger::log("  O1 (default)              - Optimize "
                            "quickly without "
                            "destroying debuggability");
                Logger::log("  O2                        - Like O3 "
                            "without triggering "
                            "significant incremental compile time or "
                            "code size growth");
                Logger::log("  O3                        - Optimize "
                            "for fast execution "
                            "as much as possible");
                Logger::log("  Os                        - Similar to "
                            "O2 but tries to "
                            "optimize for small code size instead of "
                            "fast execution");
                Logger::log("  Oz                        - A very "
                            "specialized mode "
                            "that will optimize for code size at any "
                            "and all costs");
            } else if (IF_ARG("run")) {
                Logger::log("Snowball (C) MIT");
                Logger::log("Usage: snowball run [options]\n");
                Logger::log("Help:");
                Logger::log("  Build and execute your snowball project\n");
                Logger::log("Options:");
                Logger::log("  --optimization [-o] {opt} - Optimize "
                            "your project at a "
                            "certain level");
                Logger::log("  --jit [-j] {opt}          - Execute the project "
                            "using the JIT");
                Logger::log("");
                Logger::log("Optimization levels:");
                Logger::log("  O0                        - Disable as many "
                            "optimizations as possible");
                Logger::log("  O1 (default)              - Optimize "
                            "quickly without "
                            "destroying debuggability");
                Logger::log("  O2                        - Like O3 "
                            "without triggering "
                            "significant incremental compile time or "
                            "code size growth");
                Logger::log("  O3                        - Optimize "
                            "for fast execution "
                            "as much as possible");
                Logger::log("  Os                        - Similar to "
                            "O2 but tries to "
                            "optimize for small code size instead of "
                            "fast execution");
                Logger::log("  Oz                        - A very "
                            "specialized mode "
                            "that will optimize for code size at any "
                            "and all costs");
            } else if (IF_ARG("test")) {
                Logger::log("Snowball (C) MIT");
                Logger::log("Usage: snowball test [options]\n");
                Logger::log("Help:");
                Logger::log("  Build and execute your unit tests\n");
                Logger::info("You can get your tests as an executable "
                             "by executing:\n   "
                             "-> `snowball build test`");
            } else if (IF_ARG("init")) {
                Logger::log("Snowball (C) MIT");
                Logger::log("Usage: snowball init [options]\n");
                Logger::log("Help:");
                Logger::log("  Create a new project in the current "
                            "directory\n");
                Logger::log("Options:");
                Logger::log("  --yes (-y)        - Stop asking me you "
                            "stupid bot!");
                Logger::log("  --lib (-l)        - Create a project "
                            "designed as a "
                            "library");
                Logger::log("  --cfg (-c)        - Create only a "
                            "configuration file");
                Logger::log("  --skip-cfg        - Create the project "
                            "without a config "
                            "file (errors if `--cfg` is passed)");
                Logger::log("");
                Logger::info("You can create a new folder by executing:\n   -> "
                             "`snowball new {name}`");
            } else {
                throw SNError(ARGUMENT_ERROR, FMT("Command '%s' not found.", current_arg.c_str()));
            }
        } else {
            help();
        }

        exit(0);
    } else if (current_arg == "build") {
        opts.command = Options::Command::BUILD;

        while (current_index < args.size() - 1) {
            NEXT_ARGUMENT();

            if (IF_ANY_ARG("--test", "-t")) {
                opts.build_opts.is_test = true;
            } else if (IF_ANY_ARG("--silent", "-s")) {
                opts.build_opts.silent = true;
            } else if (IF_ANY_ARG("--file", "-f")) {
                CHECK_ARG("an input file")
                NEXT_ARGUMENT()

                opts.build_opts.file = current_arg;
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
                    throw SNError(Error::ARGUMENT_ERROR,
                                  "Valid build output types are: exec, lib, "
                                  "llvm-ir");
                }
            } else if (IF_ANY_ARG("--optimization", "-o")) {
                CHECK_ARG("an optimization level")
                NEXT_ARGUMENT()

                if (current_arg == "O0") {
                    opts.build_opts.opt = Options::Optimization::OPTIMIZE_O0;
                } else if (current_arg == "O1") {
                    opts.build_opts.opt = Options::Optimization::OPTIMIZE_O1;
                } else if (current_arg == "O2") {
                    opts.build_opts.opt = Options::Optimization::OPTIMIZE_O2;
                } else if (current_arg == "O3") {
                    opts.build_opts.opt = Options::Optimization::OPTIMIZE_O3;
                } else if (current_arg == "Os") {
                    opts.build_opts.opt = Options::Optimization::OPTIMIZE_Os;
                } else if (current_arg == "Oz") {
                    opts.build_opts.opt = Options::Optimization::OPTIMIZE_Oz;
                } else {
                    throw SNError(Error::ARGUMENT_ERROR,
                                  "Valid optimization levels are: O0, O1, O2, "
                                  "O3, Os, Oz");
                }
            } else {
                throw SNError(
                        Error::ARGUMENT_ERROR,
                        FMT("Unexpected argument for the build command: %s", current_arg.c_str()));
            }
        }
    } else if (current_arg == "run") {
        opts.command = Options::Command::RUN;

        while (current_index < args.size() - 1) {
            NEXT_ARGUMENT();

            if (IF_ANY_ARG("--optimization", "-o")) {
                CHECK_ARG("an optimization level")
                NEXT_ARGUMENT()

                if (current_arg == "O0") {
                    opts.run_opts.opt = Options::Optimization::OPTIMIZE_O0;
                } else if (current_arg == "O1") {
                    opts.run_opts.opt = Options::Optimization::OPTIMIZE_O1;
                } else if (current_arg == "O2") {
                    opts.run_opts.opt = Options::Optimization::OPTIMIZE_O2;
                } else if (current_arg == "O3") {
                    opts.run_opts.opt = Options::Optimization::OPTIMIZE_O3;
                } else if (current_arg == "Os") {
                    opts.run_opts.opt = Options::Optimization::OPTIMIZE_Os;
                } else if (current_arg == "Oz") {
                    opts.run_opts.opt = Options::Optimization::OPTIMIZE_Oz;
                } else {
                    throw SNError(Error::ARGUMENT_ERROR,
                                  "Valid optimization levels are: O0, O1, O2, "
                                  "O3, Os, Oz");
                }
            } else if (IF_ANY_ARG("--silent", "-s")) {
                opts.run_opts.silent = true;
            } else if (IF_ANY_ARG("--jit", "-j")) {
                opts.run_opts.jit = true;
            } else if (IF_ANY_ARG("--file", "-f")) {
                CHECK_ARG("an input file")
                NEXT_ARGUMENT()
                opts.run_opts.file = current_arg;
            } else {
                throw SNError(
                        Error::ARGUMENT_ERROR,
                        FMT("Unexpected argument for the build command: %s", current_arg.c_str()));
            }
        }
    } else if (current_arg == "test") {
        opts.command = Options::Command::TEST;

        while (current_index < args.size() - 1) {
            NEXT_ARGUMENT();

            if (IF_ANY_ARG("--silent", "-s")) {
                opts.test_opts.silent = true;
            } else {
                throw SNError(
                        Error::ARGUMENT_ERROR,
                        FMT("Unexpected argument for the test command: %s", current_arg.c_str()));
            }
        }

        // TODO
        // TODO: optimization level for tests
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
                    throw SNError(Error::ARGUMENT_ERROR,
                                  "Can't have argument `--skip-cfg` if "
                                  "argument `--cfg` has been passed");
                }

                opts.init_opts.skip_cfg = true;
            } else {
                throw SNError(
                        Error::ARGUMENT_ERROR,
                        FMT("Unexpected argument for the init command: %s", current_arg.c_str()));
            }
        }
    } else {
        throw SNError(Error::ARGUMENT_ERROR, FMT("Unknown command found: %s", current_arg.c_str()));
    }

    return opts;
}

void CLI::help() {
    Logger::log("Snowball (C) MIT");
    Logger::log("Usage: snowball [command] [options]\n");
    Logger::log("Snowball Commands:");
    Logger::log("  build            - builds the current snowball project");
    Logger::log("  run              - build and execute the current "
                "snowball project");
    Logger::log("  test             - execute tests");
    Logger::log("  init             - create a new snowball project "
                "(in current "
                "directory)");
    Logger::log("  explain          - explain a snowball error");
    Logger::log("  help             - prints out help");
    Logger::log("");
    Logger::log("Try `snowball help [command]` for more information.");
}
} // namespace app
} // namespace snowball

#undef IF_ANY_ARG
#undef IF_ARG
#undef CHECK_ARG
#undef NEXT_ARGUMENT