
#include "../DefiniteAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Block) {
    asBlock([&] {
        for (auto i : p_node->getStmts()) {
            i->accept(this);
        }
    });
}

} // namespace Syntax
} // namespace snowball
