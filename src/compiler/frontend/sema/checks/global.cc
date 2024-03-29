
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::generate_global_scope(ast::TopLevelAst& ast) {
  for (auto& decl : ast) {
    if (auto fn_decl = decl->as<ast::FnDecl>()) {
      universe.add_scope();
      auto path = get_namespace_path(fn_decl->get_name());
      for (auto& generic : fn_decl->get_generics())
        universe.add_item(generic.get_name(), ast::types::GenericType::create(generic.get_name()));
      std::vector<ast::types::Type*> param_types;
      unsigned int i = 0;
      for (auto& param : fn_decl->get_params()) {
        param_types.push_back(nullptr);
        assert(param->get_decl_type());
        unify(param_types[i], get_type(param->get_decl_type().value()), param->get_location());
        param->get_type() = param_types[i];
        i++;
      }
      sn_assert(param_types.size() == fn_decl->get_params().size(), "param_types.size() != fn_decl->get_params().size()");
      auto ret_type = get_type(fn_decl->get_return_type());
      auto func_type = ast::types::FuncType::create(param_types, ret_type, false);
      unify(decl->get_type(), func_type, fn_decl->get_return_type().get_location());
      universe.add_fn_decl(path, fn_decl);
      if (fn_decl->get_generics().size() > 0) {
        create_generic_context(fn_decl->get_id());
      }
      universe.remove_scope();
    }
  }
}

}
}
}
