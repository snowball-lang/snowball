
#pragma once

namespace snowball {

/// @brief The main compiler class.
/// It takes control of the compiler process. It is responsible for
/// initializing the CLI, running the package manager, etc.
class Compiler final {
public:
  /// @brief The constructor.
  Compiler() = default;

  /// @brief The destructor.
  ~Compiler() = default;

  /// @brief The copy constructor.
  Compiler(const Compiler&) = delete;

  /// @brief The move constructor.
  Compiler(Compiler&&) = delete;

  /// @brief The copy assignment operator.
  Compiler& operator=(const Compiler&) = delete;

  /// @brief The move assignment operator.
  Compiler& operator=(Compiler&&) = delete;

  /// @brief The main compiler function.
  void Run();
};

} // namespace snowball
