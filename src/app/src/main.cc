
#include "cli.h"
#include "compiler/compiler.h"
#include "compiler/ctx.h"

using namespace snowball;

int main(int argc, char** argv) {
  cli::CLI cli;
  Ctx ctx = cli.parse(argc, argv);
  return Compiler::compile(ctx);
}
