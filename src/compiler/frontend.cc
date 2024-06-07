
#include "app/cli.h"
#include "compiler/ctx.h"
#include "compiler/compiler.h"

namespace snowball {
using namespace cli;
using namespace utils;

void Compiler::run_frontend() {
  for (auto ipath = allowed_paths.rbegin(); ipath != allowed_paths.rend(); ipath++) {
    auto path = *ipath;
    // Change the project context to the current project (e.g. when changing directories)
    CLI::get_package_config(ctx, path / "sn.confy");
    auto package_ctx = ctx.package_config.value();
    auto project_name = package_ctx.project.name;
    auto module_root_path = frontend::NamespacePath::from_file(project_name);
    Logger::status("Compiling", fmt::format("{} v{}", package_ctx.project.name, package_ctx.project.version));
    sn_assert(std::filesystem::exists(path), "Path does not exist (looking for {})", path.string());
    // Iterate recursively through the project and the dependencies.
    auto src_path = path / package_ctx.project.src;
    for (auto& entry : std::filesystem::recursive_directory_iterator(src_path)) {
      if (entry.is_regular_file() && entry.path().extension() == ".sn" && !utils::sw(entry.path().filename().string(), "_")) {
        auto timer_name = "module " + project_name + "::" + entry.path().filename().stem().string();
        timer.start(timer_name);
        auto source_file = std::make_shared<frontend::SourceFile>(entry);
        frontend::Lexer lexer(ctx, source_file);
        auto tokens = lexer.lex();
        if (lexer.handle_errors()) {
          stop_compilation();
        }
        frontend::Parser parser(ctx, source_file, tokens);
        modules.push_back(parser.parse());
        timer.stop(timer_name);
        modules.back().parent_crate = module_root_path;
        module_paths.push_back(module_root_path);
        if (parser.handle_errors()) {
          stop_compilation();
        }
        print_compiling_bar();
      }
    }
    // We add the top module so that it can be accessed from 
    // other modules in the same project.
    modules.push_back(frontend::Module({}, module_root_path, modules.back().is_main));
    modules.back().parent_crate = module_root_path;
    module_paths.push_back(module_root_path);
    progress_iteration += 0.5 / allowed_paths.size();
  }
}

}
