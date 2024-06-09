
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::generate_global_scope(ast::TopLevelAst& ast, bool first) {
  if (first) {
    for (auto& decl : ast) { 
      if (auto class_decl = decl->as<ast::ClassDecl>()) {
        do_global_class(class_decl);
        class_decl->set_complete();
      }
    }
    return;
  }
  for (auto& decl : ast) {
    if (auto fn_decl = decl->as<ast::FnDecl>()) {
      do_global_func(fn_decl);
    } else if (auto class_decl = decl->as<ast::ClassDecl>()) {
      for (auto& method : class_decl->get_funcs()) {
        auto backup = ctx.current_class;
        ctx.current_class = class_decl;
        for (auto& generic : class_decl->get_generics())
          universe.add_item(generic.get_name(), create_generic_type(generic));
        do_global_func(method);
        ctx.current_class = backup;
      }
    }
  }
}

void TypeChecker::do_global_func(ast::FnDecl* fn_decl) {
  enter_scope();
  auto path = get_namespace_path(fn_decl->get_name());
  fn_decl->set_module_path(ctx.current_module->get_path());
  check_fn(fn_decl);
  if (fn_decl->get_link_name().has_value()) {
    auto link_name = fn_decl->get_link_name().value();
    for (auto& decl : external_declared) {
      if (decl == link_name) {
        err(fn_decl->get_location(), fmt::format("Function with linkage name '{}' already declared!", link_name), Error::Info {
          .highlight = "Function with same linkage name already declared!",
          .help = "Function with same linkage name already declared, to fix this change the linkage name",
          .see = "https://snowball-lang.gitbook.io/docs/language-reference/functions/external-functions"
        }, Error::Type::Err, false);
        break;
      }
    }
    external_declared.push_back(link_name);
  }
  check_for_entry(fn_decl);
  universe.add_fn_decl(path, fn_decl);
  if (fn_decl->get_generics().size() > 0) {
    create_generic_context(fn_decl->get_id());
  }
  exit_scope();
}

void TypeChecker::do_global_class(ast::ClassDecl* class_decl) {
  // We only define the class here, we don't check the methods
  // class methods are checked in the second pass
  enter_scope();
  auto path = get_namespace_path(class_decl->get_name());
  class_decl->set_module_path(ctx.current_module->get_path());
  std::vector<ast::types::Type*> generics;
  for (auto& generic : class_decl->get_generics()) {
    // TODO: Should we use `create_generic_type` here?
    auto generic_ty = ast::types::GenericType::create(generic.get_name());
    universe.add_item(generic.get_name(), generic_ty);
    generics.push_back(generic_ty);
  }
  auto class_type = ast::types::ClassType::create(class_decl, path, generics, class_decl->get_location());
  unify(class_decl->get_type(), class_type, class_decl->get_location());
  universe.add_type(path, class_type);
  if (class_decl->get_generics().size() > 0) {
    create_generic_context(class_decl->get_id());
  }
  exit_scope();
}

void TypeChecker::check_for_entry(ast::FnDecl* fn_decl) {
  if (fn_decl->get_name() != "main" 
      || !ctx.current_module->is_main
      || fn_decl->get_privacy() != ast::AttributedNode::Privacy::Public) {
    return;
  }
  if (has_entry_declared) {
    err(fn_decl->get_location(), "Multiple entry points found!", Error::Info {
      .highlight = "Multiple entry points found!",
      .help = "Multiple entry points found, to fix this remove the 'main' function from one of the modules",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/functions/program-entries"
    }, Error::Type::Err);
  }
  has_entry_declared = true;
  if (fn_decl->get_params().size() != 0) {
    err(fn_decl->get_location(), "Main function should not have any parameters!", Error::Info {
      .highlight = "Multiple parameters found!",
      .help = "Main function should not have any parameters, to use command line arguments use the 'std::env' module",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/functions/program-entries"
    }, Error::Type::Err);
  }
  auto ret_type = fn_decl->get_type()->as_func()->get_return_type();
  if (!ret_type->is_int() || !(ret_type->as_int()->get_bits() == 32)) {
    err(fn_decl->get_location(), "Main function should return an integer of 32 bits!", Error::Info {
      .highlight = "Return type is not 'i32'",
      .help = "Main function should return an integer of 32 bits, to return a value use 'return' statement",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/functions/program-entries"
    }, Error::Type::Err);
  }
  if (fn_decl->get_generics().size() > 0) {
    err(fn_decl->get_location(), "Main function should not have any generics!", Error::Info {
      .highlight = "Generics found!",
      .help = "Main function should not have any generics, to use generics in a function use a normal function",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/functions/program-entries"
    }, Error::Type::Err);
  }
  fn_decl->set_link_name("main");
  external_declared.push_back("main");
}

}
}
}
