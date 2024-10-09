
#pragma once

namespace snowball {

/// @brief A castable class.
/// This class is used to cast between different types, this is useful
/// when we want to encapsulate a type and cast it to it's child type.
template <typename T> class Castable {
public:
  /// @brief Cast to the child type.
  /// @return The child type.
  template <typename U> inline auto Cast() -> U& {
    CheckType<U>();
    return static_cast<U&>(*this);
  }

  /// @brief Cast to the child type.
  /// @return The child type.
  template <typename U> inline auto Cast() const -> const U& {
    CheckType<U>();
    return static_cast<const U&>(*this);
  }

  /// @brief Checks if the type is the same as the given type.
  /// @return True if the type is the same, false otherwise.
  template <typename U> inline auto Is() const -> bool {
    return Cast(U) != nullptr;
  }

private:
  /// @brief Check if the type is the same as the given type.
  /// @return True if the type is the same, false otherwise.
  template <typename U> auto CheckType() void {
    static_assert(std::is_base_of_v<T, U>, "U must be a child of T.");
  }

protected:
  Castable() = default;
  ~Castable() = default;
};

}; // namespace snowball