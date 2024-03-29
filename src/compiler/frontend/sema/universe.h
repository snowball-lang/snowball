
#ifndef __SNOWBALL_FRONTEND_SEMA_UNIVERSE_H__
#define __SNOWBALL_FRONTEND_SEMA_UNIVERSE_H__

#include <map>
#include <unordered_map>

#include "compiler/utils/utils.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/location.h"

namespace snowball {
namespace frontend {
namespace sema {

template <class Item>
class Scope {
  std::unordered_map<std::string, Item> items;
public:
  Scope() = default;
  ~Scope() = default;

  void add_item(const std::string& name, const Item& item) { items.insert(std::make_pair(name, item)); }
  void remove_item(Item item) { items.erase(item.get_name()); }

  std::optional<Item> get_item(const std::string& name) {
    auto it = items.find(name);
    if (it != items.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  auto& get_items() { return items; }
};

template <class ScopeItem>
class Universe {
  std::vector<Scope<ScopeItem>> scopes;
  std::map<NamespacePath, ast::types::Type*> types;
  std::vector<ast::types::Type*> constraints;
  std::vector<std::pair<NamespacePath, ast::FnDecl*>> fn_decls;
  std::map<uint64_t, ast::Stmt*> var_ids;
public:
  Universe() { add_scope(); }
  ~Universe() = default;

  void add_scope() { scopes.push_back(Scope<ScopeItem>()); }
  void remove_scope() { scopes.pop_back(); }

  bool is_global() const { return scopes.size() == 1; }
  void add_item(const std::string& name, const ScopeItem& item) 
    { scopes.back().add_item(name, item); }

  std::optional<ScopeItem> get_item(const std::string& name) {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      auto item = it->get_item(name);
      if (item.has_value()) {
        return item;
      }
    }
    return std::nullopt;
  }

  void add_type(const NamespacePath& path, ast::types::Type* type) { types[path] = type; }

  std::optional<ast::types::Type*> get_type(const NamespacePath& path) {
    auto it = types.find(path);
    if (it != types.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  std::optional<ast::types::Type*> get_constraint(size_t index) {
    if (index < constraints.size()) {
      return constraints[index];
    }
    return std::nullopt;
  }

  void add_fn_decl(const NamespacePath& path, ast::FnDecl* fn_decl) {
    fn_decls.push_back({path, fn_decl});
  }

  auto get_fn_decl(const NamespacePath& path) {
    std::vector<ast::FnDecl*> result;
    for (auto& [p, fn_decl] : fn_decls) {
      if (p == path) {
        result.push_back(fn_decl);
      }
    }
    return result;
  }

  void add_var_id(uint64_t id, ast::Stmt* stmt) { var_ids[id] = stmt; }
  auto get_var_id(uint64_t id) {
    auto it = var_ids.find(id);
    if (it != var_ids.end()) {
      return std::optional(it->second);
    }
    return std::nullopt;
  }

  auto get_types() const { return types; }
  auto& get_constraints() { return constraints; }
  auto get_fn_decls() const { return fn_decls; }
  auto& get_scopes() { return scopes; }
  auto& current_scope() { return scopes.back(); }
};

}
}
}

#endif // __SNOWBALL_FRONTEND_SEMA_UNIVERSE_H__
