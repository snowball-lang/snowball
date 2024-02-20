
#ifndef __SNOWBALL_FRONTEND_SEMA_UNIVERSE_H__
#define __SNOWBALL_FRONTEND_SEMA_UNIVERSE_H__

#include <map>
#include <unordered_map>

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

  void add_item(const std::string& name, Item item) { items.insert({name, item}); }
  void remove_item(Item item) { items.erase(item.get_name()); }

  std::optional<Item> get_item(const std::string& name) {
    auto it = items.find(name);
    if (it != items.end()) {
      return it->second;
    }
    return std::nullopt;
  }
};

template <class ScopeItem>
class Universe {
  std::vector<Scope<ScopeItem>> scopes;
  std::map<NamespacePath, ast::types::Type*> types;
public:
  Universe() = default;
  ~Universe() = default;

  void add_scope() { scopes.push_back(Scope<ScopeItem>()); }
  void remove_scope() { scopes.pop_back(); }

  bool is_global() const { return scopes.size() == 1; }
  void add_item(const std::string& name, ScopeItem item) 
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
};

}
}
}

#endif // __SNOWBALL_FRONTEND_SEMA_UNIVERSE_H__
