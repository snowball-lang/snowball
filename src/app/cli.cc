
#include "cli.h"

namespace snowball {
namespace cli {

CLI::CLI() {}

const Ctx CLI::parse(int argc, char** argv) {
  // TODO:
  Ctx ctx;
  ctx.build_mode = BuildMode::Build;
  ctx.input_file = "tests/main.sn";
  ctx.emit_type = EmitType::Llvm;
  return ctx;
}

}
}
