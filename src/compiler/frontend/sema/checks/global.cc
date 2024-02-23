
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::generate_global_scope(ast::TopLevelAst& ast) {
  for (auto& decl : ast) {
    if (auto fn_decl = decl->as<ast::FnDecl>()) {
      auto path = get_namespace_path(fn_decl->get_name());
      std::vector<ast::types::Type*> param_types;
      unsigned int i = 0;
      for (auto& param : fn_decl->get_params()) {
        unify(param_types[i], get_type(param.type));
      }
      sn_assert(param_types.size() == fn_decl->get_params().size(), "param_types.size() != fn_decl->get_params().size()");
      auto ret_type = get_type(fn_decl->get_return_type());
      auto func_type = ast::types::FuncType::create(param_types, ret_type);
      unify(decl->get_type(), func_type);
      assert(false && "not implemented");
    }
  }
}

}
}
}
