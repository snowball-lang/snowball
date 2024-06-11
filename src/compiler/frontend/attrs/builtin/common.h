
#ifndef __SNOWBALL_FRONTEND_ATTRS_COMMON_H__
#define __SNOWBALL_FRONTEND_ATTRS_COMMON_H__

#include <string>
#include <vector>

#include "compiler/utils/utils.h"
#include "compiler/frontend/location.h"
#include "compiler/frontend/attrs/attr.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/attrs/interp.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

// Utility functions for attributes' logic.

inline bool assert_target_is_node(Reporter& reporter, AttrInterpreter& interp, 
    AttrInterpreter::Target target, const std::string& name, const SourceLocation& loc) {
  if (!target.has_value()) {
    interp.error(reporter, F("Attribute '{}' requires a target node", name), Error::Info {
      .highlight = "Not attached to any node"
    }, loc);
    return true;
  }
  return false;
}

inline bool assert_attr_has_value(Reporter& reporter, AttrInterpreter& interp, 
    const Attr& attr, const std::string& name, const SourceLocation& loc) {
  if (!attr.is_key_value()) {
    interp.error(reporter, F("Attribute '{}' requires a value", name), Error::Info {
      .highlight = "No value provided",
      .note = F("This attribute requires a value to be set.\n"
              "For example, try doing the following: '#[{} = \"value\"]'", name)
    }, loc);
    return true;
  }
  return false;
}

inline bool assert_attr_is_single(Reporter& reporter, AttrInterpreter& interp, 
    const Attr& attr, const std::string& name, const SourceLocation& loc) {
  if (!attr.is_single()) {
    interp.error(reporter, F("Attribute '{}' does not require a value", name), Error::Info {
      .highlight = "Value provided",
      .note = F("This attribute does not require a value to be set.\n"
              "For example, try doing the following: '#[{}]'", name)
    }, loc);
    return true;
  }
  return false;
}

inline bool assert_attr_is_nested(Reporter& reporter, AttrInterpreter& interp, 
    const Attr& attr, const std::string& name, const SourceLocation& loc) {
  if (!attr.is_nested()) {
    interp.error(reporter, F("Attribute '{}' requires a nested value", name), Error::Info {
      .highlight = "No nested value provided",
      .note = F("This attribute requires a nested value to be set.\n"
              "For example, try doing the following: '#[{}( key = \"value\" )]'", name)
    }, loc);
    return true;
  }
  return false;
}

[[nodiscard]] inline auto target_get_function(Reporter& reporter, AttrInterpreter& interp, 
    AttrInterpreter::Target target, const std::string& name, const SourceLocation& loc) {
  if (assert_target_is_node(reporter, interp, target, name, loc)) {
    return (ast::FnDecl*)nullptr;
  }
  if (auto as_func = target.value()->as<ast::FnDecl>()) {
    return as_func;
  }
  interp.error(reporter, F("Attribute '{}' requires a function node", name), Error::Info {
    .highlight = "Not attached to a function node"
  }, loc);
  return (ast::FnDecl*)nullptr;
}

[[nodiscard]] inline auto get_callback(Reporter& reporter, AttrInterpreter& interp, 
    const ParentArgs& args, const std::string& name, const SourceLocation& loc) {
  if (!args.callback.has_value()) {
    interp.error(reporter, F("Attribute '{}' cant be called at a top-level state", name), Error::Info {
      .highlight = "No parent function provided"
    }, loc);
    return (std::function<bool(const std::string&, std::optional<std::string>, 
      Reporter&, AttrInterpreter&, const Attr&)>)nullptr;
  }
  return args.callback.value();
}

}
}
}

#endif // __SNOWBALL_FRONTEND_ATTRS_COMMON_H__
