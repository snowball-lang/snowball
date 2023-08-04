
#include "../Driver.h"

namespace snowball {
namespace os {
std::string Driver::getOutputFilename(std::string input, app::Options::EmitType type, bool isStatic) {
#ifdef __APPLE__
  std::string output = input;
  switch (type) {
    case app::Options::EmitType::EXECUTABLE: output; break;
    case app::Options::EmitType::OBJECT: 
        if (isStatic) output += ".a";
        else output += ".dylib";
        break;
    case app::Options::EmitType::LLVM_IR: output += ".ll"; break;
    case app::Options::EmitType::ASSEMBLY: output += ".s"; break;
  }
#elif __linux__
  std::string output = input;
  switch (type) {
    case app::Options::EmitType::EXECUTABLE: output; break;
    case app::Options::EmitType::OBJECT:
        if (isStatic) output += ".a";
        else output += ".so";
        break;
    case app::Options::EmitType::LLVM_IR: output += ".ll"; break;
    case app::Options::EmitType::ASSEMBLY: output += ".s"; break;
  }
#elif _WIN32
  std::string output = input;
  switch (type) {
    case app::Options::EmitType::EXECUTABLE: output += ".exe"; break;
    case app::Options::EmitType::OBJECT:
        if (isStatic) output += ".a";
        else output += ".dll";
        break;
    case app::Options::EmitType::LLVM_IR: output += ".ll"; break;
    case app::Options::EmitType::ASSEMBLY: output += ".s"; break;
  }
#else
#error "Unsupported platform"
#endif
  return output;
}
}
}
