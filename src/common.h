
#include <memory>

#ifndef __SNOWBALL_COMMON_H_
#define __SNOWBALL_COMMON_H_

namespace snowball {
template <typename Derived, typename Parent> class AcceptorExtend : public Parent {
  public:
    using Parent::Parent;
};

template <typename T> using UniquePtr = std::unique_ptr<T>;
} // namespace snowball

#endif // __SNOWBALL_COMMON_H_
