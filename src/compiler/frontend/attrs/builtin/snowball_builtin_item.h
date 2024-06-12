
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "compiler/utils/utils.h"
#include "compiler/frontend/attrs/interp.h"
#include "compiler/frontend/attrs/builtin/common.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

#define snowball_builtin_item "snowball_builtin_item"
#define ALLOWED_VALUES_MAP { \
  { "sized", false }, \
  { "copy", false } \
}

class SnowballBuiltinItem final : public AttrInstance {
public:
  SnowballBuiltinItem(const std::string& name) : AttrInstance(name) {}
  virtual ~SnowballBuiltinItem() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter,
                        const ParentArgs& args = {}) override;
};

bool SnowballBuiltinItem::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter,
                          const ParentArgs& args) {
  static std::unordered_map<std::string, bool> allowed_values_map = ALLOWED_VALUES_MAP;
  if (assert_attr_has_value(reporter, interpreter, attr, snowball_builtin_item, attr.get_location()))
    return false;
  auto cls = target_get_class(reporter, interpreter, target, snowball_builtin_item, attr.get_location());
  if (!cls) return false;
  auto value = attr.get_value();
  auto it = allowed_values_map.find(value);
  if (it == allowed_values_map.end()) {
    interpreter.error(reporter, F("Attribute '{}' has an invalid value", snowball_builtin_item), Error::Info {
      .highlight = "Invalid value provided",
      .note = F("This attribute requires a valid value to be set.\n"
              "For example, try doing the following: '#[{} = \"value\"]'", snowball_builtin_item)
    }, attr.get_location());
    return false;
  } else if (it->second) {
    interpreter.error(reporter, F("Attribute '{}' already set", snowball_builtin_item), Error::Info {
      .highlight = "Value already set",
      .help = "This attribute is used for internal purposes only, if you are seeing this error\n"
              "please report it to the developers or check your life choices.",
      .note = F("This attribute has already been set.\n"
              "For example, try doing the following: '#[{} = \"value\"]'", snowball_builtin_item)
    }, attr.get_location());
    return false;
  }
  cls->set_builtin_name(value);
  it->second = true;
  return true;
}

static auto get_snowball_builtin_item() {
  return new SnowballBuiltinItem(snowball_builtin_item);
}

#undef snowball_builtin_item

}
}
}
