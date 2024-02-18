
#include "compiler/compiler.h"
#include "compiler/frontend/ast/lexer.h"

namespace snowball {

Compiler::Compiler(const Ctx& ctx) : ctx(ctx) {}

bool Compiler::compile() {

  // TODO: Iterate through the whole project and compile everything.
  //  For now, we will just do the input_file.
  auto input_file = ctx.input_file;

  frontend::Lexer lexer(ctx);
  auto tokens = lexer.lex();
  if (lexer.handle_errors()) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

bool Compiler::compile(const Ctx& ctx) {
  Compiler compiler(ctx);
  return compiler.compile();
}

} // namespace snowball