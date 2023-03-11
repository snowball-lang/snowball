
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

namespace snowball::parser {

ptr<Syntax::Expression::Base>
Parser::buildOperatorTree(std::vector<ptr<Syntax::Expression::Base>>& exprs) {
    assert(exprs.size() > 0);

    while (exprs.size() > 1) {
        assert(false && "TODO: binary op tree");
    }

    return exprs[0];
}

} // namespace snowball::parser

#undef IF_TOKEN
