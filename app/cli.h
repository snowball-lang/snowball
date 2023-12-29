
#include "../src/os/Driver.h"

#include <string>
#include <vector>

#ifndef __SNOWBALL_EXEC_CLI_H_
#define __SNOWBALL_EXEC_CLI_H_

namespace snowball {
namespace app {
struct Options {
  enum EmitType
  {
    EXECUTABLE,
    OBJECT,
    LLVM_IR,
    ASSEMBLY,
    SNOWBALL_IR,
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

  struct BuildOptions {
    bool is_test = false;
    bool is_bench = false;
    Optimization opt = OPTIMIZE_O1;
    EmitType emit_type = EXECUTABLE;

    bool silent = false;
    std::string file = "";
    std::string output = "";
    bool no_progress = false;
  } build_opts;

  struct RunOptions : BuildOptions {
    bool jit = false;
    std::vector<std::string> progArgs;
  } run_opts;

  struct TestOptions {
    bool silent = false;
    bool no_progress = false;
    Optimization opt = OPTIMIZE_O1;
  } test_opts;

  struct BenchmarkOptions {
    bool silent = false;
    bool no_progress = false;
    Optimization opt = OPTIMIZE_O1;
  } bench_opts;

  struct InitOptions {
    bool cfg = false;
    bool lib = false;
    bool yes = false;
    bool skip_cfg = false;

    std::string name = "";
    bool create_dir = false;
  } init_opts;

  struct DocsOptions {
    bool silent = false;
    bool no_progress = false;

    std::string base = "";
  } docs_opts;

  enum Command
  {
    UNKNOWN = -1,

    BUILD,
    RUN,
    TEST,
    INIT,
    DOCS,
    BENCH,
  } command = UNKNOWN;
};

using argsVector = std::vector<const char*>;

namespace cli {
namespace modes {

void run(Options& opts, argsVector& args);
void build(Options& opts, argsVector& args);
void test(Options& opts, argsVector& args);
void init(Options& opts, argsVector& args);
void docs(Options& opts, argsVector& args);
void bench(Options& opts, argsVector& args);

} // namespace modes
} // namespace cli

class CLI {
public:
  CLI(int argc, char** argv);
  Options parse();

private:
  int argc;
  char** argv;
};
} // namespace app
} // namespace snowball

#endif // __SNOWBALL_EXEC_CLI_H_