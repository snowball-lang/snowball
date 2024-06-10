
#include "compiler/frontend/sema/ctx.h"

namespace snowball {
namespace frontend {
namespace sema {

TypeCheckItem::TypeCheckItem(ast::types::Type* type, bool dont_deduce)
    : kind(Kind::Type), type(type), dont_deduce(dont_deduce) {}

TypeCheckItem::TypeCheckItem(ast::VarDecl* var)
    : kind(Kind::Var), var(var) {}

TypeCheckItem::TypeCheckItem(const std::vector<ast::FnDecl*>& funcs)
    : kind(Kind::Func), funcs(funcs) {}

TypeCheckItem::TypeCheckItem(const NamespacePath& module)
    : kind(Kind::Module), module(module) {}

// Accessors
TypeCheckItem::Kind TypeCheckItem::get_kind() const { 
    return kind; 
}

ast::types::Type* TypeCheckItem::get_type() const {
    assert(is_type());
    return type;
}

ast::VarDecl* TypeCheckItem::get_var() const {
    assert(is_var());
    return var;
}

const std::vector<ast::FnDecl*>& TypeCheckItem::get_funcs() const {
    assert(is_func());
    return funcs;
}

const NamespacePath& TypeCheckItem::get_module() const {
    assert(is_module());
    return module;
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
TypeCheckItem TypeCheckItem::create_type(ast::types::Type* type, bool dont_deduce) {
    return TypeCheckItem(type, dont_deduce);
}

TypeCheckItem TypeCheckItem::create_var(ast::VarDecl* var) { 
    return TypeCheckItem(var); 
}

TypeCheckItem TypeCheckItem::create_fn_decl(const std::vector<ast::FnDecl*>& funcs) { 
    return TypeCheckItem(funcs); 
}

TypeCheckItem TypeCheckItem::create_module(const NamespacePath& module) { 
    return TypeCheckItem(module); 
}

} // namespace sema
} // namespace frontend
} // namespace snowball
