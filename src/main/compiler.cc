
#include "main/reky.h"
#include "main/compiler.h"

#include "common/stl.h"

namespace snowball {

auto Compiler::Execute() -> bool {
  return ExecuteReky();
}

auto Compiler::ExecuteReky() -> bool {
  reky::Reky reky;
  // TODO: Return modules to compile.
  return reky.Execute();
}

}; // namespace snowball
