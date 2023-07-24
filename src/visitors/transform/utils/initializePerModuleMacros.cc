#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::initializePerModuleMacros() {
    auto pkgMacro = N<Macro>("pkg", std::vector<std::tuple<std::string, Macro::ArguementType, Node*>>
        {{ "e", Macro::ArguementType::EXPRESSION, nullptr }}, nullptr);
    auto pkgInstance = new transform::MacroInstance(pkgMacro, ctx->module);
    auto pkgMacroItem = std::make_shared<transform::Item>(pkgInstance);
    ctx->addItem("pkg", pkgMacroItem);
}

} // namespace Syntax
} // namespace snowball