
#include "compiler/frontend/sema/borrow.h"

namespace snowball {
namespace frontend {
namespace sema::borrow {

void BorrowChecker::enter_scope() {
  scopes.push_back({});
}

BorrowChecker::Result<CleanStatus> BorrowChecker::exit_scope(std::optional<Scope> unified_scope) {
  auto scope = scopes.back();
  scopes.pop_back();
  CleanStatus clean_status;
  if (unified_scope) {
    for (auto& init : (*unified_scope).initialized) {
      auto var = get_variable(init, true);
      if (std::find(scope.initialized.begin(), scope.initialized.end(), init) != scope.initialized.end()
        && var.has_value()) {
        if (var->get_status() == VariableStatusType::Uninitialized) {
          scopes.back().variables[init].set_initialized();
          scopes.back().initialized.push_back(init);
        }
      }   
    }
  }
  for (auto& [id, status] : scope.variables) {
    if (status.is_initialized()) {
      clean_status.add_dropped(id);
    }
  }
  return {{}, clean_status};
}

std::optional<VariableStatus> BorrowChecker::get_variable(uint64_t id, bool current_scope_only) {
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    auto& scope = *it;
    auto var = scope.variables.find(id);
    if (var != scope.variables.end()) {
      return var->second;
    }
    if (current_scope_only) {
      break;
    }
  }
  return std::nullopt;
}

void BorrowChecker::declare_variable(uint64_t id, const std::string& name, VariableStatusType status) {
  scopes.back().variables[id].set_status(status);
  // if (status == VariableStatusType::Initialized) {
  //   scopes.back().initialized.push_back(id);
  // }
}

}
}
}
