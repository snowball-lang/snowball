
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::VarDecl* node) {
  sn_assert(ctx.current_func.has_value(), "No current function (global variables not supported yet)");
  if (node->get_used() == 0 && !utils::sw(node->get_name(), "_")) {
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
  //sn_assert(!ty->is_deep_generic(), "Type should not be deep generic at this point");
  value = VarDecl::create(node->get_location(), ty, node->get_name(), *node, var_value, node->get_id());
  ctx.current_func.value()->add_var_id(node->get_id(), value);
}

}
}
