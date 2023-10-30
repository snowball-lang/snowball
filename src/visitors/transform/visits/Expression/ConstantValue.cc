#include "../../../Transformer.h"

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
      auto prefix = p_node->getPrefix();

      // Remove the "" from the string value
      str = str.substr(1, str.size() - 2);
      value = getBuilder().createStringValue(p_node->getDBGInfo(), str);
      value->setType(ctx->getUIntType(8)->getPointerTo(false));
      
      if (prefix.empty()) {
        auto size = getBuilder().createNumberValue(p_node->getDBGInfo(), str.size());
        size->setType(ctx->getInt32Type());

        auto index = N<Expression::Index>(
                utils::startsWith(ctx->module->getUniqueName(), (ctx->imports->CORE_UUID + "Core")) ?
                        (Expression::Base*) N<Expression::Identifier>("String") :
                        (Expression::Base*) N<Expression::Index>(
                                N<Expression::Identifier>("Core"), N<Expression::Identifier>("String"), true
                        ),
                N<Expression::Identifier>("from"),
                true
        );
        index->setDBGInfo(p_node->getDBGInfo());
        index->getBase()->setDBGInfo(p_node->getDBGInfo());

        auto [result, _] = getFromIndex(p_node->getDBGInfo(), index, true);
        auto fn = getFunction(p_node, result, "String::from", {value->getType(), size->getType()});

        assert(fn != nullptr);
        value = getBuilder().createCall(p_node->getDBGInfo(), fn, {value, size});
        value->setType(fn->getRetTy());
      } else if (prefix == "b") {}
      else {
        E<SYNTAX_ERROR>(p_node->getDBGInfo(), FMT("Invalid string prefix '%s'", prefix.c_str()), {
          .info = "Invalid prefix",
          .note = "Valid prefixes are: '', 'b'"
        });
      }

      break;
    }

    CASE(Number) : {
      auto str = p_node->getValue();

      snowball_int_t n = 0;
      if (utils::startsWith(str, "0x") || utils::startsWith(str, "0X")) {
        n = std::stoll(str, nullptr, 16);
      } else if (utils::startsWith(str, "0b") || utils::startsWith(str, "0B")) {
        n = std::stoul(str.substr(2, (size_t) (str.size() - 2)), nullptr, 2);
      } else {
        // TODO: big numbers!
        n = std::stoll(str); // We asume the number is correct
      }

      value = getBuilder().createNumberValue(p_node->getDBGInfo(), n);
      getBuilder().setType(value, ctx->getInt32Type());
      break;
    }

    CASE(Float) : {
      auto str = p_node->getValue();
      auto d = std::stod(str);

      value = getBuilder().createFloatValue(p_node->getDBGInfo(), d);
      getBuilder().setType(value, ctx->getF64Type());
      break;
    }

    CASE(Bool) : {
      auto str = p_node->getValue();
      auto b = str == _SNOWBALL_KEYWORD__TRUE;

      value = getBuilder().createBooleanValue(p_node->getDBGInfo(), b);
      getBuilder().setType(value, ctx->getBoolType());
      break;
    }

    CASE(Char) : {
      auto str = p_node->getValue();

      str = str.substr(1, str.size() - 2);
      auto ascii = (int) str[0];
      value = getBuilder().createCharValue(p_node->getDBGInfo(), ascii);
      getBuilder().setType(value, ctx->getUIntType(8));
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