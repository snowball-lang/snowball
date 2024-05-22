
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace sil {

using Extern = frontend::ast::AttributedNode::Extern;

void Binder::visit(ast::VarDecl* node) {
  if (node->get_used() == 0 
      && !utils::sw(node->get_name(), "_") 
      && (ctx.current_func 
        ? ctx.current_func.value()->get_external() == Extern::None 
        : true
      )) {
    err(node->get_location(), fmt::format("variable '{}' is declared but never used", node->get_name()), Error::Info {
      .highlight = fmt::format("This variable has never been used"),
      .help = fmt::format("Prefix the variable name with an underscore to suppress this warning\nFor example: _{}", node->get_name()),
    }, Error::Type::Warn);
  }
  auto ty = get_type(node);
  std::optional<sil::Inst*> var_value = std::nullopt;
  if (auto value = node->get_value())
    var_value = accept(value.value());
  if (ty->is_void()) {
    err(node->get_location(), fmt::format("variable '{}' cant have void as declaration type!", node->get_name()), Error::Info {
      .highlight = fmt::format("This variable has type 'void'"),
      .help = fmt::format("Variables cannot have type void, maybe remove the variable declaration?"),
    }, Error::Type::Err);
  }
  value = VarDecl::create(node->get_location(), ty, node->get_name(), *node, var_value, node->get_id());
  var_ids.insert({node->get_id(), value});
}

}
}
