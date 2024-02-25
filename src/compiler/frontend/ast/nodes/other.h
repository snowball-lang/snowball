
#ifndef __SNOWBALL_FRONTEND_AST_NODES_OTHER_H__
#define __SNOWBALL_FRONTEND_AST_NODES_OTHER_H__

#include <vector>
#include <optional>

namespace snowball {
namespace frontend {
namespace ast {

class TypeRef;

class GenericDecl {
  std::string name;
public:
  GenericDecl(const std::string& name) : name(name) {}
  ~GenericDecl() = default;

  auto get_name() const { return name; }
  static auto create(const std::string& name) {
    // note: This shoudn't be created with a `new` keyword
    return GenericDecl(name);
  }
};

template <typename T = GenericDecl>
class GenericNode {
  std::vector<T> generics; // we don't use pointers here to save memory
public:
  GenericNode(const std::vector<T>& generics) : generics(generics) {}
  GenericNode(std::optional<GenericNode<T>> generics) {
    if (generics.has_value()) {
      this->generics = generics->get_generics();
    }
  }
  ~GenericNode() = default;

  auto get_generics() const { return generics; }
  static auto create(const std::vector<T>& generics) {
    return GenericNode(generics);
  }
};

class AttributedNode {
public:
  enum Extern {
    C,
    Snowball,
    System,
    None,
  };
  enum Privacy {
    // It has to be in this order to avoid conflicts with set_privacy(int)
    Private = 0,
    Public = 1,
  };
private:
  bool is_static = false;
  bool is_const = false;
  bool is_mut = false;
  bool is_abstract = false; 
  bool is_override = false; 
  bool is_final = false;
  bool is_virtual = false; 
  bool is_inline = false;  
  Extern external = None;
  Privacy privacy = Private;
public:
  AttributedNode() = default;
  ~AttributedNode() = default;

  auto get_privacy() const { return privacy; }
  auto get_static() const { return is_static; }
  auto get_const() const { return is_const; }
  auto get_mut() const { return is_mut; }
  auto get_abstract() const { return is_abstract; }
  auto get_override() const { return is_override; }
  auto get_final() const { return is_final; }
  auto get_virtual() const { return is_virtual; }
  auto get_inline() const { return is_inline; }
  auto get_external() const { return external; }
  
  void set_privacy(Privacy privacy) { this->privacy = privacy; }
  void set_static(bool is_static) { this->is_static = is_static; }
  void set_const(bool is_const) { this->is_const = is_const; }
  void set_mut(bool is_mut) { this->is_mut = is_mut; }
  void set_abstract(bool is_abstract) { this->is_abstract = is_abstract; }
  void set_override(bool is_override) { this->is_override = is_override; }
  void set_final(bool is_final) { this->is_final = is_final; }
  void set_virtual(bool is_virtual) { this->is_virtual = is_virtual; }
  void set_inline(bool is_inline) { this->is_inline = is_inline; }
  void set_external(Extern external) { this->external = external; }

  void set_privacy(int privacy) { this->privacy = static_cast<Privacy>(privacy); }

  void assert_is_func() const;
  void assert_is_var() const;
  void assert_is_type() const;
};

}
}
}

#endif // __SNOWBALL_FRONTEND_AST_NODES_OTHER_H__
