
#include "../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::string TransformContext::createIdentifierName(const std::string name,
                                                   bool includeBase) {
    std::string result;
    bool alreadyGenerated = name.find('.') != std::string::npos;

    if (includeBase && !alreadyGenerated) {
        alreadyGenerated = true;
        if (currentClass != nullptr) {
            result = currentClass->getUUID() + "." + name;
        } else {
            auto currentModule = module->getUniqueName();

            // TODO: include class name if exists.
            result = currentModule + "." + name;
        }
    }

    if (!includeBase && !alreadyGenerated) {
        auto currentModule = module->getUniqueName();
        result = currentModule + "." + name;
    }

    return result;
}

} // namespace Syntax
} // namespace snowball