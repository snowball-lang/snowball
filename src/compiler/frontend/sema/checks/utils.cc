
#include <cassert>

#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeChecker::GetResult TypeChecker::get_item(ast::Expr* expr, NameAccumulator acc) {
  if (auto id = expr->as<ast::Ident>()) {
    auto path = acc.get_path(id->get_name());
    acc.add(id->get_name());
    if (auto item = universe.get_item(id->get_name()); 
      item.has_value() && acc.is_name()) {
      return {item, acc.get_name()};
    } else if (auto type = universe.get_type(path)) {
      return {TypeCheckItem::create_type(type.value()), acc.get_name()};
    } else {
      for (auto& uuid : allowed_uuids) {
        if (auto fns = universe.get_fn_decl(uuid + path); fns.size() > 0) {
          return {TypeCheckItem::create_fn_decl({fns}), acc.get_name()};
        }
      }
      return {std::nullopt, acc.get_name()};
    }
  } /*else if (auto member = expr->as<ast::MemberExpr>()) {
    // TODO: Check if it's static or not
    acc.add(member->get_name());
    return get_item(member->get_expr(), acc);
  }*/ else {
    sn_assert(false, "not implemented");
  }
}

TypeChecker::GetResult TypeChecker::get_item(const NamespacePath& path) {
  ast::Expr* expr = nullptr;
  for (size_t i = 0; i < path.size(); ++i) {
    if (i == 0) {
      assert(!expr);
      expr = ast::Ident::create(SourceLocation::dummy(), path[i]);
    } else {
      sn_assert(false, "not implemented");
      //assert(expr);
      //expr = ast::MemberExpr::create(expr, path[i]);
    }
  }
  return get_item(expr);
}

TypeChecker::GetResult TypeChecker::get_item(const std::string& name) {
  return get_item(NamespacePath({name}));
}   

ast::types::Type* TypeChecker::get_type(const NamespacePath& path) {
  ast::Expr* expr = nullptr;
  for (size_t i = 0; i < path.size(); ++i) {
    if (i == 0) {
      assert(!expr);
      expr = ast::Ident::create(SourceLocation::dummy(), path[i]);
    } else {
      sn_assert(false, "not implemented");
      //assert(expr);
      //expr = ast::MemberExpr::create(expr, path[i]);
    }
  }
  return get_type(expr);
}

ast::types::Type* TypeChecker::get_type(ast::Expr* expr) {
  auto [item, name] = get_item(expr);
  if (!item.has_value()) {
    auto dym = get_did_you_mean(name);
    err(expr->get_location(), "Coudnt find type named '" + name + "' in the current scope!", Error::Info {
      .highlight = fmt::format("Type '{}' not found!", name),
      .help = dym.has_value() 
        ? fmt::format("Theres a symbol with a close name called '{}'.\nDid you mean to use that instead?", dym.value()) 
        : "Maybe you forgot to import a module?"
    });
    return ast::types::ErrorType::create();
  }
  if (item->is_type()) {
    return item->get_type();
  } else {
    err(expr->get_location(), fmt::format("Expected type but '{}' is not a type", name), 
      Error::Info {
        .highlight = "Not a type",
        .help = "We expected a type here, but found something else. Maybe you forgot to import a module?"
      }, Error::Type::Err, false);
    return ast::types::ErrorType::create();
  }
}

ast::types::Type* TypeChecker::get_type(ast::TypeRef& tr) {
  return get_type(tr.get_name());
}

ast::types::Type* TypeChecker::get_type(const std::string& name) {
  return get_type(NamespacePath({name}));
}

void NameAccumulator::add(const std::string& part, const std::string& name) {
  if (name.empty()) {
    return add(part, part);
  }
  path.push(part);
  if (!this->name.empty()) {
    this->name += "::";
  }
  this->name += name;
}
  
NamespacePath NameAccumulator::get_path(const std::string& name) const { 
  auto p = path;
  p.push(name);
  return p;
}

}
}
}
