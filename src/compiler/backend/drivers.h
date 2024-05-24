
#include <filesystem>

namespace snowball {
namespace driver {

enum WorkSpaceType {
  Build,
  Bin,
  Deps,
  Libs,
  Obj,
  Data
};

std::filesystem::path get_output_path(const Ctx& ctx, bool for_linking = false, bool for_object_file = false);
void initialize_paths(const Ctx& ctx);
std::filesystem::path get_workspace_path(const Ctx& ctx, WorkSpaceType type);
std::string get_cc(const Ctx& ctx);
std::string get_git(const Ctx& ctx);
std::filesystem::path get_snowball_home();
int run(const Ctx& ctx, const std::string& output);

}
}
