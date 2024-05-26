
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
#include "app/vendor/reky/src/reky.hpp"

#ifndef SNOWBALL_DUMP_OUTPUT
#define SNOWBALL_DUMP_OUTPUT 0
#endif

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
  std::vector<std::filesystem::path> allowed_paths = {(ctx.package_config.value().project.path).lexically_normal()};
  std::vector<frontend::Module> modules;
  // Unsigned is the number of modules appened for this path
  std::vector<frontend::NamespacePath> module_paths;
  std::vector<std::filesystem::path> object_files;
  Logger::status("Project", F("{} v{} {}", ctx.package_config.value().project.name, 
    ctx.package_config.value().project.version, get_package_type_string()));
  reky::fetch_dependencies(ctx, allowed_paths);
  static auto progress_i = 0.0;
  auto print_compiling_bar = [&]() {
    std::vector<std::string> modules;
    for (size_t i = 0; i < module_paths.size(); i++) {
      if (i == 0) {
        modules.push_back(module_paths.at(i).get_path_string());
        continue;
      } 
      if (module_paths.at(i) != module_paths.at(i-1)) {
        modules.push_back(module_paths.at(i).get_path_string());
      }
    }
    Logger::progress("Compiling", progress_i, utils::join(modules, ", "));
  }; 
  auto start = std::chrono::high_resolution_clock::now();
  for (auto ipath = allowed_paths.rbegin(); ipath != allowed_paths.rend(); ipath++) {
    auto path = *ipath;
    // Change the project context to the current project (e.g. when changing directories)
    CLI::get_package_config(ctx, path / "sn.confy");
    // TODO: Display the current project being compiled
    auto package_ctx = ctx.package_config.value();
    auto project_path = package_ctx.project.path.string();
    project_path.erase(project_path.begin(), 
      project_path.begin() +
      package_ctx.project.path.parent_path().parent_path().string().size());
    auto module_root_path = frontend::NamespacePath::from_file(project_path, true);
    Logger::status("Compiling", fmt::format("{} v{}", package_ctx.project.name, package_ctx.project.version));
    //Logger::progress("Compiling", i / allowed_paths.size()+1);
    sn_assert(std::filesystem::exists(path), "Path does not exist (looking for {})", path.string());
    // Iterate recursively through the project and the dependencies.
    auto src_path = path / package_ctx.project.src;
    for (auto& entry : std::filesystem::recursive_directory_iterator(src_path)) {
      if (entry.is_regular_file() && entry.path().extension() == ".sn") {
        auto source_file = std::make_shared<frontend::SourceFile>(entry);
        frontend::Lexer lexer(ctx, source_file);
        auto tokens = lexer.lex();
        if (lexer.handle_errors()) {
          return EXIT_FAILURE;
        }
        frontend::Parser parser(ctx, source_file, tokens);
        modules.push_back(parser.parse());
        modules.back().parent_crate = module_root_path;
        module_paths.push_back(module_root_path);
        if (parser.handle_errors()) {
          return EXIT_FAILURE;
        }
        print_compiling_bar();
      }
    }
    // We add the top module so that it can be accessed from 
    // other modules in the same project.
    modules.push_back(frontend::Module({}, module_root_path, modules.at(0).is_main));
    modules.back().parent_crate = module_root_path;
    module_paths.push_back(module_root_path);
    progress_i += 0.5 / allowed_paths.size();
  }
  print_compiling_bar();
  frontend::sema::TypeChecker type_checker(ctx, modules);
  type_checker.check();
  if (type_checker.handle_errors()) {
    return EXIT_FAILURE;
  }
  print_compiling_bar();
  sil::Binder binder(ctx, modules, type_checker.get_universe());
  binder.bind(type_checker.get_generic_registry());
  if (binder.handle_errors()) {
    return EXIT_FAILURE;
  }
  auto& sil_modules = binder.get_modules();
  // Add an output module since we need to have a main/general module to link everything to.
  auto output_namespace_path = frontend::NamespacePath(".libroot");
  sil_modules.push_back(std::make_shared<sil::Module>(output_namespace_path));
  module_paths.push_back(output_namespace_path);
  bool is_object = ctx.emit_type == EmitType::Executable || ctx.emit_type == EmitType::Object
                || ctx.emit_type == EmitType::LlvmBc || ctx.emit_type == EmitType::Asm
                || ctx.emit_type == EmitType::Llvm;
  auto last_module_root_path = frontend::NamespacePath::dummy();
  for (unsigned i = 0; i < sil_modules.size(); i++) {
    auto module_root_path = module_paths.at(i);
    sil::Builder* builder;
    switch (ctx.emit_type) {
      case EmitType::Llvm:
      case EmitType::Object:
      case EmitType::Executable:
      case EmitType::LlvmBc:
      case EmitType::Asm: {
        builder = new backend::LLVMBuilder(ctx, binder.get_insts(), module_root_path);
      } break;
      default: sn_assert(false, "Unknown emit type");
    }
    auto output_file = driver::get_output_path(ctx, module_root_path[0], false, is_object); 
    if (is_object) {
      auto emit_type = ctx.emit_type;
      // Compile to LLVM bitcode if we are compiling to an executable.
      ctx.emit_type = EmitType::LlvmBc;
      output_file = driver::get_output_path(ctx, module_root_path[0], false, is_object);
      ctx.emit_type = emit_type;
    }
    if (last_module_root_path != module_root_path) {
      object_files.push_back(output_file);
    }
    last_module_root_path = module_root_path;
    builder->build(binder.get_modules());
  #if SNOWBALL_DUMP_OUTPUT == 1
    builder->dump();
  #endif
    builder->emit(output_file);
  }
  auto output = driver::get_output_path(ctx, ctx.root_package_config.value().project.name, true);
  if (is_object) {
    backend::LLVMBuilder::link(ctx, object_files, output);
  }
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
  if (ctx.build_mode == BuildMode::Run) {
    Logger::status("Running", ctx.package_config.value().project.name);
    return driver::run(ctx, output);
  }
  Logger::reset_status();
  Logger::raw("\n");
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
    case EmitType::LlvmBc: output += "llvm-bc"; break;
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