
#include "compiler/frontend/attrs/attr.h"
#include "compiler/frontend/attrs/interp.h"

#include "compiler/frontend/attrs/builtin/link_name.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

void AttrInterpreter::register_builtin_instances() {
  register_instance("link_name", get_link_name());
}

}
}
}