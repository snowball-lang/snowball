
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
                        Reporter& reporter, AttrInterpreter& interpreter) override;
};

bool LinkageName::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter) {
  assert_attr_has_value(reporter, interpreter, attr, link_name, attr.get_location());
  auto func = target_get_function(reporter, interpreter, target, link_name, attr.get_location());
  if (!func) return false;
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
