
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::visit(ast::Number* node) {
  auto val = node->get_value();
  bool _unsigned = false;
  int bytes = 32;
  assert(val.length() > 0);
  if (val.length() > 1) {
    for (size_t i = 0; i < val.size(); i++) {
      switch (val[val.length() - 1]) {
        case 'L': bytes = bytes * 2; break;
        case 'U': _unsigned = false; break;
        case 'I': {
          if (_unsigned) {
            err(node->get_location(), "Cant explicitly declare an integer as signed and unsigned at the same time!", Error::Info {
              .highlight = "Used 'I' and 'U' explicitly at the same time",
              .help = "Remove the 'I' to make the integer unsigned. By default, number constants are signed!"
            }, Error::Type::Err, false);
          }
          break;
        }
      }
    }
  }
  auto type = (_unsigned ? std::string("u") : "i") + std::to_string(bytes);
  unify(node->get_type(), get_type(type), node->get_location());
}

void TypeChecker::visit(ast::String* node) {
  switch (node->get_prefix()) {
    case 'b':
    case 'B':
      unify(node->get_type(), get_type("u8")->get_pointer_to(false), node->get_location());
      break;
    case 0:
      sn_assert(false, "Normal strings are not supported yet!");
    default: err(node->get_location(), "Invalid string prefix!", Error::Info {
      .highlight = "Invalid string prefix",
      .help = "Valid string prefixes are 'b' and 'B' for byte strings."
    }, Error::Type::Err, false);
  }
}

}
}
}
