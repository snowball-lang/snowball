module;
export module app;

import stl;

namespace snowball {
export namespace app {

/// @brief The application entry point.
/// This class is in charge of the application setup and execution of the 
/// compiler.
class Application final {
public:
  /// @brief The application entry point.
  /// @param argc The number of arguments.
  /// @param argv The arguments.
  /// @return The application exit code.
  static bool Run(int argc, char* argv[]);

  /// @brief Application constructor.
  /// @see ::Run
  Application(int argc, char* argv[]);

  /// @brief Execute the application.
  bool RunAsMain();

private:
  Vector<String> mArguments;
};

} // namespace app
} // namespace snowball

