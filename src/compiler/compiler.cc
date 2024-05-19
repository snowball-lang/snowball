
#include "compiler/compiler.h"
#include "compiler/sil/binder.h"
#include "compiler/utils/logger.h"
#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/sema/check.h"
#include "compiler/backend/llvm/builder.h"
#include "compiler/backend/drivers.h"

#include "app/cli.h"

namespace snowball {
using namespace cli;
using namespace utils;

Compiler::Compiler(Ctx& ctx) : ctx(ctx) {
  driver::initialize_paths(ctx);
}

bool Compiler::compile() {
  // TODO: Iterate through the whole project and compile everything.
  //  For now, we will just do the input_file.
  CLI::get_package_config(ctx, ctx.config_path);
  ctx.root_package_config = ctx.package_config; 
  // TODO: Populate allowed_paths with all the paths in the project and in the dependencies.
  std::vector<std::filesystem::path> allowed_paths = {(ctx.package_config.value().project.path / "..").lexically_normal()};
  std::vector<frontend::Module> modules;
  std::vector<std::filesystem::path> object_files;
  bool is_object = ctx.emit_type == EmitType::Object || ctx.emit_type == EmitType::Executable;
  Logger::status("Project", F("{} v{} {}", ctx.package_config.value().project.name, 
    ctx.package_config.value().project.version, get_package_type_string()));
  auto start = std::chrono::high_resolution_clock::now();
  for (auto& path : allowed_paths) {
    // Change the project context to the current project (e.g. when changing directories)
    CLI::get_package_config(ctx, path / "sn.confy");
    // Display the current project being compiled
    auto project_path = ctx.package_config.value().project.path.string();
    project_path.erase(project_path.begin(), 
      project_path.begin() +
      ctx.package_config.value().project.path.parent_path().string().size());
    Logger::status("Compiling", frontend::NamespacePath::from_file(project_path).get_path_string());
    //Logger::progress("Compiling", i / allowed_paths.size()+1);
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
    auto output_file = driver::get_output_path(ctx, false, is_object); 
    object_files.push_back(output_file);
    builder->build(binder.get_modules());
    //builder->dump();
    builder->emit(output_file);
  }
  if (is_object) {
    auto output = driver::get_output_path(ctx, true);
    backend::LLVMBuilder::link(ctx, object_files, output);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  Logger::raw("");
  Logger::success(F("Compiled snowball project in {}ms!", duration));
  return EXIT_SUCCESS;
}

bool Compiler::compile(Ctx& ctx) {
  Compiler compiler(ctx);
  return compiler.compile();
}

std::string Compiler::get_package_type_string() {
  std::string output = "[";
  switch (ctx.emit_type) {
    case EmitType::Object: output += "object"; break;
    case EmitType::Executable: output += "executable"; break;
    case EmitType::Asm: output += "assembly"; break;
    case EmitType::Llvm: output += "llvm"; break;
    case EmitType::Sil: output += "sil"; break;
    case EmitType::Ast: output += "ast"; break;
  }
  switch (ctx.opt_level) {
    case OptLevel::Debug: output += " + debug"; break;
    case OptLevel::Release: output += " + release"; break;
    case OptLevel::ReleaseFast: output += " + release-fast"; break;
    case OptLevel::ReleaseWithDebug: output += " + release-with-debug"; break;
  }
  output += "]";
  switch (ctx.target) {
    case Target::Linux: output += " (linux)"; break;
    case Target::MacOS: output += " (macos)"; break;
    case Target::Windows: output += " (windows)"; break;
    case Target::Unknown: output += " (unknown)"; break;
  }
  return output;
}

} // namespace snowball