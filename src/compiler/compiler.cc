
#include "compiler/compiler.h"
#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/sema/check.h"
#include "compiler/sil/binder.h"
#include "compiler/backend/llvm/builder.h"

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
  sil::Binder binder(ctx, modules, type_checker.get_universe());
  binder.bind(type_checker.get_generic_registry());
  if (binder.handle_errors()) {
    return EXIT_FAILURE;
  }
  switch (ctx.emit_type) {
    case EmitType::Llvm:
    case EmitType::Object:
    case EmitType::Executable:
    case EmitType::Asm: {
      backend::LLVMBuilder llvm_builder(ctx, binder.get_insts());
      llvm_builder.build(binder.get_modules());
      llvm_builder.dump();
    } break;
    default: sn_assert(false, "Unknown emit type");
  }
  return EXIT_SUCCESS;
}

bool Compiler::compile(const Ctx& ctx) {
  Compiler compiler(ctx);
  return compiler.compile();
}

} // namespace snowball