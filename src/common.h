
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

template <typename EnumT, typename BaseEnumT>
class InheritEnum {
 public:
  InheritEnum() { }
  InheritEnum(EnumT e) : enum_(e) { }

  InheritEnum(BaseEnumT e) : baseEnum_(e) { }

  explicit InheritEnum(int val) : enum_(static_cast<EnumT>(val)) { }

  operator EnumT() const { return enum_; }

 private:
  // Note - the value is declared as a union mainly for as a debugging aid. If
  // the union is undesired and you have other methods of debugging, change it
  // to either of EnumT and do a cast for the constructor that accepts BaseEnumT.
  union {
    EnumT enum_;
    BaseEnumT baseEnum_;
  };
};

template <typename T>
using UniquePtr = std::unique_ptr<T>;
} // namespace snowball

#endif // __SNOWBALL_COMMON_H_
