#include "../../../../ir/values/Cast.h"
#include "../../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

SN_TRANSFORMER_VISIT(Statement::Switch) {
  auto expr = trans(p_node->getExpr());
  auto cases = p_node->getCases();
  auto cStyleSwitch = p_node->isCStyleSwitch();

  if (!cStyleSwitch) {
    auto switchType = expr->getType();
    if (!utils::is<types::EnumType>(switchType)) {
      E<SYNTAX_ERROR>(p_node, "Switch expression must be of enum type!", {
        .info = "Not an enum type!",
        .help = "Try changing the expression to an enum type."
      });
    }

    auto enumType = utils::cast<types::EnumType>(switchType);
    auto enumFields = enumType->getFields();

    std::vector<ir::Switch::Case> irCases;
    bool hasDefault = std::any_of(cases.begin(), cases.end(), [](auto x) { return x.isDefault; });
    if (cases.size() != enumFields.size() && !hasDefault) {
      E<SYNTAX_ERROR>(p_node, "Switch must have a case for every enum field!", {
        .info = FMT("Enum '%s' has %d fields, but switch has %d cases!", enumType->getName().c_str(), enumFields.size(), cases.size()),
        .note = "You can add a default case to handle the remaining fields.",
        .help = ("Try adding a case for every enum field.\n"
                "Enum fields are:\n - " + utils::join<std::vector<types::EnumType::EnumField>::iterator>(enumFields.begin(), enumFields.end(), "\n - ", [&](auto x) { return x->name; }))
      });
    }
    std::shared_ptr<ir::Block> defaultBlock = nullptr;
    for (auto caseInstance : cases) {
      if (caseInstance.isDefault) {
        defaultBlock = utils::dyn_cast<ir::Block>(trans(caseInstance.block));
        continue;
      }
      auto caseArgs = caseInstance.args;
      auto caseBlock = caseInstance.block;
      auto field = std::find_if(enumFields.begin(), enumFields.end(), [&](auto field) {
        return field.name == caseInstance.expressionAsString();
      });
      if (field == enumFields.end()) {
        E<SYNTAX_ERROR>(p_node, "Case arguments must match enum fields!", {
          .info = FMT("Enum '%s' does not have field '%s'!", enumType->getName().c_str(), caseInstance.expressionAsString().c_str()),
          .help = ("Try changing the case arguments to match the enum fields.\n"
                  "Enum fields are:\n - " + utils::join<std::vector<types::EnumType::EnumField>::iterator>(enumFields.begin(), enumFields.end(), "\n - ", [&](auto x) { return x->name; }))
        }); 
      }

      if (caseArgs.size() != field->types.size()) {
        if (!(caseArgs.size() < field->types.size() && caseInstance.isVariadic)) {
          E<SYNTAX_ERROR>(p_node, "Case arguments must match enum fields!", {
            .info = FMT("Enum field '%s' has %d arguments, but case has %d arguments!", field->name.c_str(), field->types.size(), caseArgs.size()),
            .help = ("Try changing the case arguments to match the enum fields.\n"
                    "Enum fields are:\n - " + utils::join<std::vector<types::Type*>::iterator>(field->types.begin(), field->types.end(), "\n - ", [](auto x) { return (*x)->getPrettyName(); }))
          });
        }
      } else if (caseInstance.isVariadic) {
        E<SYNTAX_ERROR>(p_node, "Variadic is not needed!", {
          .info = FMT("Enum field '%s' has %d arguments, but case has %d arguments!", field->name.c_str(), field->types.size(), caseArgs.size()),
          .help = ("Try removing the variadic operator.\n"
                  "Enum fields are:\n - " + utils::join<std::vector<types::Type*>::iterator>(field->types.begin(), field->types.end(), "\n - ", [](auto x) { return (*x)->getPrettyName(); }))
        });
      }
      ctx->withScope([&] {
        std::vector<std::shared_ptr<ir::VariableDeclaration>> irArgs = {};
        for (size_t i = 0; i < caseArgs.size(); i++) {
          auto var = getBuilder().createVariable(p_node->getDBGInfo(), caseArgs[i], false, false, ctx->getScopeIndex());
          getBuilder().setType(var, field->types[i]);
          auto varDecl = getBuilder().createVariableDeclaration(p_node->getDBGInfo(), var, nullptr);
          varDecl->setId(var->getId());
          auto item = std::make_shared<transform::Item>(transform::Item::VALUE, var);
          ctx->addItem(caseArgs[i], item);
          assert(ctx->getCurrentFunction());
          ctx->getCurrentFunction()->addSymbol(varDecl);
          irArgs.push_back(varDecl);
        }
        irCases.push_back(ir::Switch::Case {
          .args = irArgs,
          .block = utils::dyn_cast<ir::Block>(trans(caseBlock)),
          .name = field->name
        });
      });
    }

    auto irSwitch = getBuilder().createSwitch(p_node->getDBGInfo(), expr, irCases, defaultBlock);
    this->value = irSwitch;
  } else {
    auto switchType = expr->getType();
    if (!utils::is<types::IntType>(switchType)) {
      E<SYNTAX_ERROR>(p_node, "Switch expression must be of integer type!", {
        .info = "Not an integer type!",
        .help = "Try changing the expression to an integer type."
      });
    }

    std::vector<ir::Switch::CStyleCase> irCases;
    std::shared_ptr<ir::Block> defaultBlock = nullptr;

    for (auto& caseInstance : cases) {
      if (caseInstance.isDefault) {
        defaultBlock = utils::dyn_cast<ir::Block>(trans(caseInstance.block));
        assert(defaultBlock != nullptr);
        continue;
      }

      auto expr = caseInstance.getExpression();
      auto block = caseInstance.block;

      if (auto constant = utils::cast<Expression::ConstantValue>(expr)) {
        switch (constant->getType()) {
          case Expression::ConstantValue::String:
            E<SYNTAX_ERROR>(p_node, "Switch case cannot be a string!", {
              .info = "Not an integer type!",
              .help = "Try changing the case to an integer type."
            });
            break;
          case Expression::ConstantValue::Float:
            E<SYNTAX_ERROR>(p_node, "Switch case cannot be a float!", {
              .info = "Not an integer type!",
              .help = "Try changing the case to an integer type."
            });
            break;
          default:
            break;
        }
      } else {
        E<SYNTAX_ERROR>(p_node, "Switch case must be a constant value!", {
          .info = "Not a constant value!",
          .help = "Try changing the case to a constant value."
        });
      }

      assert(caseInstance.args.size() == 0);
      irCases.push_back(ir::Switch::CStyleCase {
        .value = trans(expr),
        .block = utils::dyn_cast<ir::Block>(trans(block))
      });
      assert(irCases.back().block != nullptr);
    }

    if (defaultBlock == nullptr) {
      E<SYNTAX_ERROR>(p_node, "Switch must have a default case!", {
        .info = "No default case!",
        .help = "Try adding a default case."
      });
    }

    auto irSwitch = getBuilder().createSwitch(p_node->getDBGInfo(), expr, irCases, defaultBlock);
    this->value = irSwitch;
  }
}

} // namespace Syntax
} // namespace snowball