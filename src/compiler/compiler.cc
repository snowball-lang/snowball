
#include "compiler/compiler.h"
#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/location.h"

namespace snowball {

Compiler::Compiler(const Ctx& ctx) : ctx(ctx) {}

bool Compiler::compile() {
  // TODO: Iterate through the whole project and compile everything.
  //  For now, we will just do the input_file.
  auto source_file = std::make_shared<frontend::SourceFile>(ctx.input_file);
  frontend::Lexer lexer(ctx, source_file);
  auto tokens = lexer.lex();
  if (lexer.handle_errors()) {
    return EXIT_FAILURE;
  }
  frontend::Parser parser(ctx, source_file, tokens);
  auto module = parser.parse();
  if (parser.handle_errors()) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

bool Compiler::compile(const Ctx& ctx) {
  Compiler compiler(ctx);
  return compiler.compile();
}

} // namespace snowball