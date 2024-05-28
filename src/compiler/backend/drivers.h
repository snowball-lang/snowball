
#include <filesystem>

#ifndef __SNOWBALL_COMPILER_BACKEND_DRIVERS_H__
#define __SNOWBALL_COMPILER_BACKEND_DRIVERS_H__

namespace snowball {
namespace driver {

enum WorkSpaceType {
  Build,
  Bin,
  Deps,
  Libs,
  Obj,
  Data,
  Reky,
};

std::filesystem::path get_output_path(const Ctx& ctx, const std::string& name, bool for_linking = false, bool for_object_file = false);
void initialize_paths(const Ctx& ctx);
std::filesystem::path get_workspace_path(const Ctx& ctx, WorkSpaceType type);
std::string get_cc(const Ctx& ctx);
std::string get_git(const Ctx& ctx);
std::filesystem::path get_snowball_home();
int run(const Ctx& ctx, const std::string& output);
LinkerType get_linker_type(const Ctx& ctx);
bool program_exists(const std::string& name);
bool cc_is_clang(const Ctx& ctx);

}
}

#endif // __SNOWBALL_COMPILER_BACKEND_DRIVERS_H__
