#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::Index) {
    assert(false && "TODO: index node");
    std::shared_ptr<ir::Value> value = nullptr;
    this->value                      = value;
}

} // namespace Syntax
} // namespace snowball