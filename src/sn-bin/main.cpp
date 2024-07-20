module;
import app;

using namespace snowball;

#ifdef __cplusplus
extern "C" {
#endif

/// @brief The entry point of the application.
int main(int argc, char* argv[]) {
  return Application::Run(argc, argv);
}

#ifdef __cplusplus
}
#endif
