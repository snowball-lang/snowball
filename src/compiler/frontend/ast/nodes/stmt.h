
#ifndef __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
#define __SNOWBALL_FRONTEND_AST_NODES_STMT_H__

#include <optional>
#include <string>
#include <vector>

#include "compiler/utils/id.h"
#include "compiler/utils/clone.h"
#include "compiler/frontend/ast/nodes/expr.h"
#include "compiler/frontend/ast/nodes/other.h"

#include "compiler/frontend/ast/borrows.h"

namespace snowball {
namespace frontend {
namespace ast {

// --- Module Holder (declare here to avoid circular dependency) ---

class ModuleHolder {
  std::optional<NamespacePath> path;
public:
  ModuleHolder() : path(std::nullopt) {}
  ~ModuleHolder() = default;

  void set_module_path(const NamespacePath& path) { this->path = path; }
  auto get_module_path() const { return path; }
};

// --- Forward declarations ---

class TypeRef;
class VarDecl;

// --- Stmt ---

class Block final : public Stmt {
  std::vector<Node*> stmts;

public:
  Block(const SourceLocation& location, const std::vector<Node*>& stmts)
    : Stmt(location)
    , stmts(stmts) {}
  ~Block() = default;
  Node* clone() const override;
  auto& get_stmts() { return stmts; }
  static auto create(const SourceLocation& location, const std::vector<Node*>& stmts) {
    return new Block(location, stmts);
  }

  SN_VISIT()
};

class FnDecl final : public Stmt,
                     public GenericNode<>,
                     public AttributedNode,
                     public Identified,
                     public ModuleHolder {
private:
  std::string name;
  std::vector<VarDecl*> params;
  TypeRef return_type;
  std::optional<Block*> body;
  // This is a clone of the body, used for cloning the function,
  // and fetching the body without it not being typechecked
  Block* body_clone = nullptr;
  bool generic_instanced = false;
  std::optional<types::Type*> parent_type = std::nullopt;
  std::optional<uint64_t> generic_id = std::nullopt;

public:
  FnDecl(const SourceLocation& location, const std::string& name,
         const std::vector<VarDecl*>& params, TypeRef return_type,
         std::optional<Block*> body, std::optional<GenericNode> generics = std::nullopt,
         const AttributedNode& attributes = AttributedNode());
  ~FnDecl() = default;
  auto& get_name() const { return name; }
  auto& get_params() { return params; }
  auto& get_return_type() { return return_type; }
  auto get_body() const { return body; }
  void create_body_clone();
  Node* clone() const override;
  bool is_generic_instanced() const;
  void set_generic_instanced();
  bool should_generate() const;
  void set_parent_type(types::Type* type) { parent_type = type; }
  auto get_parent_type() const { return parent_type; }
  uint64_t get_generic_id() const;
  static auto
  create(const SourceLocation& location, const std::string& name,
         const std::vector<VarDecl*>& params, TypeRef return_type,
         std::optional<Block*> body, std::optional<GenericNode> generics = std::nullopt,
         const AttributedNode& attributes = AttributedNode()) {
    return new FnDecl(location, name, params, return_type, body, generics, attributes);
  }

  SN_VISIT()
};

class VarDecl final : public Stmt, public AttributedNode, public Identified, 
    public ModuleHolder, public Borrowable {
  std::string name;
  std::optional<TypeRef> decl_type;
  std::optional<Expr*> value;
  std::optional<FnDecl*> arg_for = std::nullopt;
  std::optional<types::Type*> parent_type = std::nullopt; // Direct parent type
  std::optional<uint64_t> index; // Member access index
  unsigned int used = 0;

public:
  VarDecl(const SourceLocation& location, const std::string& name,
          std::optional<TypeRef> type, std::optional<Expr*> value,
          const AttributedNode& attributes = AttributedNode())
    : Stmt(location), AttributedNode(attributes), name(name), decl_type(type), value(value) {}
  VarDecl(const SourceLocation& location, const std::string& name,
          std::optional<TypeRef> type, std::optional<Expr*> value, FnDecl* arg_for,
          const AttributedNode& attributes = AttributedNode())
    : Stmt(location), AttributedNode(attributes), name(name), 
      decl_type(type), value(value), arg_for(arg_for) {}
  ~VarDecl() = default;

  auto& get_name() const { return name; }
  auto& get_decl_type() { return decl_type; }
  auto& get_value() { return value; }
  Node* clone() const override;
  void set_used() { used++; }
  auto get_used() const { return used; }

  void set_parent_type(types::Type* type) { parent_type = type; }
  auto get_parent_type() const { return parent_type; }

  auto get_member_index() const { return index; }
  void set_member_index(uint64_t idx) { index = idx; }

  auto get_arg_for() const { return arg_for; }
  void mutate_arg_for(FnDecl* new_arg_for) {
    assert(arg_for.has_value());
    arg_for = new_arg_for;
  }

  static auto
  create(const SourceLocation& location, const std::string& name,
         std::optional<TypeRef> type, std::optional<Expr*> value,
         const AttributedNode& attributes = AttributedNode()) {
    return new VarDecl(location, name, type, value, attributes);
  }

  static auto
  create(const SourceLocation& location, const std::string& name,
         std::optional<TypeRef> type, std::optional<Expr*> value, FnDecl* arg_for,
         const AttributedNode& attributes = AttributedNode()) {
    return new VarDecl(location, name, type, value, arg_for, attributes);
  }

  SN_VISIT()
};

class InterfaceDecl;

class ClassDecl : public Stmt,
                  public GenericNode<>,
                  public AttributedNode,
                  public Identified,
                  public ModuleHolder {
public:
  enum class ClassType
  {
    Class,
    Interface
  };
private:
  friend InterfaceDecl;
  std::string name;
  bool generic_instanced = false;
  std::vector<VarDecl*> vars;
  std::vector<FnDecl*> funcs;
  bool complete = false; // If the class is complete, i.e. all methods are defined
  ClassType class_type = ClassType::Class;
  std::vector<TypeRef> implemented_interfaces;

public:
// clang-format off
  ClassDecl(
          const SourceLocation& location, const std::string& name,
          const std::vector<VarDecl*>& vars, const std::vector<FnDecl*>& funcs,
          ClassType class_type = ClassType::Class,
          std::optional<GenericNode> generics = std::nullopt,
          const AttributedNode& attributes = AttributedNode())
    : Stmt(location), GenericNode(generics), AttributedNode(attributes), 
      name(name), vars(vars), funcs(funcs), class_type(class_type) {}
// clang-format on

  virtual ~ClassDecl() = default;

  auto& get_name() const { return name; }
  auto& get_vars() { return vars; }
  auto& get_funcs() { return funcs; }

  Node* clone() const override;

  bool is_generic_instanced() const;
  void set_generic_instanced();

  void set_complete() { complete = true; }
  auto is_complete() const { return complete; }
  
  auto& get_implemented_interfaces() { return implemented_interfaces; }
  void set_implemented_interfaces(const std::vector<TypeRef>& interfaces) {
    implemented_interfaces = interfaces;
  }
  
  auto get_class_type() const { return class_type; }
  bool is_interface() const { return class_type == ClassType::Interface; }
  bool is_class() const { return class_type == ClassType::Class; }

  bool has_vtable() const;

  static auto
  create(const SourceLocation& location, const std::string& name,
         const std::vector<VarDecl*>& vars, const std::vector<FnDecl*>& funcs,
         ClassType class_type = ClassType::Class,
         std::optional<GenericNode> generics = std::nullopt,
         const AttributedNode& attributes = AttributedNode()) {
    return new ClassDecl(location, name, vars, funcs, class_type, generics, attributes);
  }

  SN_VISIT()
};

} // namespace ast
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
