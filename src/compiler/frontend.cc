
#include "app/cli.h"
#include "compiler/ctx.h"
#include "compiler/compiler.h"

#include "compiler/frontend/attrs/interp.h"

namespace snowball {
using namespace cli;
using namespace utils;

void Compiler::run_frontend() {
  auto attr_interp = initialize_attr_interpreter();
  attr_interp.register_builtin_instances();

  for (auto ipath = allowed_paths.rbegin(); ipath != allowed_paths.rend(); ++ipath) {
    auto path = *ipath;
    setup_project_context(path);
    
    auto package_ctx = ctx.package_config.value();
    auto project_name = package_ctx.project.name;
    
    Logger::status("Compiling", fmt::format("{} v{}", package_ctx.project.name, package_ctx.project.version));
    sn_assert(std::filesystem::exists(path), "Path does not exist (looking for {})", path.string());

    compile_project_sources(path, package_ctx.project.src, project_name, attr_interp);
  }
}

frontend::ast::attrs::AttrInterpreter Compiler::initialize_attr_interpreter() {
  return frontend::ast::attrs::AttrInterpreter::create();
}

void Compiler::setup_project_context(const std::filesystem::path& path) {
  CLI::get_package_config(ctx, path / "sn.confy");
}

void Compiler::compile_project_sources(const std::filesystem::path& path, const std::string& src, 
                                       const std::string& project_name, frontend::ast::attrs::AttrInterpreter& attr_interp) {
  auto src_path = path / src;

  auto module_root_path = frontend::NamespacePath::from_file(project_name);
  modules.push_back(frontend::Module({}, module_root_path, false));
  module_paths.push_back(module_root_path);
  progress_iteration += 0.5 / allowed_paths.size();

  for (auto& entry : std::filesystem::directory_iterator(src_path)) {
    if (entry.is_regular_file() && entry.path().extension() == ".sn" 
        && !utils::sw(entry.path().filename().string(), "_")) {
      compile_source_file(entry, project_name, attr_interp);
      print_compiling_bar(modules);
    } else if (entry.is_directory()) {
      compile_project_sources(entry.path().parent_path(), entry.path().filename().string(), project_name + "/" + entry.path().filename().string(), attr_interp);
    }
  }
}

void Compiler::compile_source_file(const std::filesystem::directory_entry& entry, const std::string& project_name,
                                   frontend::ast::attrs::AttrInterpreter& attr_interp) {
  auto timer_name = "module " + project_name + "::" + entry.path().filename().stem().string();
  timer.start(timer_name);
  
  auto source_file = std::make_shared<frontend::SourceFile>(entry);
  frontend::Lexer lexer(ctx, source_file);
  auto tokens = lexer.lex();
  
  if (lexer.handle_errors()) {
    stop_compilation();
  }
  
  frontend::Parser parser(ctx, source_file, tokens, attr_interp);
  auto ast_module = parser.parse(project_name);
  modules.push_back(ast_module);
  timer.stop(timer_name);
  
  modules.back().parent_crate = ast_module.get_path();
  module_paths.push_back(modules.back().get_path());
    
  if (parser.handle_errors()) {
    stop_compilation();
  }
}

}
