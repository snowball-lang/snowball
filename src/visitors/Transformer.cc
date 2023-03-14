
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

Transformer::Transformer(std::shared_ptr<ir::Module> mod, ptr<SourceInfo> srci)
    : AcceptorExtend<Transformer, Visitor>(srci) {
    ctx = new TransformContext(mod);
}

std::vector<std::shared_ptr<ir::Module>> Transformer::getModules() const {
    return modules;
}
void Transformer::addModule(std::shared_ptr<ir::Module> m) {
    modules.push_back(m);
}
auto Transformer::getModule() const { return ctx->module; }

// mark: - noops

SN_TRANSFORMER_VISIT(Expression::TypeRef) { assert(false); }

} // namespace Syntax
} // namespace snowball