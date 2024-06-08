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
namespace ast {

enum class BorrowStatus 
{
  None = 0,
  Uninitialized,
  Initialized,
  Borrowed,
  MutablyBorrowed,
};

class Borrowable {
  BorrowStatus status = BorrowStatus::None;
public:
  Borrowable() = default;
  virtual ~Borrowable() = default;

  void set_status(BorrowStatus status) { this->status = status; }
  BorrowStatus get_status() const { return status; }

  void set_uninitialized() { set_status(BorrowStatus::Uninitialized); }
  void set_initialized() { set_status(BorrowStatus::Initialized); }
  void set_borrowed() { set_status(BorrowStatus::Borrowed); }
  void set_mutably_borrowed() { set_status(BorrowStatus::MutablyBorrowed); }

  bool is_uninitialized() const { return get_status() == BorrowStatus::Uninitialized; }
  bool is_initialized() const { return get_status() == BorrowStatus::Initialized; }
  bool is_borrowed() const { return get_status() == BorrowStatus::Borrowed; }
  bool is_mutably_borrowed() const { return get_status() == BorrowStatus::MutablyBorrowed; }
};

} // namespace sema
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_SEMA_LIFETIME_H__
