
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

#include "compiler/globals.h"

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
    auto global_backup = global;
    if (run_backend(sil))
      return EXIT_FAILURE;
    // run_backend resets the global variable
    // more specifically the linking part (lld)
    global = global_backup;
    post_compile();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    if (ctx.build_mode == BuildMode::Run) {
      auto output = driver::get_output_path(ctx, ctx.root_package_config.value().project.name, true);
      Logger::status("Running", ctx.root_package_config.value().project.name + " (" + output.string() + ")");
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
  if (global.timer_type != TimerType::None) {
    timer.print_all();
  }
}

std::string Compiler::get_package_type_string() {
  std::string output = "[";
  switch (global.emit_type) {
    case EmitType::Object: output += "object"; break;
    case EmitType::Executable: output += "executable"; break;
    case EmitType::Asm: output += "assembly"; break;
    case EmitType::Llvm: output += "llvm"; break;
    case EmitType::Sil: output += "sil"; break;
    case EmitType::Ast: output += "ast"; break;
    case EmitType::LlvmBc: output += "llvm-bc"; break;
  }
  switch (global.opt_level) {
    case OptLevel::Debug: output += " + debug"; break;
    case OptLevel::Release: output += " + release"; break;
    case OptLevel::ReleaseFast: output += " + release-fast"; break;
    case OptLevel::ReleaseWithDebug: output += " + release-with-debug"; break;
  }
  output += "]";
  switch (global.target) {
    case Target::Linux: output += " (linux)"; break;
    case Target::MacOS: output += " (macos)"; break;
    case Target::Windows: output += " (windows)"; break;
    case Target::Unknown: output += " (unknown)"; break;
  }
  return output;
}

void Compiler::print_compiling_bar(std::vector<frontend::Module>& module_paths) {
  llvm::SmallVector<std::string> modules;
  auto progress = progress_iteration;
  for (size_t i = 0; i < module_paths.size(); i++) {
    auto& module = module_paths.at(i);
    if (i == 0 || module.get_path()[0] != module_paths.at(i-1).get_path()[0]) {
      bool all_generated = true;
      for (auto& module : module_paths) {
        if (!module.is_generated() && module.get_path()[0] == module_paths.at(i).get_path()[0]) {
          all_generated = false;
          break;
        }
      }
      if (all_generated) {
        progress += 0.2f / module_paths.size();
        continue;
      }
      if (module.is_generated())
        progress += 0.45f / (module_paths.size()/2);
      modules.push_back(module.get_path()[0]);
    }
  }
  Logger::progress("Compiling", progress, utils::join(modules, ", "));
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

float Compiler::progress_iteration = 0.0f;

} // namespace snowball