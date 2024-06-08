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
namespace sema {

enum class LifetimeStatus 
{
  None = 0,
  Uninitialized,
  Initialized,
  Dropped
};

class LifetimeHelper {
  LifetimeStatus status = LifetimeStatus::None;
public:
  LifetimeHelper() = default;
  virtual ~LifetimeHelper() = default;

  void set_status(LifetimeStatus status) { this->status = status; }
  LifetimeStatus get_status() const { return status; }

  void set_uninitialized() { set_status(LifetimeStatus::Uninitialized); }
  void set_initialized() { set_status(LifetimeStatus::Initialized); }
  void set_dropped() { set_status(LifetimeStatus::Dropped); }

  bool is_uninitialized() const { return get_status() == LifetimeStatus::Uninitialized; }
  bool is_initialized() const { return get_status() == LifetimeStatus::Initialized; }
  bool is_dropped() const { return get_status() == LifetimeStatus::Dropped; }
};

} // namespace sema
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_SEMA_LIFETIME_H__
