
#include <memory>

#ifndef __SNOWBALL_COMMON_H_
#define __SNOWBALL_COMMON_H_

namespace snowball {
template <typename Derived, typename Parent>
class AcceptorExtend : public Parent {
  public:
    using Parent::Parent;
};

#if 0
template <class Base>
class enable_shared_from_base
  : public std::enable_shared_from_this<Base>
{
protected:
    template <class Derived>
    std::shared_ptr<Derived> shared_from_base()
    {
        return std::static_pointer_cast<Derived>(shared_from_this());
    }
};
#endif

template <typename T>
using UniquePtr = std::unique_ptr<T>;
} // namespace snowball

#endif // __SNOWBALL_COMMON_H_
