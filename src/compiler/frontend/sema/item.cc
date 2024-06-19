
#include "compiler/frontend/sema/ctx.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeCheckItem::TypeCheckItem(ast::types::Type* type)
  : kind(Kind::Type), data(type) {}

TypeCheckItem::TypeCheckItem(ast::VarDecl* var)
  : kind(Kind::Var), data(var) {}

TypeCheckItem::TypeCheckItem(const FunctionsVector& funcs)
  : kind(Kind::Func), data(funcs) {}

TypeCheckItem::TypeCheckItem(const NamespacePath& module)
  : kind(Kind::Module), data(module) {}

// Accessors
TypeCheckItem::Kind TypeCheckItem::get_kind() const { 
  return kind; 
}

ast::types::Type* TypeCheckItem::get_type() const {
  assert(is_type());
  return std::get<ast::types::Type*>(data);
}

ast::VarDecl* TypeCheckItem::get_var() const {
  assert(is_var());
  return std::get<ast::VarDecl*>(data);
}

const FunctionsVector& TypeCheckItem::get_funcs() const {
  assert(is_func());
  return std::get<FunctionsVector>(data);
}

const NamespacePath& TypeCheckItem::get_module() const {
  assert(is_module());
  return std::get<NamespacePath>(data);
}

// Type checkers
bool TypeCheckItem::is_type() const { 
  return kind == Kind::Type; 
}

bool TypeCheckItem::is_func() const { 
  return kind == Kind::Func; 
}

bool TypeCheckItem::is_var() const { 
  return kind == Kind::Var; 
}

bool TypeCheckItem::is_module() const { 
  return kind == Kind::Module; 
}

// Static factory methods
TypeCheckItem TypeCheckItem::create_type(ast::types::Type* type) {
  return TypeCheckItem(type);
}

TypeCheckItem TypeCheckItem::create_var(ast::VarDecl* var) { 
  return TypeCheckItem(var); 
}

TypeCheckItem TypeCheckItem::create_fn_decl(const FunctionsVector& funcs) { 
  return TypeCheckItem(funcs); 
}

TypeCheckItem TypeCheckItem::create_module(const NamespacePath& module) { 
  return TypeCheckItem(module); 
}

} // namespace sema
} // namespace frontend
} // namespace snowball
