
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
void Transformer::addModule(std::shared_ptr<ir::Module> m) { modules.push_back(m); }
auto Transformer::getModule() const { return ctx->module; }
void Transformer::visit(std::vector<Node*> p_nodes) {
    ctx->withScope([&] {
        AcceptorExtend::visit(p_nodes);

        ctx->generateFunction = true;
        for (auto node : p_nodes) {
            if (utils::cast<Statement::BodiedFunction>(node) ||
                utils::cast<Statement::LLVMFunction>(node) ||
                utils::cast<Statement::ConstructorDef>(node) ||
                utils::cast<Statement::Namespace>(node) ||
                utils::cast<Statement::DefinedTypeDef>(node) ||
                utils::cast<Statement::TypeAlias>(node)) {
                node->accept(this);
            }
        }

        ctx->generateFunction = false;
    });
}

// mark: - noops

SN_TRANSFORMER_VISIT(Expression::TypeRef) { assert(false); }

} // namespace Syntax
} // namespace snowball