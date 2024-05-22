
#ifndef __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
#define __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__

#include "compiler/utils/id.h"
#include "compiler/frontend/ast/operators.h"
#include "compiler/frontend/ast/nodes/other.h"

namespace snowball {
namespace frontend {
namespace ast {

class Ident final : public Self<Ident>, public Expr, public GenericNode<ast::TypeRef> {
  std::string name;
  uint64_t var_id = 0;
public:
  Ident(const SourceLocation& location, const std::string& name, 
    std::optional<GenericNode> generics = std::nullopt)
    : Expr(location), GenericNode(generics), name(name) {}
  ~Ident() = default;

  auto get_name() const { return name; }
  auto get_var_id() const { return var_id; }
  void set_var_id(uint64_t id) { var_id = id; }

  static auto create(const SourceLocation& location, const std::string& name, 
    std::optional<GenericNode> generics = std::nullopt) {
    return new Ident(location, name, generics);
  }

  SN_VISIT()
  SN_DEFAULT_CLONE()
};

class MemberAccess final : public Self<MemberAccess>, public Expr {
public:
  enum AccessType {
    Default,
    Static,
  };
private:
  Expr* object;
  Ident* member;
  AccessType access_type;
  uint64_t var_id = 0;
  uint64_t index = 0;
  enum { Var, Index } kind = Var;
public:
  MemberAccess(const SourceLocation& location, Expr* object, Ident* member, AccessType access_type = AccessType::Default)
    : Expr(location), object(object), member(member), access_type(access_type) {}
  ~MemberAccess() = default;

  auto& get_object() { return object; }
  auto get_const_object() const { return object; }
  auto get_member() const { return member; }
  auto get_access_type() const { return access_type; }

  auto is_type_index() const { return kind == Index; }
  auto get_index() const { assert(is_type_index()); return index; }
  void set_index(uint64_t idx) { 
    kind = Index;
    index = idx; 
  }

  auto get_var_id() const { assert(!is_type_index()); return var_id; }
  void set_var_id(uint64_t id) { var_id = id; }

  static auto create(const SourceLocation& location, Expr* object, Ident* member, AccessType access_type = AccessType::Default) {
    return new MemberAccess(location, object, member, access_type);
  }

  SN_VISIT()
  SN_DEFAULT_CLONE()
};

class PointerType;

class TypeRef : public LocationHolder {
public:
  enum Type {
    Pointer = 0,
    Normal  = 1,
  };
private:
  Expr* name;
  Type tt = Type::Normal;
  friend PointerType;
public:
  TypeRef(const SourceLocation& location, Expr* name, Type tt)
    : LocationHolder(location), name(name), tt(tt) {}
  ~TypeRef() = default;

  auto get_name() const { return name; }

#define SUB_TYPE(nType, name, eName) \
  nType* as_##name() const { \
    if (tt == Type::eName) return (nType*)this; \
    return nullptr; } \
  bool is_##name() const { return tt == Type::eName; }
  SUB_TYPE(PointerType, pointer, Pointer)
#undef SUB_TYPE

  static auto create(const SourceLocation& location, Expr* name, Type tt = Type::Normal) {
    return TypeRef(location, name, tt);
  }
};

class PointerType : public TypeRef, public Self<PointerType> {
  bool is_const;
public:
  PointerType(const SourceLocation& location, TypeRef type, bool is_const)
    : TypeRef(location, type.get_name(), Pointer), is_const(is_const) {}
  ~PointerType() = default;

  auto get_type() const { return get_name(); }
  auto is_const_pointer() const { return is_const; }

  static auto create(const SourceLocation& location, TypeRef type, bool is_const) {
    return PointerType(location, type, is_const);
  }
};

class Number final : public Self<Number>, public Expr {
  std::string value;
public:
  Number(const SourceLocation& location, const std::string& value)
    : Expr(location), value(value) {}
  ~Number() = default;

  auto get_value() const { return value; }

  static auto create(const SourceLocation& location, const std::string& value) {
    return new Number(location, value);
  }

  SN_VISIT()
  SN_DEFAULT_CLONE()
};

class String final : public Self<String>, public Expr {
  std::string value;
  char prefix = 0;
public:
  String(const SourceLocation& location, const std::string& value, char prefix = 0)
    : Expr(location), value(value), prefix(prefix) {}
  ~String() = default;

  auto get_value() const { return value; }
  auto get_prefix() const { return prefix; }

  static auto create(const SourceLocation& location, const std::string& value, char prefix = 0) {
    return new String(location, value, prefix);
  }

  SN_VISIT()
  SN_DEFAULT_CLONE()
};

class BinaryOp final : public Self<BinaryOp>, public Expr {
  Operator op;
  std::optional<Expr*> lhs;
  std::optional<Expr*> rhs;
public:
  BinaryOp(const SourceLocation& location, Operator op, std::optional<Expr*> lhs = std::nullopt, std::optional<Expr*> rhs = std::nullopt)
    : Expr(location), op(op), lhs(lhs), rhs(rhs) {}
  ~BinaryOp() = default;

  auto get_op() const { return op; }
  auto get_lhs() const { return lhs; }
  auto get_rhs() const { return rhs; }

  static auto create(const SourceLocation& location, Operator op, std::optional<Expr*> lhs = std::nullopt, std::optional<Expr*> rhs = std::nullopt) {
    return new BinaryOp(location, op, lhs, rhs);
  }

  SN_VISIT()
  SN_DEFAULT_CLONE()
};

class Call final : public Expr, public GenericNode<TypeRef> {
  Expr* callee;
  std::vector<Expr*> args;
public:
  Call(const SourceLocation& location, Expr* callee, std::vector<Expr*> args, 
    const std::vector<TypeRef>& generics = {})
    : Expr(location), GenericNode(generics), callee(callee), args(args) {}
  ~Call() = default;

  auto get_callee() const { return callee; }
  auto& get_args() { return args; }
  Node* clone() const override;

  static auto create(const SourceLocation& location, Expr* callee, std::vector<Expr*> args,
    const std::vector<TypeRef>& generics = {}) {
    return new Call(location, callee, args, generics);
  }

  SN_VISIT()
};

class Reference final : public Self<Reference>, public Expr {
  Expr* expr;
public:
  Reference(const SourceLocation& location, Expr* expr)
    : Expr(location), expr(expr) {}
  ~Reference() = default;

  auto get_expr() const { return expr; }

  static auto create(const SourceLocation& location, Expr* expr) {
    return new Reference(location, expr);
  }

  SN_VISIT()
  SN_DEFAULT_CLONE()
};

}
}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_EXPR_H__
