
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

#define not_attr "not"

class NotAttr final : public AttrInstance {
public:
  NotAttr(const std::string& name) : AttrInstance(name) {}
  virtual ~NotAttr() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter,
                        const ParentArgs& args = {}) override;
};

bool NotAttr::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter,
                          const ParentArgs& args) {
  if (assert_attr_is_nested(reporter, interpreter, attr, not_attr, attr.get_location()))
    return false;
  auto callback = get_callback(reporter, interpreter, args, not_attr, attr.get_location());
  if (!callback) return false;
  bool success = true;
  for (auto& inner_attr : attr.get_attrs()) {
    if (inner_attr.is_nested()) {
      success &= interpreter.interpret(reporter, inner_attr, target, args);
    } else if (inner_attr.is_key_value()) {
      success &= callback(inner_attr.get_key(), inner_attr.get_value(), 
        reporter, interpreter, inner_attr);
    } else {
      success &= callback(inner_attr.get_key(), std::nullopt, 
        reporter, interpreter, inner_attr);
    }
  }
  return !success; // Negate the result.
}

static auto get_not() {
  return new NotAttr(not_attr);
}

#undef not_attr

}
}
}
