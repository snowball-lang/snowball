
#ifndef __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
#define __SNOWBALL_FRONTEND_AST_NODES_STMT_H__

#include <optional>
#include <string>
#include <vector>

#include "compiler/utils/id.h"
#include "compiler/utils/clone.h"
#include "compiler/frontend/ast/nodes/expr.h"
#include "compiler/frontend/ast/nodes/other.h"

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
class ConstructorDecl;

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

class FnDecl : public Stmt, public GenericNode<>, 
  public AttributedNode, public Identified, public ModuleHolder {
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
  // If this function is a virtual function that overrides its parent
  // parent class, this will be set to the overriden function.
  // note that this does not necessarily equal to parent_type, as the
  // parent type can be a trait.
  // e.g.: (B has foo)
  // class A implements B {
  //   virtual func foo() {} // foo has B as virtual_overriden
  //                         // and A as parent_type
  // }
  std::optional<types::Type*> virtual_overriden = std::nullopt;
  std::optional<std::pair<size_t, size_t>> vtable_index = std::nullopt; // Relative virtual_overriden index

  friend class ConstructorDecl;

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

  auto get_virtual_overriden() const { return virtual_overriden; }
  void set_virtual_overriden(types::Type* type) { virtual_overriden = type; }

  auto get_vtable_index() const { return vtable_index; }
  void set_vtable_index(std::pair<size_t, size_t> idx) { vtable_index = idx; }

  uint64_t get_generic_id() const;
  static auto
  create(const SourceLocation& location, const std::string& name,
         const std::vector<VarDecl*>& params, TypeRef return_type,
         std::optional<Block*> body, std::optional<GenericNode> generics = std::nullopt,
         const AttributedNode& attributes = AttributedNode()) {
    return new FnDecl(location, name, params, return_type, body, generics, attributes);
  }

  virtual bool is_constructor() const { return false; }
  virtual ConstructorDecl* get_constructor() { return nullptr; }

  SN_VISIT()
};

class ConstructorDecl final : public FnDecl {
public:
  template <typename... Args>
  ConstructorDecl(Args&&... args)
    : FnDecl(std::forward<Args>(args)...) {}
  ~ConstructorDecl() = default;

  bool is_constructor() const override { return true; }
  ConstructorDecl* get_constructor() override { return this; }

  Node* clone() const override;

  template <typename... Args>
  static auto create(Args&&... args) {
    return new ConstructorDecl(std::forward<Args>(args)...);
  }
};

class VarDecl final : public Stmt, public AttributedNode, public Identified, 
    public ModuleHolder {
  std::string name;
  std::optional<TypeRef> decl_type;
  std::optional<Expr*> value;
  std::optional<FnDecl*> arg_for = std::nullopt;
  std::optional<types::Type*> parent_type = std::nullopt; // Direct parent type
  std::optional<uint64_t> index; // Member access index
  bool used = 0;

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
  void set_used() { used = true; }
  auto is_used() const { return used; }

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

class ExtensionDecl;

class ClassDecl : public Stmt, public GenericNode<>, 
  public AttributedNode, public Identified, public ModuleHolder {
public:
  enum class ClassType
  {
    Class,
    Interface,
    Extension
  };
private:
  friend ExtensionDecl;

  std::string name;
  bool generic_instanced = false;
  std::vector<VarDecl*> vars;
  std::vector<FnDecl*> funcs;
  bool complete = false; // If the class is complete, i.e. all methods are defined
  ClassType class_type = ClassType::Class;
  std::vector<TypeRef> implemented_interfaces;

  // Interface specific
  std::string builtin_name; // Identifier for builtin types (e.g. Sized has "sized")

public:
  ClassDecl(
      const SourceLocation& location, const std::string& name,
      const std::vector<VarDecl*>& vars, const std::vector<FnDecl*>& funcs,
      ClassType class_type = ClassType::Class,
      std::optional<GenericNode> generics = std::nullopt,
      const AttributedNode& attributes = AttributedNode())
    : Stmt(location), GenericNode(generics), AttributedNode(attributes), 
      name(name), vars(vars), funcs(funcs), class_type(class_type) {}

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

  // Iterate over virtual functions by using iterators
  std::vector<uint64_t>& get_virtual_fn_ids() const;
  size_t get_virtual_fn_count() const;

  auto get_builtin_name() const { return builtin_name; }
  void set_builtin_name(const std::string& name) { builtin_name = name; }

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

class ExtensionDecl final : public ClassDecl {
  TypeRef extended_type;

public:
  ExtensionDecl(
      const SourceLocation& location, const TypeRef& extended_type,
      const std::vector<FnDecl*>& funcs
  ) : ClassDecl(location, "", {}, funcs, ClassType::Extension), extended_type(extended_type) {}
  ~ExtensionDecl() = default;

  auto& get_extended_type() { return extended_type; }
  Node* clone() const override;

  static auto
  create(const SourceLocation& location, const TypeRef& extended_type,
         const std::vector<FnDecl*>& funcs) {
    return new ExtensionDecl(location, extended_type, funcs);
  }
};

class Return final : public Stmt {
  std::optional<Expr*> value;
  bool implicit = false;

public:
  Return(const SourceLocation& location, std::optional<Expr*> value, bool implicit)
    : Stmt(location), value(value), implicit(implicit) {}
  ~Return() = default;

  auto& get_value() { return value; }
  Node* clone() const override;
  static auto create(const SourceLocation& location, std::optional<Expr*> value,
                     bool implicit = false) {
    return new Return(location, value, implicit);
  }

  SN_VISIT()
};

class Use final : public Stmt, public AttributedNode, public Self<Use>, public Identified {
public:
  struct Item {
    NamespacePath path;
    std::optional<std::string> alias;
  };

  struct Section {
    std::vector<Item> items;
  };
private:
  // e.g. you can have "hello::(my, mod)::world" and "hello::my::world", etc.
  std::vector<Section> sections;

public:
  Use(const SourceLocation& location, const std::vector<Section>& sections,
      const AttributedNode& attributes = AttributedNode())
    : Stmt(location), AttributedNode(attributes), sections(sections) {}
  ~Use() = default;

  auto& get_sections() { return sections; }
  static auto create(const SourceLocation& location, const std::vector<Section>& sections,
                     const AttributedNode& attributes = AttributedNode()) {
    return new Use(location, sections, attributes);
  }

  SN_VISIT()
  SN_DEFAULT_CLONE() // There is no need to clone this, as it doesn't need modification
};

} // namespace ast
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_AST_NODES_STMT_H__
