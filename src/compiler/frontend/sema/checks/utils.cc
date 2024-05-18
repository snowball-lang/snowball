
#include <cassert>

#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeChecker::GetResult TypeChecker::get_item(const ast::Expr* expr, NameAccumulator acc) {
  if (const auto id = expr->as<ast::Ident>()) {
    auto path = acc.get_path(id->get_name());
    acc.add(id->get_name());
    if (auto item = universe.get_item(id->get_name()); 
      item.has_value() && acc.is_name()) {
      return {item, acc.get_name()};
    } else if (auto type = universe.get_type(path)) {
      return {TypeCheckItem::create_type(type.value()), acc.get_name()};
    } else {
      for (auto& uuid : allowed_uuids) {
        auto new_path = uuid + path;
        if (auto fns = universe.get_fn_decl(new_path); fns.size() > 0) {
          return {TypeCheckItem::create_fn_decl({fns}), acc.get_name()};
        } else if (auto type = universe.get_type(new_path)) {
          return {TypeCheckItem::create_type(type.value()), acc.get_name()};
        } else if (auto mod = get_module(new_path); mod.has_value()) {
          return {TypeCheckItem::create_module(new_path), acc.get_name()};
        }
      }
      return {std::nullopt, acc.get_name()};
    }
  } else if (auto member = expr->as<ast::MemberAccess>()) {
    auto [obj, obj_name] = get_item(member->get_object(), acc);
    if (!obj.has_value()) {
      return {std::nullopt, obj_name};
    }
    if (obj->is_type()) {
      if (member->get_access_type() != ast::MemberAccess::AccessType::Static) {
        err(member->get_location(), "use of type as value is not allowed", Error::Info {
          .highlight = "Expected a value but type is used",
          .help = "You cant use a type as a value in this context."
        }, Error::Type::Err, false);
        return {std::nullopt, obj_name};
      }
      sn_assert(false, "not implemented (static member access for types)");
    } else if (obj->is_module()) {
      auto mod = obj->get_module();
      if (member->get_access_type() != ast::MemberAccess::AccessType::Static) {
        err(member->get_location(), "use of module as value is not allowed", Error::Info {
          .highlight = "Expected a value but module is used",
          .help = "You cant use a module as a value in this context."
        }, Error::Type::Err, false);
        return {std::nullopt, obj_name};
      }
      acc.add(mod);
      return get_item(member->get_member(), acc);
    } else if (obj->is_var()) {
      if (member->get_access_type() == ast::MemberAccess::AccessType::Static) {
        err(member->get_location(), "use of variable as type is not allowed", Error::Info {
          .highlight = "Expected a type but variable is used",
          .help = "You cant use a variable as a type in this context."
        }, Error::Type::Err, false);
        return {std::nullopt, obj_name};
      }
      sn_assert(false, "not implemented (var member access)");
    } else if (obj->is_func()) {
      if (member->get_access_type() == ast::MemberAccess::AccessType::Static) {
        err(member->get_location(), "use of function as type is not allowed", Error::Info {
          .highlight = "Expected a type but function is used",
          .help = "You cant use a function as a type in this context."
        }, Error::Type::Err, false);
        return {std::nullopt, obj_name};
      }
      sn_assert(false, "not implemented (fn_decl member access)");
    }
    sn_assert(false, "Invalid member access object found!");
  } else {
    sn_assert(false, "not implemented (invalid expr type for get_item)");
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

ast::types::Type* TypeChecker::get_type(const ast::Expr* expr) {
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
    std::vector<ast::types::Type*> generics;
    if (auto id = expr->as<ast::Ident>()) {
      auto idnt_generics = id->get_generics();
      generics.reserve(idnt_generics.size());
      for (auto& gen : idnt_generics) {
        generics.push_back(get_type(gen));
      }
    }
    return deduce_type(item->get_type(), generics, expr->get_location());
  } else {
    err(expr->get_location(), fmt::format("Expected type but '{}' is not a type", name), 
      Error::Info {
        .highlight = "Not a type",
        .help = "We expected a type here, but found something else. Maybe you forgot to import a module?"
      }, Error::Type::Err, false);
    return ast::types::ErrorType::create();
  }
}

ast::types::Type* TypeChecker::get_type(const ast::TypeRef& tr) {
  return get_type(tr.get_name());
}

ast::types::Type* TypeChecker::get_type(const std::string& name) {
  return get_type(NamespacePath({name}));
}

ast::types::Type* TypeChecker::deduce_type(ast::types::Type* type, const std::vector<ast::types::Type*>& generics, const SourceLocation& loc) {
  if (auto as_class = type->as_class()) {
    auto decl = (ast::ClassDecl*)as_class->get_decl();
    std::map<std::string, ast::types::Type*> deduced;
    if (generics.size() > 0) {
      for (size_t i = 0; i < decl->get_generics().size(); ++i) {
        auto gen = decl->get_generics().at(i);
        if (i < generics.size()) {
          deduced[gen.get_name()] = generics.at(i);
        } else {
          err(loc, "Not enough generics provided for class", Error::Info {
            .highlight = "Not enough generics",
            .help = "You didn't provide enough generics for this class. Maybe you forgot to specify some?"
          }, Error::Type::Err, false);
        }
      }
    }
    if (generics.size() < decl->get_generics().size()) {
      for (size_t i = generics.size(); i < decl->get_generics().size(); ++i) {
        // TODO: Check if the generic has a default value
        // if not, add unknown type
        deduced[decl->get_generics().at(i).get_name()] = get_unknown_type();
      }
    }
    if (as_class->get_generics().size() < generics.size()) {
      err(loc, "Too many generics provided for class", Error::Info {
        .highlight = "Too many generics",
        .help = "You provided too many generics for this class. Maybe you forgot to specify some?"
      }, Error::Type::Err, false);
    }
    if (deduced.size() > 0) {
      if (generic_class_registry.find(decl->get_id()) != generic_class_registry.end()) {
        for (auto& monorph : generic_class_registry[decl->get_id()]) {
          bool match = true;
          for (auto [key,_] : monorph.generics) {
            match = unify(deduced[key], monorph.generics[key], loc, true);
          }
          if (match) {
            return monorph.decl->get_type();
          }
        }
      }
      auto clone = (ast::ClassDecl*)decl->clone();
      return monorphosize(clone, deduced, loc)->get_type();
    }
  } else {
    if (generics.size() > 0) {
      err(loc, "Type has no generics to deduce", Error::Info {
        .highlight = type->get_printable_name() + " has no generics to deduce",
        .help = "This type has no generics to deduce. Maybe you forgot to specify them?"
      }, Error::Type::Err, false);
    }
  }
  return type;
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

void NameAccumulator::add(const NamespacePath& path) {
  for (auto part : path) {
    add(part);
  }
}
  
NamespacePath NameAccumulator::get_path(const std::string& name) const { 
  auto p = path;
  p.push(name);
  return p;
}

std::optional<const Module> TypeChecker::get_module(const NamespacePath& path) {
  for (auto& mod : modules) {
    if (mod.get_path() == path) {
      return mod;
    }
  }
  return std::nullopt;
}

}
}
}
