
#include "app/cli.h"
#include "compiler/ctx.h"
#include "compiler/backend/drivers.h"
#include "compiler/utils/utils.h"

namespace snowball {
namespace driver {

std::filesystem::path get_output_path(const Ctx& ctx, bool for_linking, bool for_object_file) {
  auto emit_type = ctx.emit_type;
  auto workspace = for_linking ? WorkSpaceType::Bin : (for_object_file ? WorkSpaceType::Obj : WorkSpaceType::Build);
  auto default_output_path = get_workspace_path(ctx, workspace);
  auto name = ctx.package_config.value().project.name;
  if (for_object_file && ctx.emit_type == EmitType::Executable) {
    emit_type = EmitType::Object;
  }
  switch (emit_type) {
    case EmitType::Llvm:
      return default_output_path / (name + ".ll");
    case EmitType::Object:{
      switch (ctx.target) {
        case Target::Windows:
          return default_output_path / (name + ".obj");
        case Target::Linux:
        case Target::MacOS:
          return default_output_path / (name + ".o");
        default: sn_unreachable();
      }
    } break;
    case EmitType::Executable:{
      switch (ctx.target) {
        case Target::Windows:
          return default_output_path / (name + ".exe");
        case Target::Linux:
        case Target::MacOS:
          return default_output_path / name;
        default: sn_unreachable();
      }
    } break;
    case EmitType::Asm:{
      switch (ctx.target) {
        case Target::Windows:
          return default_output_path / (name + ".asm");
        case Target::Linux:
        case Target::MacOS:
          return default_output_path / (name + ".s");
        default: sn_unreachable();
      }
    } break;
    case EmitType::Ast:
      return default_output_path / (name + ".ast");
    case EmitType::Sil:
      return default_output_path / (name + ".sil");
    default: sn_unreachable();
  }
}

void initialize_paths(const Ctx& ctx) {
  std::filesystem::create_directory(".sn");
  std::filesystem::create_directory(get_workspace_path(ctx, WorkSpaceType::Build));
  std::filesystem::create_directory(get_workspace_path(ctx, WorkSpaceType::Bin));
  std::filesystem::create_directory(get_workspace_path(ctx, WorkSpaceType::Deps));
  std::filesystem::create_directory(get_workspace_path(ctx, WorkSpaceType::Libs));
  std::filesystem::create_directory(get_workspace_path(ctx, WorkSpaceType::Obj));
  std::filesystem::create_directory(get_workspace_path(ctx, WorkSpaceType::Data));
}

std::filesystem::path get_workspace_path(const Ctx& ctx, WorkSpaceType type) {
  switch (type) {
    case WorkSpaceType::Build:
      return ".sn/build";
    case WorkSpaceType::Bin:
      return ".sn/bin";
    case WorkSpaceType::Deps:
      return ".sn/deps";
    case WorkSpaceType::Libs:
      return ".sn/libs";
    case WorkSpaceType::Obj:
      return ".sn/obj";
    case WorkSpaceType::Data:
      return ".sn/data";
    default: sn_unreachable();
  }
}

}
}
