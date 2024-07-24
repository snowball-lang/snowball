
#include "common/error.h"
#include "common/stl.h"
#include "common/location.h"
#include "common/utility/format.h"
#include "common/utility/logger.h"

using namespace snowball::utils;

namespace snowball {

auto FatalError(const Error& error) -> void {
  GetLogger().Error(error.GetMessage());
  std::exit(Failure);
}

auto FatalError(const String& message) -> void {
  FatalError(Error(message));
}

auto CrashError(const String& message) -> void {
  GetLogger().Fatal(message);
  std::exit(Failure);
}

auto UnreachableError(const_ptr_t error) -> void {
  if (error == nullptr) {
    FatalError("Unreachable code reached!");
  }
  FatalError((String)"Unreachable code reached: " + error);
}

}; // namespace snowball
