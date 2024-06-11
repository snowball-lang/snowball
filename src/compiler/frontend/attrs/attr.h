
#ifndef __SNOWBALL_FRONTEND_SEMA_ATTRS_ATTR_H__
#define __SNOWBALL_FRONTEND_SEMA_ATTRS_ATTR_H__

#include <string>
#include <vector>
#include <optional>

#include "compiler/ctx.h"
#include "compiler/utils/utils.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

// Attributes can be either a single string or a key-value pair.
//
// Examples:
//   #[attr]
//   #[attr = "value"]
//   #[attr(key = "value")]
//   #[attr(key)]
//
// They can also contain other attributes inside them.
//
// Examples:
//   #[attr(attr2(attr3))]
enum class AttrType
{
  Single,
  KeyValue,
  Nested,
};

class Attr final : public Self<Attr>, public LocationHolder {
  std::string key;
  std::optional<std::string> value; // Optional because it can be a key-value pair or just a key.
  std::vector<Attr> attrs; // Attributes inside this attribute.
  AttrType type;
  bool is_global = false;

public:
  Attr(const std::string& key, std::string value, const SourceLocation& location)
    : LocationHolder(location), key(key), value(value), type(AttrType::KeyValue) {}

  Attr(const std::string& key, const SourceLocation& location)
    : LocationHolder(location), key(key), type(AttrType::Single) {}

  Attr(const std::string& key, const std::vector<Attr>& attrs, const SourceLocation& location)
    : LocationHolder(location), key(key), attrs(attrs), type(AttrType::Nested) {}

  ~Attr() = default;

  std::string get_key() const { return key; }
  std::string get_value() const;
  std::vector<Attr*> get_attrs() const;

  bool is_single() const { return type == AttrType::Single; }
  bool is_key_value() const { return type == AttrType::KeyValue; }
  bool is_nested() const { return type == AttrType::Nested; }

  void set_global() { is_global = true; }
  bool is_global_attr() const { return is_global; }
};

} // namespace ast::attrs
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_SEMA_ATTRS_ATTR_H__
