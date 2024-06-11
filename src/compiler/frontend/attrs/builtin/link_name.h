
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "compiler/utils/utils.h"
#include "compiler/frontend/attrs/interp.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

class LinkageName final : public AttrInstance {
public:
  LinkageName(const std::string& name) : AttrInstance(name) {}
  virtual ~LinkageName() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter) override;
};

bool LinkageName::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter) {
  sn_assert(false, "TODO: implement LinkageName::interpret");
}

static auto get_link_name() {
  return new LinkageName("link_name");
}

}
}
}
