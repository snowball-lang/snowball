
#include "compiler/frontend/attrs/attr.h"
#include "compiler/frontend/attrs/interp.h"

#include "compiler/frontend/attrs/builtin/cfg.h"
#include "compiler/frontend/attrs/builtin/not.h"
#include "compiler/frontend/attrs/builtin/link_name.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

void AttrInterpreter::register_builtin_instances() {
  register_instance("cfg", get_cfg());
  register_instance("not", get_not());
  register_instance("link_name", get_link_name());
}

}
}
}