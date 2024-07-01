
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "compiler/utils/utils.h"
#include "compiler/frontend/attrs/interp.h"
#include "compiler/frontend/attrs/builtin/common.h"

#include "compiler/globals.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

#define test "test"

class TestCase final : public AttrInstance {
public:
  TestCase(const std::string& name) : AttrInstance(name) {}
  virtual ~TestCase() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter,
                        const ParentArgs& args = {}) override;
};

bool TestCase::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter,
                          const ParentArgs& args) {
  if (assert_attr_is_single(reporter, interpreter, attr, test, attr.get_location())) 
    return false;
  auto func = target_get_function(reporter, interpreter, target, test, attr.get_location());
  if (!func) return false;
  func->set_test(true);
  return global.test_mode;
}

static auto get_test() {
  return new TestCase(test);
}

#undef test

}
}
}
