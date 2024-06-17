
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

#define no_mangle "no_mangle"

class NoMangle final : public AttrInstance {
public:
  NoMangle(const std::string& name) : AttrInstance(name) {}
  virtual ~NoMangle() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter,
                        const ParentArgs& args = {}) override;
};

bool NoMangle::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter,
                          const ParentArgs& args) {
  if (assert_attr_is_single(reporter, interpreter, attr, no_mangle, attr.get_location())) 
    return false;
  auto func = target_get_function(reporter, interpreter, target, no_mangle, attr.get_location());
  if (!func) return false;
  func->set_link_name(func->get_name());
  return true;  
}

static auto get_no_mangle() {
  return new NoMangle(no_mangle);
}

#undef no_mangle

}
}
}
