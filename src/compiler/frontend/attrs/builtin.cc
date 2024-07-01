
#include "compiler/frontend/attrs/attr.h"
#include "compiler/frontend/attrs/interp.h"

#include "compiler/frontend/attrs/builtin/cfg.h"
#include "compiler/frontend/attrs/builtin/not.h"
#include "compiler/frontend/attrs/builtin/test.h"
#include "compiler/frontend/attrs/builtin/link_name.h"
#include "compiler/frontend/attrs/builtin/no_mangle.h"
#include "compiler/frontend/attrs/builtin/snowball_builtin_item.h"

namespace snowball {
namespace frontend {
namespace ast::attrs {

void AttrInterpreter::register_builtin_instances() {
  register_instance("cfg", get_cfg());
  register_instance("not", get_not());
  register_instance("test", get_test());
  register_instance("link_name", get_link_name());
  register_instance("no_mangle", get_no_mangle());
  register_instance("snowball_builtin_item", get_snowball_builtin_item());
}

}
}
}