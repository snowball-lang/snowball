#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Expression::ConstantValue) {
    std::shared_ptr<ir::Value> value = nullptr;

    switch (p_node->getType()) {
#define CASE(t) case Expression::ConstantValue::ConstantType::t
        CASE(String) : {
            auto str = p_node->getValue();

            // Remove the "" from the string value
            str   = str.substr(1, str.size() - 2);
            value = ctx->module->N<ir::StringValue>(p_node->getDBGInfo(), str);
            value->setType(ctx->getStringType());
            break;
        }

        CASE(Number) : {
            auto str = p_node->getValue();

            snowball_int_t n = 0;
            if (utils::startsWith(str, "0x") && utils::startsWith(str, "0X")) {
                n = std::stoll(str, nullptr, 16);
            } else if (utils::startsWith(str, "0x") &&
                       utils::startsWith(str, "0X")) {
                n = std::stoul(str.substr(2, (size_t)(str.size() - 2)), nullptr,
                               2);
            } else {
                n = std::stoll(str); // We asume the number is correct
            }

            value = ctx->module->N<ir::NumberValue>(p_node->getDBGInfo(), n);
            value->setType(ctx->getInt32Type());
            break;
        }

        CASE(Float) : {
            auto str = p_node->getValue();
            auto d   = std::stod(str);

            value = ctx->module->N<ir::FloatValue>(p_node->getDBGInfo(), d);
            value->setType(ctx->getF64Type());
            break;
        }

        CASE(Bool) : {
            auto str = p_node->getValue();
            auto b   = str == _SNOWBALL_KEYWORD__TRUE;

            value = ctx->module->N<ir::BooleanValue>(p_node->getDBGInfo(), b);
            value->setType(ctx->getBoolType());
            break;
        }

        CASE(Null) : {
            value = ctx->module->N<ir::NullValue>(p_node->getDBGInfo());
            // TODO: set a null type
            break;
        }

        CASE (Char) : {
            auto str = p_node->getValue();

            str   = str.substr(1, str.size() - 2);
            auto ascii = (int)str[0];
            value = ctx->module->N<ir::NumberValue>(p_node->getDBGInfo(), ascii);
            value->setType(ctx->getInt8Type());
            break;
        }

        default: {
            E<BUG>(FMT("Undefined constant type (%i)", p_node->getType()));
        }
#undef CASE
    }

    this->value = value;
}

} // namespace Syntax
} // namespace snowball