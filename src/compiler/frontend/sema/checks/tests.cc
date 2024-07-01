
#include <cassert>

#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/check.h"

namespace snowball {
namespace frontend {
namespace sema {

void TypeChecker::check_test_case(const ast::FnDecl* fn_decl) {
  if (!fn_decl->get_test()) return;
  auto ret_type = fn_decl->get_type()->as_func()->get_return_type();
  if (!ret_type->is_int() || !(ret_type->as_int()->get_bits() == 1)) {
    err(fn_decl->get_location(), "Test functions must return a bool", Error::Info {
      .highlight = "Return type is not 'bool'",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/testing"
    });
  }
  if (fn_decl->get_params_count() != 0) {
    err(fn_decl->get_location(), "Test functions must not have any parameters", Error::Info {
      .highlight = "Test functions must not have any parameters",
      .help = "Test functions must not have any parameters",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/testing"
    });
  }
  if (fn_decl->get_link_name() == "main") {
    err(fn_decl->get_location(), "Test functions cannot have the link name 'main'", Error::Info {
      .highlight = "Test functions cannot have the link name 'main'",
      .help = "Test functions cannot have the link name 'main'",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/testing"
    });
  }
  if (fn_decl->get_generics().size() != 0) {
    err(fn_decl->get_location(), "Test functions cannot be generic", Error::Info {
      .highlight = "Test functions cannot be generic",
      .help = "Test functions cannot be generic",
      .see = "https://snowball-lang.gitbook.io/docs/language-reference/testing"
    });
  }
}

}
}
}
