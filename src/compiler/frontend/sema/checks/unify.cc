
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
  if (!a) return SUCCESS;
  if (a->is_int() && b->is_int()) {
    if (a->as_int()->get_bits() == b->as_int()->get_bits() &&
        a->as_int()->is_signed() == b->as_int()->is_signed())
      return SUCCESS;
  } else if (a->is_float() && b->is_float()) {
    if (a->as_float()->get_bits() == b->as_float()->get_bits())
      return SUCCESS;
  } else if (a->is_generic() && b->is_generic()) {
    if (a->get_printable_name() == b->get_printable_name())
      return SUCCESS;
  } else if (a->is_void() && b->is_void()) {
    return SUCCESS;
  } else if (a->is_class() && b->is_class()) {
    auto ac = a->as_class();
    auto bc = b->as_class();
    if (ac->get_path() == bc->get_path()) {
      if (ac->get_generics().size() == bc->get_generics().size()) {
        bool match = true;
        for (size_t i = 0; i < ac->get_generics().size(); i++) {
          if (!unify(ac->get_generics()[i], bc->get_generics()[i], loc, true)) {
            match = false;
            break;
          }
        }
        if (match) 
          return SUCCESS;
      }
    }
  } else if (a->is_reference() && b->is_reference()) {
    return unify(a->as_reference()->get_mut_ref(), b->as_reference()->get_mut_ref(), loc, just_check);
  } else if (a->is_pointer() && b->is_pointer()) {
    return unify(a->as_pointer()->get_mut_pointee(), b->as_pointer()->get_mut_pointee(), loc, just_check);
  } else if (a->is_error() || b->is_error()) {
    return SUCCESS;
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
        return unify(constraint, b, loc, just_check);
      }
    }
  } else if (a->is_func() && b->is_func()) {
    auto a_func = a->as_func();
    auto b_func = b->as_func();
    if (a_func->get_param_types().size() == b_func->get_param_types().size()) {
      bool match = true;
      bool ignore_self = flags & static_cast<int>(UnifyFlags::IgnoreSelf);
      assert(!(ignore_self && a_func->get_param_types().size() < 1));
      for (size_t i = ignore_self; i < a_func->get_param_types().size(); i++) {
        if (!unify(a_func->get_param_types()[i], b_func->get_param_types()[i], loc, true)) {
          match = false;
          break;
        }
      }
      if (match) {
        match = unify(a_func->get_return_type(), b_func->get_return_type(), loc, true);
        if (match) return SUCCESS;
      }
    }
  }
  if (just_check) return false;
  err(loc, fmt::format("Type mismatch between '{}' and '{}'", 
    a->get_printable_name(), b->get_printable_name()), Error::Info {
      .highlight = fmt::format("Expected '{}', found '{}'", 
        a->get_printable_name(), b->get_printable_name()),
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

}
}
}
