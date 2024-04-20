
#include "compiler/frontend/ast/nodes.h"
#include "compiler/utils/utils.h"
#include "compiler/frontend/ast/visitors.h"

namespace snowball {
namespace frontend {
namespace ast {

void AttributedNode::assert_is_func() const {
  sn_assert(!is_abstract || !is_final || !is_const, "Other attributes are not allowed with 'func'");
}

void AttributedNode::assert_is_var() const {
  sn_assert(!is_abstract || !is_final || !is_override || !is_inline || !is_virtual, "Other attributes are not allowed with 'var'");
}

void AttributedNode::assert_is_type() const {
  sn_assert(!is_const || !is_mut || !is_static || !is_override || !is_virtual || !is_inline, "Other attributes are not allowed with 'type'");
  sn_assert(external == Extern::None, "External attribute is not allowed with 'type'");
}

#define SN_REGISTER_ACCEPT(n) void n::accept(ast::AstVisitor* v) { v->visit(this); }
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

Node* Block::clone() const {
  std::vector<Node*> new_stmts;
  new_stmts.reserve(stmts.size());
  for (auto stmt : stmts) {
    new_stmts.push_back(stmt->clone());
  }
  auto clone = Cloneable<Block>::default_clone(this);
  clone->stmts = new_stmts;
  return clone;
}

Node* FnDecl::clone() const {
  std::vector<VarDecl*> new_params;
  new_params.reserve(params.size());
  for (auto param : params) {
    assert(param->is<VarDecl>());
    // raw cast, we know it's a VarDecl
    new_params.push_back((VarDecl*)param->clone());
  }
  auto clone = Cloneable<FnDecl>::default_clone(this);
  clone->params = new_params;
  clone->body = (Block*)body_clone->clone();
  return clone;
}

Node* Call::clone() const {
  std::vector<Expr*> new_args;
  new_args.reserve(args.size());
  for (auto arg : args) {
    new_args.push_back((Expr*)arg->clone());
  }
  auto clone = Cloneable<Call>::default_clone(this);
  clone->args = new_args;
  return clone;
}

Node* VarDecl::clone() const {
  std::optional<Expr*> value_clone;
  if (value.has_value()) {
    value_clone = (Expr*)value.value()->clone();
  }
  auto clone = Cloneable<VarDecl>::default_clone(this);
  clone->value = value_clone;
  return clone;
}

Node* ClassDecl::clone() const {
  std::vector<FnDecl*> new_funcs;
  std::vector<VarDecl*> new_vars;
  new_funcs.reserve(funcs.size());
  new_vars.reserve(vars.size());
  for (auto func : funcs) {
    new_funcs.push_back((FnDecl*)func->clone());
  }
  for (auto var : vars) {
    new_vars.push_back((VarDecl*)var->clone());
  }
  auto clone = Cloneable<ClassDecl>::default_clone(this);
  clone->funcs = new_funcs;
  clone->vars = new_vars;
  return clone;
}

void FnDecl::create_body_clone() {
  if (get_generics().size() > 0) {
    body_clone = (Block*)body->clone();
  }
}

bool FnDecl::is_generic_instanced() const {
  return generic_instanced;
}

void FnDecl::set_generic_instanced() { generic_instanced = true; }
void ClassDecl::set_generic_instanced() { generic_instanced = true; }

}
}
}
