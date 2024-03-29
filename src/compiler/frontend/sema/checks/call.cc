
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Call* node) {
  std::vector<ast::types::Type*> arg_types;
  arg_types.reserve(node->get_args().size());
  for (auto& arg : node->get_args()) {
    arg->accept(this);
    arg_types.push_back(arg->get_type());
  }
  ast::types::Type* callee_type = nullptr;
  if (auto ident = node->get_callee()->as<ast::Ident>()) {
    auto item = get_item(ident).first;
    if (!item.has_value()) {
      auto dym = get_did_you_mean(ident->get_name());
      err(node->get_location(), fmt::format("use of undeclared identifier when calling '{}'", ident->get_name()), Error::Info {
        .highlight = 
          fmt::format("Variable or function '{}' not found. {}", ident->get_name(), 
          dym.has_value() ? fmt::format("Did you mean '{}'?", dym.value()) : ""),
        .help = fmt::format("Did you mean to declare a variable with the name '{}'?", ident->get_name())
      }, Error::Type::Err, false);
      unify(node->get_type(), ast::types::ErrorType::create());
      return;
    }
    if (item.value().is_type()) {
      err(node->get_location(), fmt::format("Types cant be called as values and type '{}' has been used as callee!", item.value().get_type()->get_printable_name()), Error::Info {
        .highlight = fmt::format("Symbol '{}' is a type!", item.value().get_type()->get_printable_name()),
        .help = fmt::format("Types cannot be called as functions. Did you mean to use a 'new' expression?")
      });
      unify(node->get_type(), ast::types::ErrorType::create());
      return;
    } else if (item.value().is_var()) {
      auto var = item.value().get_var();
      var->set_used();
      ident->set_var_id(var->get_id());
      callee_type = var->get_type();
    } else {
      auto fn_decls = item.value().get_funcs();
      auto fn = get_best_match(fn_decls, arg_types, node->get_location());
      ident->set_var_id(fn->get_id());
      callee_type = fn->get_type();
    }
  } else {
    node->get_callee()->accept(this);
    callee_type = node->get_callee()->get_type();
  }
  if (callee_type->is_error()) {
    unify(node->get_type(), callee_type);
    return;
  }
  if (!callee_type->is_func()) {
    err(node->get_location(), fmt::format("cannot call non-function type '{}'", callee_type->get_printable_name()), Error::Info {
      .highlight = callee_type->get_printable_name(),
      .help = fmt::format("Expected a function but '{}' is not a function", callee_type->get_printable_name())
    }, Error::Type::Err, false);
    unify(node->get_type(), ast::types::ErrorType::create());
    return;
  }
  for (size_t i = 0; i < arg_types.size(); i++) {
    if (!type_match(callee_type->as_func()->get_param_types()[i], arg_types[i])) {
      err(node->get_location(), fmt::format("Type mismatch in argument {} of call to function '{}'", i + 1, callee_type->get_printable_name()), Error::Info {
        .highlight = fmt::format("Type mismatch in argument {} of call to function '{}'", i + 1, callee_type->get_printable_name()),
        .help = fmt::format("Expected '{}' but found '{}'", callee_type->as_func()->get_param_types()[i]->get_printable_name(), arg_types[i]->get_printable_name())
      }, Error::Type::Err, false);
      unify(node->get_type(), ast::types::ErrorType::create());
      return;
    }
  }
  unify(node->get_type(), callee_type->as_func()->get_return_type());
}

}
}
}
