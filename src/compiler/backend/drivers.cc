
#include "app/cli.h"
#include "compiler/ctx.h"
#include "compiler/backend/drivers.h"
#include "compiler/utils/utils.h"
#include "compiler/utils/hash.h"

namespace snowball {
namespace driver {

std::filesystem::path get_output_path(const Ctx& ctx, const std::string& name, bool for_linking, bool for_object_file) {
  auto emit_type = ctx.emit_type;
  auto output_name = name;
  if (for_object_file)
    output_name = utils::hash::hashString(name);
  auto workspace = for_linking ? WorkSpaceType::Bin : (for_object_file ? WorkSpaceType::Obj : WorkSpaceType::Build);
  auto default_output_path = get_workspace_path(ctx, workspace);
  if (for_object_file && ctx.emit_type == EmitType::Executable) {
    emit_type = EmitType::LlvmBc;
  }
  switch (emit_type) {
    case EmitType::Llvm:
      return default_output_path / (output_name + ".ll");
    case EmitType::LlvmBc:
      return default_output_path / (output_name + ".bc");
    case EmitType::Object:{
      switch (ctx.target) {
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
      switch (ctx.target) {
        case Target::Windows:
          return default_output_path / (output_name + ".exe");
        case Target::Linux:
        case Target::MacOS:
          return default_output_path / output_name;
        default: sn_unreachable();
      }
    } break;
    case EmitType::Asm:{
      switch (ctx.target) {
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

std::string get_cc(const Ctx& ctx) {
  if (ctx.custom_cc != "") {
    return ctx.custom_cc;
  }
  if (auto cc = std::getenv("SNOWBALL_CC"); cc != nullptr) {
    return cc;
  }
  switch (ctx.target) {
    case Target::Windows:
      return "cl";
    case Target::Linux:
    case Target::MacOS:
      return "cc";
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

LinkerType get_linker_type(const Ctx& ctx) {
  if (ctx.linker_type == LinkerType::Detect) {
    if (program_exists("ld.mold") && ctx.target != Target::MacOS) {
      return LinkerType::Mold;
    } else if (program_exists("ld.lld")) {
      return LinkerType::Lld;
    }
  }
  return ctx.linker_type;
}

bool program_exists(const std::string& name) {
#ifdef SN_WIN
  return std::system(("where " + name + " > nul 2>&1").c_str()) == 0;
#else
  return std::system(("which " + name + " > /dev/null 2>&1").c_str()) == 0;
#endif
}

bool cc_is_clang(const Ctx& ctx, const std::string& cc) {
#ifdef SN_WIN
  return run(ctx, cc + " --version 2>&1 | findstr /C:\"clang version\"") == 0;
#else
  // Check if we find "clang version" in the output of the compiler
  return run(ctx, cc + " --version 2>&1 | grep -q 'clang version'") == 0;
#endif
}

}
}
