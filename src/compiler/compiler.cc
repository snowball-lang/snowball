
#include "compiler/compiler.h"

namespace snowball {

Compiler::Compiler(const Ctx& ctx) : ctx(ctx) {}

bool Compiler::compile() {
  return EXIT_SUCCESS;
}

bool Compiler::compile(const Ctx& ctx) {
  Compiler compiler(ctx);
  return compiler.compile();
}

} // namespace snowball