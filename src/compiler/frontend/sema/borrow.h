// clang-format off

#ifndef __SNOWBALL_FRONTEND_SEMA_LIFETIME_H__
#define __SNOWBALL_FRONTEND_SEMA_LIFETIME_H__

#include <string>
#include <vector>

#include "compiler/ctx.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/nodes.h"

namespace snowball {
namespace frontend {
namespace sema::borrow {

enum class VariableStatusType 
{
  None = 0,
  Uninitialized,
  Initialized,
  Moved
};

class VariableStatus {
  VariableStatusType status = VariableStatusType::None;
  std::string name;
public:
  VariableStatus() = default;
  virtual ~VariableStatus() = default;

  void set_status(VariableStatusType status) { this->status = status; }
  VariableStatusType get_status() const { return status; }

  void set_uninitialized() { set_status(VariableStatusType::Uninitialized); }
  void set_initialized() { set_status(VariableStatusType::Initialized); }
  void set_moved() { set_status(VariableStatusType::Moved); }

  bool is_uninitialized() const { return get_status() == VariableStatusType::Uninitialized; }
  bool is_initialized() const { return get_status() == VariableStatusType::Initialized; }
  bool is_moved() const { return get_status() == VariableStatusType::Moved; }
};

struct BorrowError {
  enum class Kind {
    OwnershipError,
    BorrowError,
    LifetimeError,
  };

  Kind kind;
  std::string message;
};  

struct Scope {
  std::unordered_map<uint64_t, VariableStatus> variables;
  std::vector<uint64_t> initialized;
};

class CleanStatus {
  std::vector<uint64_t> dropped;
  Scope scope;
public:
  CleanStatus() = default;
  virtual ~CleanStatus() = default;

  void add_dropped(uint64_t id) { dropped.push_back(id); }
  const std::vector<uint64_t>& get_dropped() const { return dropped; }
};

class BorrowChecker {
  std::vector<Scope> scopes = {{}};
public:
  using ResultVec = std::vector<BorrowError>;
  template <typename T>
  using Result = std::pair<ResultVec, T>;
  
  BorrowChecker() = default;
  virtual ~BorrowChecker() = default;

  void enter_scope();
  // @return A clean status, this is used to drop variables that are no longer in scope
  //   e.g. call their destructor
  // @param unified_scope If set, the scope will be unified with the current scope.
  //   This is used for if-else statements, where the scope is the same for both branches
  Result<CleanStatus> exit_scope(std::optional<Scope> unified_scope = std::nullopt);

  void declare_variable(uint64_t id, const std::string& name, VariableStatusType status);
  ResultVec assign_variable(uint64_t id);
  ResultVec borrow_variable(uint64_t id, bool mutable_borrow);

private:
  std::optional<VariableStatus> get_variable(uint64_t id, bool current_scope_only = false);
};

} // namespace ast::borrow
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_SEMA_LIFETIME_H__
