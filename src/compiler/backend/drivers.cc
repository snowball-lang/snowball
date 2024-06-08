
#include "app/cli.h"
#include "compiler/ctx.h"
#include "compiler/backend/drivers.h"
#include "compiler/utils/utils.h"
#include "compiler/utils/hash.h"

#include "compiler/globals.h"

namespace snowball {
namespace driver {

std::filesystem::path get_output_path(const Ctx& ctx, const std::string& name, bool for_linking, bool for_object_file) {
  auto emit_type = global.emit_type;
  auto output_name = name;
  if (for_object_file)
    output_name = utils::hash::hashString(name);
  auto workspace = for_linking ? WorkSpaceType::Bin : (for_object_file ? WorkSpaceType::Obj : WorkSpaceType::Build);
  auto default_output_path = get_workspace_path(ctx, workspace);
  if (for_object_file && global.emit_type == EmitType::Executable) {
    emit_type = EmitType::LlvmBc;
  }
  switch (emit_type) {
    case EmitType::Llvm:
      return default_output_path / (output_name + ".ll");
    case EmitType::LlvmBc:
      return default_output_path / (output_name + ".bc");
    case EmitType::Object:{
      switch (global.target) {
        case Target::Windows:
          return default_output_path / (output_name + ".obj");
        case Target::Linux:
          return default_output_path / (output_name + ".o");
        case Target::MacOS:
          return default_output_path / (output_name + ".dylib");
        default: sn_unreachable();
      }
    } break;
    case EmitType::Executable:{
      switch (global.target) {
        case Target::Windows:
          return default_output_path / (output_name + ".exe");
        case Target::Linux:
        case Target::MacOS:
          return default_output_path / output_name;
        default: sn_unreachable();
      }
    } break;
    case EmitType::Asm:{
      switch (global.target) {
        case Target::Windows:
          return default_output_path / (output_name + ".asm");
        case Target::Linux:
        case Target::MacOS:
          return default_output_path / (output_name + ".s");
        default: sn_unreachable();
      }
    } break;
    case EmitType::Ast:
      return default_output_path / (output_name + ".ast");
    case EmitType::Sil:
      return default_output_path / (output_name + ".sil");
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
  std::filesystem::create_directory(get_workspace_path(ctx, WorkSpaceType::Reky));
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
    case WorkSpaceType::Reky:
      return ".sn/reky";
    default: sn_unreachable();
  }
}

int run(const Ctx& ctx, const std::string& output) {
  std::vector<std::string> args;
  args.push_back(output);
  std::string cmd;
  for (auto& arg : args) {
    cmd += arg + " ";
  }
  return std::system(cmd.c_str());
}

std::string get_git(const Ctx& ctx) {
  if (auto git = std::getenv("SNOWBALL_GIT"); git != nullptr) {
    return git;
  }
  return "git";
}

std::filesystem::path get_snowball_home() {
  if (auto home = std::getenv("SNOWBALL_HOME"); home != nullptr) {
    return home;
  }
  auto home = std::getenv("HOME");
  if (home == nullptr) {
    home = std::getenv("USERPROFILE");
  }
  return std::filesystem::path(home) / ".snowball";
}

bool program_exists(const std::string& name) {
#ifdef SN_WIN
  return std::system(("where " + name + " > nul 2>&1").c_str()) == 0;
#else
  return std::system(("which " + name + " > /dev/null 2>&1").c_str()) == 0;
#endif
}

}
}
