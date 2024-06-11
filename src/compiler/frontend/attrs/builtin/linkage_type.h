
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "compiler/utils/utils.h"
#include "compiler/frontend/attrs/interp.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

class LinkageType final : public AttrInstance {
public:
  LinkageType(const std::string& name) : AttrInstance(name) {}
  virtual ~LinkageType() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter) override;
};

bool LinkageType::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter) {
  sn_assert(false, "TODO: implement LinkageType::interpret");
}

static auto get_linkage_type() {
  return new LinkageType("linkage_type");
}

}
}
}
