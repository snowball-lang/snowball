
#include <vector>
#include <string>

#ifndef __SNOWBALL_EXEC_CLI_H_
#define __SNOWBALL_EXEC_CLI_H_

namespace snowball {
    namespace exec {
        struct Options {
            // TODO: optimization level

            enum EmitType {
                EXECUTABLE,
                OBJECT,
                LLVM_IR
            };

            enum Optimization {
                OPTIMIZE_O0,
                OPTIMIZE_O1,
                OPTIMIZE_O2,
                OPTIMIZE_O3,
                OPTIMIZE_Os,
                OPTIMIZE_Oz
            };

            struct RunOptions {
                Optimization opt = OPTIMIZE_O1;
            } run_opts;

            struct BuildOptions {
                bool is_test = false;
                Optimization opt = OPTIMIZE_O1;
                EmitType emit_type = EXECUTABLE;
            } build_opts;

            struct ExplainOptions {
                // TODO

            } explain_opts;

            struct TestOptions {
                // TODO
            } test_opts;

            struct InitOptions {
                bool cfg = false;
                bool lib = false;
                bool yes = false;
                bool skip_cfg = false;
            } init_opts;


            enum Command {
                UNKNOWN = -1,

                BUILD,
                RUN,
                TEST,
                EXPLAIN,
                INIT
            } command = UNKNOWN;
        };

        class CLI {
            public:
                CLI(int argc, char** argv);

                Options parse();
                static void help();

            private:
                int current_index = 0;
                std::string current_arg;
                std::vector<std::string> args;
        };
    }
}

#endif // __SNOWBALL_EXEC_CLI_H_