
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

inline void assert_target_is_node(Reporter& reporter, AttrInterpreter& interp, 
    AttrInterpreter::Target target, const std::string& name, const SourceLocation& loc) {
  if (!target.has_value()) {
    interp.error(reporter, F("Attribute '{}' requires a target node"), Error::Info {
      .highlight = "Not attached to any node"
    }, loc);
  }
}

inline void assert_attr_has_value(Reporter& reporter, AttrInterpreter& interp, 
    const Attr& attr, const std::string& name, const SourceLocation& loc) {
  if (!attr.is_key_value()) {
    interp.error(reporter, F("Attribute '{}' requires a value"), Error::Info {
      .highlight = "No value provided",
      .note = F("This attribute requires a value to be set.\n"
              "For example, try doing the following: #[{} = \"value\"]", name)
    }, loc);
  }
}

inline void assert_attr_is_single(Reporter& reporter, AttrInterpreter& interp, 
    const Attr& attr, const std::string& name, const SourceLocation& loc) {
  if (!attr.is_single()) {
    interp.error(reporter, F("Attribute '{}' does not require a value"), Error::Info {
      .highlight = "Value provided",
      .note = F("This attribute does not require a value to be set.\n"
              "For example, try doing the following: #[{}]", name)
    }, loc);
  }
}

inline void assert_attr_is_nested(Reporter& reporter, AttrInterpreter& interp, 
    const Attr& attr, const std::string& name, const SourceLocation& loc) {
  if (!attr.is_nested()) {
    interp.error(reporter, F("Attribute '{}' requires a nested value"), Error::Info {
      .highlight = "No nested value provided",
      .note = F("This attribute requires a nested value to be set.\n"
              "For example, try doing the following: #[{}( key = \"value\" )]", name)
    }, loc);
  }
}

[[nodiscard]] inline auto target_get_function(Reporter& reporter, AttrInterpreter& interp, 
    AttrInterpreter::Target target, const std::string& name, const SourceLocation& loc) {
  assert_target_is_node(reporter, interp, target, name, loc);
  if (auto as_func = target.value()->as<ast::FnDecl>()) {
    return as_func;
  }
  interp.error(reporter, F("Attribute '{}' requires a function node"), Error::Info {
    .highlight = "Not attached to a function node"
  }, loc);
  return (ast::FnDecl*)nullptr;
}

}
}
}

#endif // __SNOWBALL_FRONTEND_ATTRS_COMMON_H__
