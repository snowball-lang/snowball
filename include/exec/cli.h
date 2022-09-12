
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

            struct RunOptions {

            } run_opts;

            struct BuildOptions {
                bool is_test = false;
                EmitType emit_type = EXECUTABLE;
            } build_opts;

            struct ExplainOptions {
                // TODO

            } explain_opts;

            struct TestOptions {
                // TODO
            } test_opts;

            struct InitOptions {
                // TODO
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