#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

namespace {

bool is_accessible(ast::AttributedNode::Privacy privacy, const NamespacePath& decl_path, 
  std::optional<const NamespacePath> current_path) {
  switch (privacy) {
    case ast::AttributedNode::Privacy::Public:
      return true;
    case ast::AttributedNode::Privacy::Crate:
      if (!current_path.has_value())
        return false;
      return decl_path[0] == current_path.value()[0];
    case ast::AttributedNode::Privacy::Private:
      if (!current_path.has_value())
        return false;
      return decl_path == current_path;
  }
  return false;
}

} // anonymous namespace

TypeChecker::GetResult TypeChecker::check_privacy(GetResult result, const SourceLocation& loc) {
  if (!result.item.has_value()) {
    return result;
  }

  auto item = result.item.value();
  auto current_path = ctx.current_module->get_path();

  bool is_valid = false;
  std::string item_name;
  std::string item_type;
  ast::AttributedNode::Privacy privacy;

  if (item.is_type()) {
    auto ty = item.get_type();
    auto as_class = ty->as_class();
    if (!as_class) {
      return result;
    }
    auto decl = as_class->get_decl();
    privacy = decl->get_privacy();
    item_name = decl->get_type()->get_printable_name();
    item_type = "type";
    is_valid = is_accessible(privacy, decl->get_module_path().value(), current_path);
  } else if (item.is_func()) {
    auto funcs = item.get_funcs();
    auto decl = funcs[0];
    privacy = decl->get_privacy();
    item_name = decl->get_name();
    item_type = "function";
    bool cont = true;
    if (auto parent = decl->get_parent_type()) {
      auto as_class = parent.value()->as_class();
      if (as_class) {
        if (ctx.current_class) {
          current_path = ctx.current_class->get_type()->as_class()->get_path();
        }
        is_valid = is_accessible(privacy, as_class->get_path(), current_path);
        cont = false;
      }
    }
    if (cont)
      is_valid = is_accessible(privacy, decl->get_module_path().value(), current_path);
  } else if (item.is_var()) {
    auto decl = item.get_var();
    privacy = decl->get_privacy();
    item_name = decl->get_name();
    item_type = "variable";
    bool cont = true;
    if (decl->get_parent_type().has_value()) {
      auto as_class = decl->get_parent_type().value()->as_class();
      if (as_class) {
        if (ctx.current_class) {
          current_path = ctx.current_class->get_type()->as_class()->get_path();
        }
        is_valid = is_accessible(privacy, as_class->get_path(), current_path);
        cont = false;
      }
    } 
    if (decl->get_module_path().has_value() && cont) {
      is_valid = is_accessible(privacy, decl->get_module_path().value(), current_path);
    } else if (cont) {
      is_valid = true;
    }
  } else if (item.is_module()) {
    // TODO: Implement module privacy checks
    // TODO: Maybe we DO need to check namespaces here but it's fine for global modules
    is_valid = true;
  } else {
    sn_unreachable();
  }

  if (!is_valid) {
    err(loc, "Attempted to access private " + item_type + " '" + item_name + "'", Error::Info{
      .highlight = "Not accessible from this context",
      .help = "Make the " + item_type + " public or move the usage to the same module",
      .note = std::string("The " + item_type + " is marked as ") + 
        (privacy == ast::AttributedNode::Privacy::Crate 
          ? "'public(crate)', but you are not on the\nsame crate context." 
          : "'private'")
    }, Error::Type::Err, false);
  }

  return result;
}

}
}
}
