
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

#define SUCCESS (flags & static_cast<int>(UnifyFlags::JustCheck)) ? true : (a = b, true)

bool TypeChecker::unify(ast::types::Type*& a, ast::types::Type* b, 
                      const SourceLocation& loc, int flags) {
  bool just_check = flags & static_cast<int>(UnifyFlags::JustCheck);
  if (!a) {
    return SUCCESS;
  } else if (a->is_reference() && b->is_reference()) {
    return unify(a->as_reference()->get_mut_ref(), b->as_reference()->get_mut_ref(), loc, flags);
  } else if (a->is_pointer() && b->is_pointer()) {
    return unify(a->as_pointer()->get_mut_pointee(), b->as_pointer()->get_mut_pointee(), loc, flags);
  } else if (a->is_unknown()) {
    auto as_unknown = a->as_unknown();
    auto& constraint = universe.get_constraints().at(as_unknown->get_id());
    if (auto unk = constraint->as_unknown(); unk && unk->get_id() == as_unknown->get_id() && !just_check) {
      // Avoid infinite recursion
      // TODO: Is this the right way to handle this?
      return (constraint = b, true);
    } else {
      if (b->is_unknown()) {
        auto b_unknown = b->as_unknown();
        auto& b_constraint = universe.get_constraints().at(b_unknown->get_id());
        if (auto unk = b_constraint->as_unknown(); unk && unk->get_id() == b_unknown->get_id() && !just_check) {
          // Avoid infinite recursion
         return (b_constraint = a, true);
        } else if (b_unknown->get_id() == as_unknown->get_id()) {
          return SUCCESS;
        }
      } else if (!just_check) {
        return unify(constraint, b, loc, flags);
      }
    }
  } else if (b->is_unknown()) {
    auto b_unknown = b->as_unknown();
    auto& b_constraint = universe.get_constraints().at(b_unknown->get_id());
    if (auto unk = b_constraint->as_unknown(); unk && unk->get_id() == b_unknown->get_id() && !just_check) {
      // Avoid infinite recursion
      return (b_constraint = a, true);
    } else if (!just_check) {
      return unify(a, b_constraint, loc, flags);
    }
  } else if (a->is_class() && b->is_class()) {
    auto a_class = a->as_class();
    auto b_class = b->as_class();
    if (a_class->get_path() == b_class->get_path()) {
      auto a_generics = a_class->get_generics();
      auto b_generics = b_class->get_generics();
      if (a_generics.size() == b_generics.size()) {
        bool success = true;
        for (size_t i = 0; i < a_generics.size(); i++) {
          if (!unify(a_generics[i], b_generics[i], loc, flags)) {
            success = false;
          }
        }
        if (success) {
          return SUCCESS;
        }
      }
    }
  } else if (a->equals(b, flags & (int)UnifyFlags::IgnoreSelf)) {
    return SUCCESS;
  }
  if (just_check) return false;
  err(loc, fmt::format("Type mismatch between '{}' and '{}'", 
    a->get_printable_name(), b->get_printable_name()), Error::Info {
      .highlight = fmt::format("Expected '{}', found '{}'", 
        b->get_printable_name(), a->get_printable_name()),
      .help = "Try casting the type to the expected type by using a cast expression",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/casting"
    }, Error::Type::Err, false);
  a = get_error_type();
  return false;
}

bool TypeChecker::type_match(ast::types::Type* a, ast::types::Type* b, bool ignore_self) {
  int flags = static_cast<int>(UnifyFlags::JustCheck);
  if (ignore_self) flags |= static_cast<int>(UnifyFlags::IgnoreSelf);
  return unify(a, b, SourceLocation::dummy(), flags);
}

ast::types::Type* TypeChecker::try_get_unknown(ast::types::Type* type) {
  if (type->is_unknown()) {
    auto unknown = type->as_unknown();
    auto& constraint = universe.get_constraints().at(unknown->get_id());
    return constraint;
  }
  return type;
}

}
}
}
