
#include "../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Block) {
    std::vector<std::string> blockInited;
    asBlock([&] {
        for (auto i : p_node->getStmts()) {
            i->accept(this);
        }

        blockInited = this->state.inited;
    });

    for (auto id : blockInited) {
        if (auto x = getIdentifier(id)) {
            if (x->second == NotInitialized) {
                this->state.inited.push_back(id);
                this->scopes.front()[id] = Initialized;
            }
        }
    }
}

} // namespace Syntax
} // namespace snowball
