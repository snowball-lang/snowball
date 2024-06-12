
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

#define link_name "link_name"

class LinkageName final : public AttrInstance {
public:
  LinkageName(const std::string& name) : AttrInstance(name) {}
  virtual ~LinkageName() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter,
                        const ParentArgs& args) override;
};

bool LinkageName::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter,
                          const ParentArgs& args) {
  if (assert_attr_has_value(reporter, interpreter, attr, link_name, attr.get_location())) 
    return false;
  auto func = target_get_function(reporter, interpreter, target, link_name, attr.get_location());
  if (!func) return false;
  if (attr.get_value().empty()) {
    interpreter.error(reporter, F("Attribute '{}' requires a non-empty value", link_name), Error::Info {
      .highlight = "Empty value provided",
      .note = F("This attribute requires a non-empty value to be set.\n"
              "For example, try doing the following: '#[{} = \"value\"]'", link_name)
    }, attr.get_location());
    return false;
  } else if (attr.get_value() == "main") {
    interpreter.error(reporter, F("Attribute '{}' cannot be set to 'main'", link_name), Error::Info {
      .highlight = "Invalid value provided",
      .note = F("This attribute cannot be set to 'main'.\n"
              "For example, try doing the following: '#[{} = \"value\"]'", link_name)
    }, attr.get_location());
    return false;
  }
  func->set_link_name(attr.get_value());
  return true;
}

static auto get_link_name() {
  return new LinkageName(link_name);
}

#undef link_name

}
}
}
