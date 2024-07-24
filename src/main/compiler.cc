
#include "reky/reky.h"
#include "main/compiler.h"

#include "common/stl.h"

namespace snowball {

auto Compiler::Execute() -> bool {
  return ExecuteReky();
}

auto Compiler::ExecuteReky() -> bool {
  // TODO: Return modules to compile.
  return reky::GetRekyManager().Execute();
}

}; // namespace snowball
