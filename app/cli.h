
#include <string>
#include <vector>

#ifndef __SNOWBALL_EXEC_CLI_H_
#define __SNOWBALL_EXEC_CLI_H_

namespace snowball {
namespace app {
struct Options {
    // TODO: optimization level

    enum EmitType
    {
        EXECUTABLE,
        OBJECT,
        LLVM_IR
    };

    enum Optimization
    {
        OPTIMIZE_O0 = 0x00,
        OPTIMIZE_O1 = 0x01,
        OPTIMIZE_O2 = 0x02,
        OPTIMIZE_O3 = 0x03,
        OPTIMIZE_Os = 0x04,
        OPTIMIZE_Oz = 0x05
    };

    struct RunOptions {
        Optimization opt = OPTIMIZE_O1;
        bool silent = false;
        bool jit = false;

        std::string file = "";
    } run_opts;

    struct BuildOptions {
        bool is_test = false;
        Optimization opt = OPTIMIZE_O1;
        EmitType emit_type = EXECUTABLE;

        bool silent = false;
        std::string file = "";
    } build_opts;

    struct ExplainOptions {
        // TODO

    } explain_opts;

    struct TestOptions {
        bool silent = false;
    } test_opts;

    struct InitOptions {
        bool cfg = false;
        bool lib = false;
        bool yes = false;
        bool skip_cfg = false;
    } init_opts;

    enum Command
    {
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
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_EXEC_CLI_H_