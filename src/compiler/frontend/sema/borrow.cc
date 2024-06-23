
#include "compiler/frontend/sema/borrow.h"

namespace snowball {
namespace frontend {
namespace sema::borrow {

void BorrowChecker::enter_scope() {
  scopes.push_back(Scope());
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
        if (var.value()->get_status() == VariableStatusType::Uninitialized) {
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

std::optional<VariableStatus*> BorrowChecker::get_variable(uint64_t id, bool current_scope_only) {
  for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
    auto& scope = *it;
    auto var = scope.variables.find(id);
    if (var != scope.variables.end()) {
      return &var->second;
    }
    if (current_scope_only) {
      break;
    }
  }
  return std::nullopt;
}

void BorrowChecker::declare_variable(uint64_t id, const std::string& name, VariableStatusType status) {
  scopes.back().variables.try_emplace(id, VariableStatus(name, status));
  // if (status == VariableStatusType::Initialized) {
  //   scopes.back().initialized.push_back(id);
  // }
}

void BorrowChecker::assign_variable(uint64_t id) {
  auto var = get_variable(id);
  assert(var.has_value());
  // We don't need to check if the variable is initialized here!
  var.value()->set_moved();
}

BorrowChecker::ResultOpt BorrowChecker::check_var_use(uint64_t id, bool is_assignment, bool is_copy) {
  auto var = get_variable(id);
  if (!var.has_value()) return {}; // It's ok
  auto var_value = var.value();
  switch (var_value->get_status()) {
    case VariableStatusType::Moved:
      if (is_copy) { return {}; } // It's ok 
      return {BorrowError {
        .kind = BorrowError::Kind::UseAfterMove,
        .message = F("Variable '{}' used after move!", var_value->get_name())
      }};
    case VariableStatusType::Uninitialized:
      if (!is_assignment && std::find(scopes.back().initialized.begin(), scopes.back().initialized.end(), id) == scopes.back().initialized.end()) {
        return {BorrowError {
          .kind = BorrowError::Kind::UseBeforeInit,
          .message = F("Variable '{}' used before initialization!", var_value->get_name())
        }};
      } [[fallthrough]];
    default:
      return {};
  }
}

void BorrowChecker::init_variable(uint64_t id) {
  auto var = get_variable(id);
  assert(var.has_value());
  scopes.back().initialized.push_back(id);
}

}
}
}
