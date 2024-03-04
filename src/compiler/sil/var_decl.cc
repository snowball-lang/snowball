
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::VarDecl* node) {
  if (node->get_used() == 0 && !utils::sw(node->get_name(), "_")) {
    err(node->get_location(), fmt::format("variable '{}' is declared but never used", node->get_name()), Error::Info {
      .highlight = fmt::format("This variable has never been used"),
      .help = fmt::format("Prefix the variable name with an underscore to suppress this warning\nFor example: _{}", node->get_name()),
    }, Error::Type::Warn);
  }
  get_type(node);
  std::optional<sil::Inst*> var_value = std::nullopt;
  if (auto value = node->get_value())
    var_value = accept(value.value());
  value = VarDecl::create(node->get_location(), node->get_type(), node->get_name(), *node, var_value, node->get_id());
  var_ids.insert({node->get_id(), value});
}

}
}
