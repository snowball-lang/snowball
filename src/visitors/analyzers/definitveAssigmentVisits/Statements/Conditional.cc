
#include "../../DefinitveAssigment.h"

#include <algorithm>
#include <optional>

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Statement::Conditional) {
  p_node->getCondition()->accept(this);

  std::vector<std::string> blockInited;
  asBlock([&] {
    for (auto i : p_node->getBlock()->getStmts()) { i->accept(this); }

    blockInited = this->state.inited;
  });

  if (auto e = p_node->getElse()) {
    std::vector<std::string> elseInited;
    asBlock([&] {
      for (auto i : p_node->getBlock()->getStmts()) { i->accept(this); }

      elseInited = this->state.inited;
    });

    for (auto id : blockInited) {
      auto var = getIdentifier(id);
      if ((std::find(elseInited.begin(), elseInited.end(), id) != elseInited.end()) && var != std::nullopt) {
        if (var.value().second == NotInitialized) {
          this->state.inited.push_back(id);
          this->scopes.front()[id] = Initialized;
        }
      }
    }
  }
}

} // namespace Syntax
} // namespace snowball
