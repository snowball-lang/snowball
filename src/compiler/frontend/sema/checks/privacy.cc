
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeChecker::GetResult TypeChecker::check_privacy(GetResult result, const SourceLocation& loc) {
  if (!result.item.has_value()) {
    return result;
  }
  if (result.item.value().is_type()) {
    auto ty = result.item.value().get_type();
    auto as_class = ty->as_class();
    if (!as_class) {
      return result;
    }
    auto decl = as_class->get_decl();
    auto privacy = decl->get_privacy();
    switch (privacy) {
      case ast::AttributedNode::Privacy::Public:
        return result;
      case ast::AttributedNode::Privacy::Crate:
        if (decl->get_module_path().value()[0] == ctx.current_module->get_path()[0]) {
          return result;
        }
        break;
      case ast::AttributedNode::Privacy::Private:
        if (decl->get_module_path() == ctx.current_module->get_path()) {
          return result;
        }
        break;
    }
    err(loc, "Attempted to access private type '" + as_class->get_printable_name() + "'", Error::Info {
      .highlight = "Not accessible from this context",
      .help = "Make the type public or move the usage to the same module",
      .note = std::string("The type is marked as ") + 
        (privacy == ast::AttributedNode::Privacy::Crate 
          ? "'public(crate)', but you are not on the\nsame crate context." 
          : "'private'")
    }, Error::Type::Err, false);
    return result;
  }
  sn_assert(false, "Not implemented (finish check_privacy)");
  return result;
}

}
}
}
