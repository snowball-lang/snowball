#include "../../../ast/syntax/nodes.h"
#include "../../Transformer.h"

#include "../../../lexer/lexer.h"
#include "../../../parser/Parser.h"
#include "../../../utils/utils.h"
#include "../../../visitors/Analyzer.h"
#include "../../../visitors/Transformer.h"
#include "../../../visitors/TypeChecker.h"
#include "../../../visitors/analyzers/DefinitveAssigment.h"
#include <fstream>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::initializeCoreRuntime() {
    auto dbg = new DBGSourceInfo(ctx->module->getSourceInfo(), 0);
    auto import =
            Syntax::N<Syntax::Statement::ImportStmt>(std::vector<std::string>{"_$core"}, "Core");
    import->setDBGInfo(dbg);
    trans(import);

    ctx->uuidStack.push_back(ctx->imports->CORE_UUID + "_$core");

    // std::map<std::string, std::vector<std::string>> typeAliases = {
    //     { "String", {} },
    //     { "Exception", {} },
    //     { "Vector", { "_StoreType" } },
    //     { "StringView", { "_CharType" } },
    //     { "Iterable", { "_IteratorType" } }
    // };
    //
    // for (auto [type, generics] : typeAliases) {
    //    auto uuid = ctx->imports->CORE_UUID + "_$core." + type;
    //    auto mainUuid = ctx->module->getUniqueName() + "." + type;
    //    auto fetchedType = ctx->cache->getTransformedType(uuid);
    //    assert(fetchedType || (generics.size() > 0));
    //    if (generics.size() == 0) {
    //        auto identifiers = ctx->cache->identifierLookup[uuid];
    //        auto types = fetchedType.value();
    //        assert(identifiers.size() == types.size());
    //        int i = 0;
    //        for (auto x : types) {
    //            auto id = identifiers[i++];
    //            utils::replaceAll(id, uuid, mainUuid);
    //            ctx->cache->setTransformedType(mainUuid, x, id);
    //        }
    //    }
    //
    //    auto cachedType = ctx->cache->getType(uuid);
    //    assert(cachedType);
    //    ctx->cache->setType(mainUuid, cachedType.value().type, cachedType.value().state);
    //}
}

} // namespace Syntax
} // namespace snowball