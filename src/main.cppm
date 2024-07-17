
import app;

int main(int argc, char** argv) {
  // Initialize the application. This will run the whole command line parsing
  // and compiler process.
  app::App app(argc, argv);

  return app.Run();
}
