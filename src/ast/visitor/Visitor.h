
#include "../../SourcedObject.h"
#include "../syntax/nodes.h"

#include <assert.h>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_VISITOR_H_
#define __SNOWBALL_AST_VISITOR_H_

#define ACCEPT(Node)                                                                               \
    virtual void visit(Node* p_node) { assert(false && "BUG: Visitor::visit called"); }

namespace snowball {
namespace Syntax {

class Visitor : public SrcObject {
  public:
    Visitor(SourceInfo* srci) : SrcObject(srci){};
    virtual void visitGlobal(std::vector<Node*>);

#include "../../defs/accepts.def"
};

} // namespace Syntax
} // namespace snowball

#undef ACCEPT
#endif // __SNOWBALL_AST_VISITOR_H_
