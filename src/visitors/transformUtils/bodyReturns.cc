#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

bool Transformer::bodyReturns(std::vector<ptr<Node>> exprs) {
    for (auto expr : exprs) {
        if (cast<Statement::Return>(expr)) {
            return true;
        } else if (auto b = cast<Block>(expr)) {
            if (bodyReturns(b->getStmts())) return true;
        } else if (auto b = cast<Statement::Conditional>(expr)) {
            assert(false);
        }
        // TODO: Break, continue: return false
        // TODO: Loop, while: if (bodyReturns(b->getStmts())) return true;
        // TODO: If: if bodyReturns(if_body) && bodyReturns(else_body) { return true }

        // Ignore unhandled!
    }

    return false;
}


} // namespace Syntax
} // namespace snowball