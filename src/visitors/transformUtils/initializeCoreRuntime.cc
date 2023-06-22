#include "../../ast/syntax/nodes.h"
#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void
Transformer::initializeCoreRuntime() {
    auto import =
            Syntax::N<Syntax::Statement::ImportStmt>(std::vector<std::string>{"_$core"}, "Core");
    import->setDBGInfo(new DBGSourceInfo(ctx->module->getSourceInfo(), 0));

    import->accept(this);
}

} // namespace Syntax
} // namespace snowball