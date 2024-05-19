
#include "compiler/compiler.h"
#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/sema/check.h"
#include "compiler/sil/binder.h"
#include "compiler/backend/llvm/builder.h"
#include "compiler/backend/drivers.h"

#include "app/cli.h"

namespace snowball {
using namespace cli;

Compiler::Compiler(Ctx& ctx) : ctx(ctx) {
  driver::initialize_paths(ctx);
}

bool Compiler::compile() {
  // TODO: Iterate through the whole project and compile everything.
  //  For now, we will just do the input_file.
  CLI::get_package_config(ctx, ctx.config_path);
  // TODO: Populate allowed_paths with all the paths in the project and in the dependencies.
  std::vector<std::filesystem::path> allowed_paths = {ctx.package_config.value().project.path};
  std::vector<frontend::Module> modules;
  for (auto& path : allowed_paths) {
    sn_assert(std::filesystem::exists(path), "Path does not exist (looking for {})", path.string());
    // Iterate recursively through the project and the dependencies.
    for (auto& entry : std::filesystem::recursive_directory_iterator(path)) {
      if (entry.is_regular_file() && entry.path().extension() == ".sn") {
        auto source_file = std::make_shared<frontend::SourceFile>(entry);
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
      }
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
    sil::Builder* builder;
    switch (ctx.emit_type) {
      case EmitType::Llvm:
      case EmitType::Object:
      case EmitType::Executable:
      case EmitType::Asm: {
        builder = new backend::LLVMBuilder(ctx, binder.get_insts());
      } break;
      default: sn_assert(false, "Unknown emit type");
    }
    bool is_object = ctx.emit_type == EmitType::Object || ctx.emit_type == EmitType::Executable;
    auto output_file = driver::get_output_path(ctx, false, is_object); 
    builder->build(binder.get_modules());
    builder->dump();
    builder->emit(output_file);
  }
  return EXIT_SUCCESS;
}

bool Compiler::compile(Ctx& ctx) {
  Compiler compiler(ctx);
  return compiler.compile();
}

} // namespace snowball