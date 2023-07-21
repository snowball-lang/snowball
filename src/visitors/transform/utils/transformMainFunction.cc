#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::transformMainFunction(Statement::FunctionDef* p_node) {
    assert(ctx->module->isMain());
    assert(p_node->getName() == "main");
    assert(p_node->getPrivacy() == Statement::Privacy::PUBLIC);

    // Checking for errors
    if (p_node->getArgs().size() > 0) {
        E<SYNTAX_ERROR>(p_node, "Program entry point can't have parameters!");
    } else if (p_node->isExtern()) {
        E<SYNTAX_ERROR>(p_node, "Program entry point can't have and external flag!");
    } else if (p_node->getGenerics().size() > 0) {
        E<SYNTAX_ERROR>(p_node, "Program entry point can't have generics!");
    } else if (cast<Statement::BodiedFunction>(p_node) == nullptr) {
        E<SYNTAX_ERROR>(p_node, "Program entry can't be a declaration!");
    } // TODO: main function cant be variadic!

    auto rawRetTy = p_node->getRetType();
    auto returnType = transformType(rawRetTy);

    if (!utils::cast<types::Int32Type>(returnType)) {
        E<SYNTAX_ERROR>(rawRetTy, "Program entry's return type must be of type 'i32'!");
    }

    // Create a new function value.
    // notes: The name will always be "main" and the function shall not
    // have any arguments.
    auto fn = transformFunction({p_node, ctx->saveState()}, {}, true);
    fn->setExternalName("main");
}

} // namespace Syntax
} // namespace snowball
