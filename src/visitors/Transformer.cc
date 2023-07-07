
#include "Transformer.h"

#include "../ast/syntax/nodes.h"
#include "../ast/types/FunctionType.h"
#include "../ast/visitor/Visitor.h"
#include "../ir/module/Module.h"
#include "../ir/values/Argument.h"
#include "../ir/values/Call.h"
#include "../ir/values/Constants.h"
#include "../ir/values/Func.h"
#include "../ir/values/Return.h"
#include "../ir/values/Throw.h"
#include "../ir/values/ValueExtract.h"
#include "../utils/utils.h"
#include "TransformContext.h"

#include <assert.h>
#include <memory>
#include <string>
#include <vector>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

Transformer::Transformer(std::shared_ptr<ir::Module> mod, SourceInfo* srci)
    : AcceptorExtend<Transformer, Visitor>(srci) {
    builder = ir::IRBuilder(mod);
    ctx = new TransformContext(mod, builder);
    initializeCoreRuntime();
}

std::vector<std::shared_ptr<ir::Module>> Transformer::getModules() const { return modules; }
void Transformer::addModule(std::shared_ptr<ir::Module> m) { 
    ctx->cache->addModule(m->getUniqueName(), m);
    modules.push_back(m); 
}
auto Transformer::getModule() const { return ctx->module; }
void Transformer::visitGlobal(std::vector<Node*> p_nodes) {
    ctx->withScope([&] {
        bool backup = ctx->generateFunction;
        ctx->generateFunction = false;
        for (auto node : p_nodes) {
            SN_TRANSFORMER_CAN_GENERATE(node) { node->accept(this); }
        }

        ctx->generateFunction = true;
        AcceptorExtend::visitGlobal(p_nodes);
        ctx->generateFunction = backup;
    });
}

// mark: - noops

SN_TRANSFORMER_VISIT(Expression::TypeRef) { assert(false); }

} // namespace Syntax
} // namespace snowball