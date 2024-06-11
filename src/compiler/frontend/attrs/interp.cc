
#include "compiler/frontend/attrs/attr.h"
#include "compiler/frontend/attrs/interp.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

bool AttrInterpreter::interpret(Reporter& reporter, const Attr& attrs, Target target) {
  if (call_stack.size() >= SNOWBALL_ATTRS_CALL_STACK_SIZE) {
    error(reporter, "Attribute call stack overflow", Error::Info {
      .highlight = "Stack overflow from this attribute",
      .help = "Try to reduce the number of nested attributes or check for circular dependencies"
    }, attrs.get_location());
    return false;
  }
  auto name = attrs.get_key();
  auto it = instances.find(name);
  if (it == instances.end()) {
    error(reporter, F("Unknown attribute '{}'", name), Error::Info {
      .highlight = F("Attribute '{}' not found", name),
      .help = "Check if the attribute is registered or if there is a typo"
    }, attrs.get_location());
    return false;
  }
  call_stack.push_back(it->second);
  auto result = it->second->interpret(attrs, target, reporter, *this);
  call_stack.pop_back();
  return result;
}

bool AttrInterpreter::interpret(Reporter& reporter, const std::vector<Attr>& attrs, Target target) {
  bool result = true;
  for (auto& attr : attrs) {
    // We want to evaluate all attributes even if one fails.
    result &= interpret(reporter, attr, target);
  }
  return result;
}

void AttrInterpreter::error(Reporter& reporter, const std::string& message, Error::Info info, const SourceLocation& loc) {
  reporter.add_error(Error(message, loc, info));
}

void AttrInterpreter::register_instance(const std::string& name, AttrInstance* instance) {
  assert(instances.find(name) == instances.end());
  instances[name] = instance;
}

void AttrInterpreter::unregister_instance(const std::string& name) {
  instances.erase(name);
}

}
}
}