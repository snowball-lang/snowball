
#include <cstdint>
#include <stdio.h>

#ifndef __SNOWBALL_ID_MIXIN_H_
#define __SNOWBALL_ID_MIXIN_H_

namespace snowball {
namespace ir {

using id_t = std::uint64_t;

/// Mixin class for IR nodes that need ids.
class IdMixin {
  private:
    /// the global id counter
    static id_t currentId;

  protected:
    /// the instance's id
    id_t id;

  public:
    /// Resets the global id counter.
    static void resetId();

    IdMixin() : id(currentId++) { }
    IdMixin(const IdMixin&) = delete;
    IdMixin& operator=(const IdMixin&) = delete;

    /// @return the node's id.
    virtual id_t getId() const { return id; }
    /// @brief Set a "constant" ID to the IDMixin object it inherits
    ///  from.
    /// @note This must be used wisely and not very often!
    virtual void setId(id_t i) { id = i; }
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_ID_MIXIN_H_
