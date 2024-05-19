
#include "compiler/ctx.h"
#include "compiler/backend/drivers.h"
#include "compiler/backend/llvm/builder.h"

namespace snowball {
namespace backend {

void LLVMBuilder::link(const Ctx& ctx, std::vector<std::filesystem::path>& paths, std::filesystem::path output) {
  auto cc = driver::get_cc(ctx);
  std::vector<std::string> args;
  args.push_back(cc);
  args.push_back("-o");
  args.push_back(output.string());
  for (auto& path : paths) {
    args.push_back(path.string());
  }
  args.push_back("-L");
  args.push_back(driver::get_workspace_path(ctx, driver::WorkSpaceType::Libs).string());
  for (auto& lib : ctx.package_config.value().build.linkage_libs) {
    args.push_back("-l" + lib);
  }
  if (ctx.static_lib) {
    args.push_back("-static");
  }
  if (ctx.emit_type != EmitType::Executable) {
    args.push_back("-flinker-output=dyn");
  }
  args.push_back("-no-pie");
  args.push_back("-lm");
  
  std::string cmd;
  for (auto& arg : args) {
    cmd += arg + " ";
  }
  std::system(cmd.c_str());
}

}
}
