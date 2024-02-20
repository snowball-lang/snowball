
#include "compiler/frontend/ast/nodes.h"
#include "compiler/utils/utils.h"
#include "compiler/frontend/ast/visitors.h"

namespace snowball {
namespace frontend {
namespace ast {

void AttributedNode::assert_is_func() const {
  sn_assert(!is_abstract || !is_final || !is_const, "Other attributes are not allowed with 'func'");
}

void AttributedNode::assert_is_var() const {
  sn_assert(!is_abstract || !is_final || !is_override || !is_inline || !is_virtual, "Other attributes are not allowed with 'var'");
}

void AttributedNode::assert_is_type() const {
  sn_assert(!is_const || !is_mut || !is_static || !is_override || !is_virtual || !is_inline, "Other attributes are not allowed with 'type'");
  sn_assert(external == Extern::None, "External attribute is not allowed with 'type'");
}

#define SN_REGISTER_ACCEPT(n) void n::accept(ast::AstVisitor* v) { v->visit(this); }
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT

}
}
}
