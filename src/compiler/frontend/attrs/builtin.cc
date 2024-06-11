
#include "compiler/frontend/attrs/attr.h"
#include "compiler/frontend/attrs/interp.h"

#include "compiler/frontend/attrs/builtin/linkage_type.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

void AttrInterpreter::register_builtin_instances() {
  register_instance("linkage_type", get_linkage_type());
}

}
}
}