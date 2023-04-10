
#include "../visitor/Visitor.h"
#include "common.h"
#include "nodes.h"

namespace snowball {
namespace Syntax {

#define ACCEPT(Node)                                                           \
    void Node::accept(Syntax::Visitor* v) { v->visit(this); }
#include "../../defs/accepts.def"

} // namespace Syntax
} // namespace snowball
