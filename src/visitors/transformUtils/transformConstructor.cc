#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::vector<std::shared_ptr<ir::Value>>
Transformer::transformConstructor(Statement::ConstructorDef* p_node) {
    auto instrList = std::vector<std::shared_ptr<ir::Value>>();
    auto currentClass = ctx->getCurrentClass();
    if (p_node->hasSuperArgs()) {
        auto [selfArg, foundSelfArg] = ctx->getInCurrentScope("self");
        assert(foundSelfArg);
        auto superArgs = p_node->getSuperArgs();
        auto parentClass = currentClass->getParent();
        auto parentClassRef = parentClass->toRef();
        auto newInstance =
                Syntax::N<Expression::NewInstance>(p_node->getDBGInfo(), superArgs, parentClassRef);
        newInstance->setDBGInfo(p_node->getDBGInfo());
        newInstance->accept(this);
        utils::dyn_cast<ir::ObjectInitialization>(this->value)->createdObject = selfArg->getValue();
        instrList.emplace_back(this->value);
    }

    return instrList;
}

} // namespace Syntax
} // namespace snowball