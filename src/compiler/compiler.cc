
#include "compiler/compiler.h"
#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {

Compiler::Compiler(const Ctx& ctx) : ctx(ctx) {}

bool Compiler::compile() {
  // TODO: Iterate through the whole project and compile everything.
  //  For now, we will just do the input_file.
  std::vector<frontend::Module> modules;
  auto source_file = std::make_shared<frontend::SourceFile>(ctx.input_file);
  frontend::Lexer lexer(ctx, source_file);
  auto tokens = lexer.lex();
  if (lexer.handle_errors()) {
    return EXIT_FAILURE;
  }
  frontend::Parser parser(ctx, source_file, tokens);
  modules.push_back(parser.parse());
  if (parser.handle_errors()) {
    return EXIT_FAILURE;
  }
  frontend::sema::TypeChecker type_checker(ctx, modules);
  type_checker.check();
  if (type_checker.handle_errors()) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

bool Compiler::compile(const Ctx& ctx) {
  Compiler compiler(ctx);
  return compiler.compile();
}

} // namespace snowball