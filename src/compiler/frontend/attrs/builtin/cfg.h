
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

#define cfg "cfg"

class Config final : public AttrInstance {
public:
  Config(const std::string& name) : AttrInstance(name) {}
  virtual ~Config() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter,
                        const ParentArgs& args = {}) override;

  static bool get_config(const std::string& key, std::optional<std::string> value,
    Reporter& reporter, AttrInterpreter& interpreter, const Attr& attr);
};

bool Config::interpret(const Attr& attr, AttrInterpreter::Target target,
                          Reporter& reporter, AttrInterpreter& interpreter,
                          const ParentArgs& args) {
  // No need to return here, as we want to interpret the nested attributes.
  assert_target_is_node(reporter, interpreter, target, cfg, attr.get_location()); 
  if (assert_attr_is_nested(reporter, interpreter, attr, cfg, attr.get_location()))
    return false;
  auto attr_list = attr.get_attrs();
  bool success = true;
  ParentArgs new_args = {
    .callback = get_config
  };
  for (auto& inner_attr : attr_list) {
    if (inner_attr.is_nested()) {
      success &= interpreter.interpret(reporter, inner_attr, target, new_args);
    } else if (inner_attr.is_key_value()) {
      success &= get_config(inner_attr.get_key(), inner_attr.get_value(), 
        reporter, interpreter, inner_attr);
    } else {
      success &= get_config(inner_attr.get_key(), std::nullopt, 
        reporter, interpreter, inner_attr);
    }
  }
  return success;
}

bool Config::get_config(const std::string& key, std::optional<std::string> value,
  Reporter& reporter, AttrInterpreter& interpreter, const Attr& attr) {
  auto assert_no_value = [&]() {
    if (value.has_value()) {
      interpreter.error(reporter, F("Configuration key '{}' does not require a value", key), Error::Info {
        .highlight = "Value provided",
        .note = F("This configuration key does not require a value to be set.\n"
                "For example, try doing the following: '#[{}]", key)
      }, attr.get_location());
      return true;
    }
    return false;
  };
  if (key == "debug") {
    if (assert_no_value()) return false;
    return global.opt_level == OptLevel::Debug;
  } else if (key == "release") {
    if (assert_no_value()) return false;
    return global.opt_level == OptLevel::Release;
  } else if (key == "release_with_debug") {
    if (assert_no_value()) return false;
    return global.opt_level == OptLevel::ReleaseWithDebug;
  } else if (key == "release_fast") {
    if (assert_no_value()) return false;
    return global.opt_level == OptLevel::ReleaseFast;
  } else if (key == "test") {
    if (assert_no_value()) return false;
    return global.test_mode;
  }
  interpreter.error(reporter, F("Unknown configuration key '{}'", key), Error::Info {
    .highlight = "Unknown key",
    .note = F("This configuration key is not recognized by the compiler.\n"
            "Please check the documentation for a list of valid configuration keys.")
  }, attr.get_location());
  return false;
}

static auto get_cfg() {
  return new Config(cfg);
}

#undef cfg

}
}
}
