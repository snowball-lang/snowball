
#include <thread>
#include <vector>
#include <mutex>

#include "app/cli.h"
#include "compiler/ctx.h"
#include "compiler/compiler.h"
#include "compiler/globals.h"

#include "compiler/utils/thread.h"
#include "compiler/frontend/attrs/interp.h"

#include "compiler/backend/llvm/llvm.h"

#ifndef SNOWBALL_DUMP_OUTPUT
#define SNOWBALL_DUMP_OUTPUT 0
#endif

namespace snowball {
using namespace cli;
using namespace utils;

int Compiler::run_backend(const MiddleEndResult& sil) {
  auto sil_modules = sil.sil_modules;
  auto sil_insts = sil.sil_insts;
  bool is_object = global.emit_is_object();
  auto last_module_root_path = frontend::NamespacePath::dummy();
  timer.start("Building Output", true);
  {
    llvm::ThreadPool pool(llvm::hardware_concurrency(utils::get_num_threads()));
    for (unsigned i = 0; i < sil_modules.size(); i++) {
      auto module_root_path = module_paths.at(i);
      auto path_str = module_root_path.get_path_string();
      sil::Builder* builder;
      switch (global.emit_type) {
        case EmitType::Llvm:
        case EmitType::Object:
        case EmitType::Executable:
        case EmitType::LlvmBc:
        case EmitType::Asm: {
          builder = new backend::LLVMBuilder(ctx, sil_insts, module_root_path);
        } break;
        default: sn_assert(false, "Unknown emit type");
      }
      auto output_file = driver::get_output_path(ctx, path_str, false, is_object); 
      if (is_object) {
        auto emit_type = global.emit_type;
        // Compile to LLVM bitcode if we are compiling to an executable.
        global.emit_type = EmitType::LlvmBc;
        output_file = driver::get_output_path(ctx, path_str, false, is_object);
        global.emit_type = emit_type;
      }
      if (last_module_root_path != module_root_path) {
        object_files.push_back(output_file);
      }
      last_module_root_path = module_root_path;
      pool.async([=, &sil_modules] {
        builder->build(sil_modules);
        #if SNOWBALL_DUMP_OUTPUT == 1
          builder->dump();
        #endif
        builder->emit(output_file);
      });
    }
    pool.wait();
  }
  timer.stop("Building Output");
  auto output = driver::get_output_path(ctx, ctx.root_package_config.value().project.name);
  if (is_object) {
    timer.start("Linking", true);
    auto err = backend::LLVMBuilder::link(ctx, object_files, output);
    timer.stop("Linking");
    if (err) return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

}
