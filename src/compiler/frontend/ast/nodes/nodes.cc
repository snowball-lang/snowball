
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
  sn_assert(!is_abstract || !is_final || !is_override || !is_inline || !is_virtual || !is_operator, "Other attributes are not allowed with 'var'");
}

void AttributedNode::assert_is_type() const {
  sn_assert(!is_const || !is_mut || !is_static || !is_override || !is_virtual || !is_inline || !is_operator, "Other attributes are not allowed with 'type'");
  sn_assert(external == Extern::None, "External attribute is not allowed with 'type'");
}

#define SN_REGISTER_ACCEPT(n) void n::accept(ast::AstVisitor* v) { v->visit(this); }
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

void MemberAccess::set_var_id(uint64_t id) {
  var_id = id;
  member->set_var_id(id);
}

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
  if (body_clone) {
    clone->body = (Block*)body_clone->clone();
  } else if (body.has_value()) {
    // As last resort, clone the body. This should only happen when the function is 
    // generated by a class parent, which is generic
    clone->body = (Block*)body.value()->clone();
  }
  clone->generic_id = id;
  clone->get_type() = get_type();
  return clone;
}

uint64_t FnDecl::get_generic_id() const {
  if (generic_id.has_value()) {
    return generic_id.value();
  }
  return id;
}

Node* MemberAccess::clone() const {
  auto clone = Cloneable<MemberAccess>::default_clone(this);
  clone->object = (Expr*)object->clone();
  clone->member = (Ident*)member->clone();
  return clone;
}

Node* BinaryOp::clone() const {
  auto clone = Cloneable<BinaryOp>::default_clone(this);
  if (lhs)
    clone->lhs = (Expr*)lhs.value()->clone();
  if (rhs)
    clone->rhs = (Expr*)rhs.value()->clone();
  return clone;
}

Node* Reference::clone() const {
  auto clone = Cloneable<Reference>::default_clone(this);
  clone->expr = (Expr*)expr->clone();
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
  clone->callee = (Expr*)callee->clone();
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
  clone->get_type() = get_type();
  clone->id = id;
  return clone;
}

void FnDecl::create_body_clone() {
  if (get_generics().size() > 0 && body.has_value()) {
    body_clone = (Block*)body.value()->clone();
  }
}

bool FnDecl::is_generic_instanced() const {
  return generic_instanced;
}

bool FnDecl::should_generate() const {
  bool has_generic_params = false;
  for (const auto& param : params) {
    if (param->get_type()->is_deep_generic() || param->get_type()->is_deep_unknown()) {
      has_generic_params = true;
      break;
    }
  }
  bool parent_is_ok = true;
  if (parent_type) {
    if (auto as_class = parent_type.value()->as_class()) {
      parent_is_ok = !as_class->is_deep_generic()
        && !as_class->is_interface_decl();
    }
  }
  return (get_generics().size() == 0) && (!has_generic_params) && (parent_is_ok);
}

void FnDecl::set_generic_instanced() { generic_instanced = true; }
void ClassDecl::set_generic_instanced() { generic_instanced = true; }

bool ClassDecl::is_generic_instanced() const {
  return generic_instanced;
}

FnDecl::FnDecl(const SourceLocation& location, const std::string& name, 
    const std::vector<VarDecl*>& params, TypeRef return_type, std::optional<Block*> body,
    std::optional<GenericNode> generics, 
    const AttributedNode& attributes)
  : Stmt(location), GenericNode(generics), AttributedNode(attributes), name(name), params(params), 
      return_type(return_type), body(body) { 
        create_body_clone(); 
        switch (get_external()) {
          case Extern::C:
            set_link_name(name);
          default: break;
        }
      }

bool ClassDecl::has_vtable() const {
  bool has_virtual = false;
  if (implemented_interfaces.size() > 0) 
    return true;
  for (const auto& func : funcs) {
    if (func->get_virtual()) {
      has_virtual = true;
      break;
    }
  }
  return has_virtual;
}

}
}
}
