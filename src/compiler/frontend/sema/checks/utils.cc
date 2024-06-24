
#include <cassert>

#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeChecker::GetResult TypeChecker::get_item(ast::Expr* expr, NameAccumulator acc) {
  auto loc = expr->get_location();
  if (const auto id = expr->as<ast::Ident>()) {
    auto path = acc.get_path(id->get_name());
    acc.add(id->get_name());
    if (auto item = universe.get_item(id->get_name()); 
      item.has_value() && acc.is_name()) {
      return {item, acc.get_name(), false};
    } else if (auto type = universe.get_type(path)) {
      return check_privacy({TypeCheckItem::create_type(type.value()), acc.get_name()}, loc);
    } else {
      for (auto& uuid : ctx.allowed_uuids) {
        auto new_path = uuid + path;
        if (auto fns = universe.get_fn_decl(new_path); fns.size() > 0) {
          return check_privacy({TypeCheckItem::create_fn_decl(fns), acc.get_name()}, loc);
        } else if (auto type = universe.get_type(new_path)) {
          return check_privacy({TypeCheckItem::create_type(type.value()), acc.get_name()}, loc);
        } else if (auto mod = search_module(new_path)) {
          return check_privacy({TypeCheckItem::create_module(mod.value()), acc.get_name()}, loc);
        }
      }
      return {std::nullopt, acc.get_name()};
    }
  } else if (auto member = expr->as<ast::MemberAccess>()) {
    auto [obj, obj_name, ignore_self] = get_item(member->get_const_object(), acc);
    assert(!ignore_self);
    if (!obj.has_value()) {
      return {std::nullopt, obj_name, false};
    }
    if (obj->is_type()) {
      if (member->get_access_type() != ast::MemberAccess::AccessType::Static) {
        err(member->get_location(), "use of type as value is not allowed", Error::Info {
          .highlight = "Expected a value but type is used",
          .help = "You cant use a type as a value in this context."
        }, Error::Type::Err, false);
        return {std::nullopt, obj_name, false};
      }
      // note: We use get_type again here in order to instantiate the type
      // TODO: Is this the best way to do this?
      return check_privacy(get_from_type(member, get_type(member->get_const_object())), loc);
    } else if (obj->is_module()) {
      auto mod = obj->get_module();
      if (member->get_access_type() != ast::MemberAccess::AccessType::Static) {
        err(member->get_location(), "use of module as value is not allowed", Error::Info {
          .highlight = "Expected a value but module is used",
          .help = "You cant use a module as a value in this context."
        }, Error::Type::Err, false);
        return {std::nullopt, obj_name, false};
      }
      acc.add(mod);
      return get_item(member->get_member(), acc);
    } else if (obj->is_var()) {
      if (member->get_access_type() == ast::MemberAccess::AccessType::Static) {
        err(member->get_location(), "use of variable as type is not allowed", Error::Info {
          .highlight = "Expected a type but variable is used",
          .help = "You cant use a variable as a type in this context."
        }, Error::Type::Err, false);
        return {std::nullopt, obj_name, false};
      }
      return check_privacy(get_from_type(member, obj->get_var()->get_type()), loc);
    } else if (obj->is_func()) {
      if (member->get_access_type() == ast::MemberAccess::AccessType::Static) {
        err(member->get_location(), "use of function as type is not allowed", Error::Info {
          .highlight = "Expected a type but function is used",
          .help = "You cant use a function as a type in this context."
        }, Error::Type::Err, false);
        return {std::nullopt, obj_name, false};
      }
      sn_assert(false, "not implemented (fn_decl member access)");
    }
    sn_assert(false, "Invalid member access object found!");
  } else {
    err(loc, "Expected identifier or member access but found something else", Error::Info {
      .highlight = "Invalid expression",
      .help = "We expected an identifier or member access here, but found something else."
    });
    return {std::nullopt, "", false};
  }
}

TypeChecker::GetResult TypeChecker::get_item(const NamespacePath& path, const SourceLocation& loc) {
  ast::Expr* expr = nullptr;
  for (size_t i = 0; i < path.size(); ++i) {
    if (i == 0) {
      assert(!expr);
      expr = ast::Ident::create(loc, path[i]);
    } else {
      assert(expr);
      expr = ast::MemberAccess::create(loc, expr, ast::Ident::create(loc, path[i]), ast::MemberAccess::AccessType::Static);
    }
  }
  return get_item(expr);
}

TypeChecker::GetResult TypeChecker::get_item(const std::string& name) {
  return get_item(NamespacePath({name}), SourceLocation::dummy());
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

ast::types::Type* TypeChecker::get_type(ast::Expr* expr, bool no_unknown) {
  auto [item, name, ignore_self] = get_item(expr);
  assert(!ignore_self);
  if (!item.has_value()) {
    auto dym = get_did_you_mean(name);
    err(expr->get_location(), "Coudnt find type named '" + name + "' in the current scope!", Error::Info {
      .highlight = fmt::format("Type '{}' not found!", name),
      .help = dym.has_value() 
        ? fmt::format("Theres a symbol with a close name called '{}'.\nDid you mean to use that instead?", dym.value()) 
        : "Maybe you forgot to import a module?"
    });
    return get_error_type();
  }
  if (item->is_type()) {
    std::vector<ast::types::Type*> generics = fetch_generics_from_node(expr);
    auto ty = deduce_type(item->get_type(), generics, expr->get_location());
    if (no_unknown && ty->is_deep_unknown()) {
      err(expr->get_location(), "Type should be known in this context", Error::Info {
        .highlight = fmt::format("Type '{}' should be known in this context", ty->get_printable_name()),
        .help = "Maybe you forgot to set a type to a variable or forgot a generic parameter?",
        .note = "The type '_' is used to represent an unknown type"
      });
    }
    return ty;
  } else {
    err(expr->get_location(), fmt::format("Expected type but '{}' is not a type", name), 
      Error::Info {
        .highlight = "Not a type",
        .help = "We expected a type here, but found something else. Maybe you forgot to import a module?"
      }, Error::Type::Err, false);
    return get_error_type();
  }
}

ast::types::Type* TypeChecker::get_type(const ast::TypeRef& tr, bool no_unknown) {
  if (auto as_ptr = tr.as_pointer()) {
    auto pointee = get_type(as_ptr->get_type());
    return ast::types::PointerType::create(pointee, as_ptr->is_const_pointer());
  }
  return get_type(tr.get_name(), no_unknown);
}

ast::types::Type* TypeChecker::get_type(const std::string& name) {
  return get_type(NamespacePath({name}));
}

ast::types::Type* TypeChecker::deduce_type(ast::types::Type* type, const std::vector<ast::types::Type*>& generics, const SourceLocation& loc) {
  if (auto as_class = type->as_class()) {
    auto decl = (ast::ClassDecl*)as_class->get_decl();
    if (!decl->is_complete()) {
      err(loc, "Class is not complete", Error::Info {
        .highlight = "This class is empty",
        .help = "The class you are trying to use is not complete, No methods or fields have been defined yet.",
        .note = "This is probably due to a circular dependency issue in your code."
      }, Error::Type::Err, false);
      return get_error_type();
    }
    llvm::StringMap<ast::types::Type*> deduced;
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
          for (auto& [key,_] : monorph.generics) {
            match = type_match(deduced[key], monorph.generics[key]);
          }
          if (match) {
            return monorph.decl->get_type();
          }
        }
      }
      // We do a second loop here in order to add cache. We dont need to check
      // the generics again, because we already did that in the cache checking above
      // If it passed the first time, it will pass the second time (I hope)
      for (size_t i = 0; i < decl->get_generics().size(); ++i) {
        auto gen = decl->get_generics()[i];
        std::vector<ast::types::Type*> constraints_args;
        for (auto& c : gen.get_constraints()) {
          if (!c.get_internal_type().has_value()) {
            // I really don't like this implementation, but it's the best think I could think of.
            // Generic constraints should support using types that are declared *after* the generic
            // declaration. This is a temporary solution until I find a better way to do this.
            // Basically, if we didn't find an internal type, we try to find it again.
            // In most cases, if we didn't find it the first time, it's probably because of a circular
            // dependency issue. Im primarily concerned about the performance of this and if this will
            // respect the current's context scope or not. (future me, please test this better!)
            c.set_internal_type(get_type(c));
          }
          assert(c.get_internal_type().has_value());
          constraints_args.push_back(c.get_internal_type().value());
        }
        check_generic_impls(deduced[gen.get_name()], constraints_args, loc);
      }
      auto clone = (ast::ClassDecl*)decl->clone();
      return monorphosize(clone, deduced, loc)->get_type();
    }
  } else if (type->is_self_type()) {
    if (generics.size() > 0) {
      err(loc, "No generics should be provided for this specific type", Error::Info {
        .highlight = "No generics needed",
        .help = "You provided generics for a type that should not have any. Maybe you forgot to remove them?",
        .note = F("This type points to '{}' in this context.\nIf you want to provide generics, you should use the full path to the type.\nFor example 'Foo<...>'", type->get_printable_name())
      }, Error::Type::Err, false);
    }
    return type->as_self_type()->get_self();
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

TypeChecker::GetResult TypeChecker::get_from_type(ast::MemberAccess* node, ast::types::Type* type) {
  auto member = node->get_member();
  auto member_name = member->get_name();
  auto full_name = type->get_printable_name() + "::" + printable_op(member_name);
  if (auto as_ref = type->as_reference()) {
    // We dont do a recursive call here, because we can only get the member
    // of the reference (in just one level deep)
    type = as_ref->get_ref();
  } else if (auto as_unknown = type->as_unknown()) {
    // Attempt to resolve the unknown type
    // If we cant resolve it, thats the best we can do
    type = get_universe().get_constraints().at(as_unknown->get_id());
  }
  bool dont_error = false;
  size_t tries = 0;
  ast::ClassDecl* as_class_decl = nullptr;
fetch_member:
  if (auto as_class = type->as_class(); as_class || as_class_decl) {
    if (!as_class_decl) {
      as_class_decl = as_class->get_decl();
    }
    size_t index = 0;
    for (auto& field : as_class_decl->get_vars()) {
      if (field->get_name() == member_name) {
        return {TypeCheckItem::create_var(field), full_name};
      }
      index++;
    }
    FunctionsVector methods;
    for (auto& method : as_class_decl->get_funcs()) {
      if (method->get_name() == member_name) {
        methods.push_back(method);
      }
    }
    if (methods.size() > 0) {
      return {TypeCheckItem::create_fn_decl(methods), full_name};
    }
  } else if (auto as_generic = type->as_generic()) {
    std::optional<GetResult> result;
    std::vector<std::string> names;
    bool found = false;
    for (auto& constraint : as_generic->get_constraints()) {
      names.push_back(constraint->get_printable_name());
      result = get_from_type(node, constraint);
      if (result.has_value() && found) {
        // TODO: Maybe we should just a append the functions to the list and let the
        //   function deduce the correct one
        err(node->get_location(), "Generic type has more than one member", Error::Info {
          .highlight = "Generic type has more than one member",
          .help = "You can only access one member of a generic type at a time."
        }, Error::Type::Err, false);
      }
      if (result.has_value()) {
        found = true;
      }
    }
    if (!found) {
      if (!dont_error)
        err(node->get_location(), "Coudnt find member named '" + printable_op(member_name) + "' in generic type '" + type->get_printable_name() + "'!", Error::Info {
          .highlight = fmt::format("Member '{}' not found in generic type '{}'", printable_op(member_name), type->get_printable_name()),
          .note = names.empty() ? "" : fmt::format("The generic type has the following constraints: {}", utils::join(names, ", "))
        });
      return {std::nullopt, full_name};
    }
    result->ignore_self = true;
    return *result;
  }
  if (!dont_error) {
    dont_error = true;
    for (; tries < type->get_extensions().size(); ++tries) {
      as_class_decl = type->get_extensions()[tries];
      goto fetch_member;
    }
  }
  if (!dont_error)
    err(node->get_location(), "Coudnt find member named '" + printable_op(member_name) + "' in class '" + type->get_printable_name() + "'!", Error::Info {
      .highlight = fmt::format("Member '{}' not found in class '{}'", printable_op(member_name), type->get_printable_name())
    });
  return {std::nullopt, full_name, false};
}

std::optional<NamespacePath> TypeChecker::search_module(const NamespacePath& path) {
  if (path.size() == 1 && path[0] == "crate") {
    auto mod_path = ctx.current_module->get_path();
    std::vector<std::string> parts;
    // We remove the amount of parts from the current module path
    // to get the crate path
    for (size_t i = 0; i < mod_path.size() - 1; ++i) {
      parts.push_back(mod_path[i]);
    }
    return NamespacePath(parts);
  }
  for (auto& mod : modules) {
    if (mod.get_path() == path) {
      return mod.get_path();
    }
  }
  return std::nullopt;
}

std::vector<ast::types::Type*> TypeChecker::fetch_generics_from_node(const ast::Node* node) {
  std::vector<ast::types::Type*> generics;
  if (auto id = node->as<ast::Ident>()) {
    auto idnt_generics = id->get_generics();
    generics.reserve(idnt_generics.size());
    for (auto& gen : idnt_generics) {
      generics.push_back(get_type(gen));
    }
  } else if (auto member = node->as<ast::MemberAccess>()) {
    return fetch_generics_from_node(member->get_member());
  }
  return generics;
}


ast::types::GenericType* TypeChecker::create_generic_type(ast::GenericDecl& decl) {
  // TODO: Create a cache system for generic types, to avoid creating over and over  
  auto generic = ast::types::GenericType::create(decl.get_name());
  for (auto& constraint : decl.get_constraints()) {
    auto ty = constraint.get_internal_type().has_value() 
      ? constraint.get_internal_type().value() 
      : get_type(constraint.get_name(), true);
    constraint.set_internal_type(ty);
    generic->add_constraints(ty);
  }
  return generic;
}

void TypeChecker::update_self_type() {
  sn_assert(ctx.current_class, "No current class found");
  auto self = ctx.current_class;
  auto self_ty = ast::types::SelfType::create(self);
  universe.add_item("Self", self_ty);
}

}
}
}
