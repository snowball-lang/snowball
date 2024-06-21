
#include "compiler/frontend/lint/linter.h"

namespace snowball {
namespace frontend {
namespace lint {

Linter::Linter(const Ctx& ctx, std::vector<Module>& modules)
  : GenericVisitor(ctx, modules) {
}

void Linter::visit(ast::VarDecl* node) {
  GenericVisitor::visit(node);
  if (node->is_used() == 0 && !utils::sw(node->get_name(), "_")) {
    warn(node->get_location(), fmt::format("variable '{}' is declared but never used", node->get_name()), Error::Info {
      .highlight = fmt::format("This variable has never been used"),
      .help = fmt::format("Prefix the variable name with an underscore to suppress this warning\nFor example: _{}", node->get_name()),
    });
  }
  if (node->get_type()->is_void()) {
    err(node->get_location(), fmt::format("variable '{}' cant have void as declaration type!", node->get_name()), Error::Info {
      .highlight = fmt::format("This variable has type 'void'"),
      .help = fmt::format("Variables cannot have type void, maybe remove the variable declaration?"),
    }, Error::Type::Err);
  }
}

} // namespace lint
} // namespace frontend
} // namespace snowball
