
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
}

bool Compiler::compile() {
  try {
    allowed_paths = prepare_context(ctx);
    Logger::status("Project", F("{} v{} {}", ctx.package_config.value().project.name, 
      ctx.package_config.value().project.version, get_package_type_string()));
    auto start = std::chrono::high_resolution_clock::now();
    run_frontend();
    auto sil = run_middleend();
    auto sil_modules = sil.sil_modules;
    auto sil_insts = sil.sil_insts;
    bool is_object = ctx.emit_type == EmitType::Executable || ctx.emit_type == EmitType::Object
                  || ctx.emit_type == EmitType::LlvmBc || ctx.emit_type == EmitType::Asm
                  || ctx.emit_type == EmitType::Llvm;
    auto last_module_root_path = frontend::NamespacePath::dummy();
    timer.start("Building Output", true);
    for (unsigned i = 0; i < sil_modules.size(); i++) {
      auto module_root_path = module_paths.at(i);
      sil::Builder* builder;
      switch (ctx.emit_type) {
        case EmitType::Llvm:
        case EmitType::Object:
        case EmitType::Executable:
        case EmitType::LlvmBc:
        case EmitType::Asm: {
          builder = new backend::LLVMBuilder(ctx, sil_insts, module_root_path);
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
      builder->build(sil_modules);
    #if SNOWBALL_DUMP_OUTPUT == 1
      builder->dump();
    #endif
      builder->emit(output_file);
    }
    timer.stop("Building Output");
    auto output = driver::get_output_path(ctx, ctx.root_package_config.value().project.name, true);
    if (is_object) {
      timer.start("Linking", true);
      auto err = backend::LLVMBuilder::link(ctx, object_files, output);
      timer.stop("Linking");
      if (err) {
        return err;
      }
    }
    post_compile();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    if (ctx.build_mode == BuildMode::Run) {
      Logger::status("Running", ctx.root_package_config.value().project.name);
      return driver::run(ctx, output);
    }
    Logger::reset_status();
    Logger::raw("\n");
    Logger::success(F("Compiled snowball project in {}ms!", duration));
    return EXIT_SUCCESS;
  } catch (CompilationError& e) {
    return EXIT_FAILURE;
  }
}

bool Compiler::compile(Ctx& ctx) {
  Compiler compiler(ctx);
  return compiler.compile();
}

void Compiler::stop_compilation() {
  throw CompilationError();
}

void Compiler::post_compile() {
  if (ctx.timer != TimerType::None) {
    timer.print_all(ctx.timer);
  }
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

void Compiler::print_compiling_bar() {
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
  Logger::progress("Compiling", progress_iteration, utils::join(modules, ", "));
}

std::vector<std::filesystem::path> Compiler::prepare_context(Ctx& ctx, reky::RekyManager** reky) {
  driver::initialize_paths(ctx);

  CLI::get_package_config(ctx, ctx.config_path);
  ctx.root_package_config = ctx.package_config; 
  std::vector<std::filesystem::path> allowed_paths = {ctx.package_config.value().project.path};
  auto manager = reky::fetch_dependencies(ctx, allowed_paths);
  if (reky)
    *reky = manager;
  else delete manager;
  return allowed_paths;
}

} // namespace snowball