
#include "Visitor.h"

#include "../syntax/nodes.h"

namespace snowball {
namespace Syntax {

void Visitor::visitGlobal(std::vector<Node*> p_list) {
  for (auto node : p_list) 
    node->accept(this);
}

} // namespace Syntax
} // namespace snowball
