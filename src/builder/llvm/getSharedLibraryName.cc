
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

std::string LLVMBuilder::getSharedLibraryName(std::string name) {
#if defined(__APPLE__)
  return "\x01" + name;
#else
  return name;
#endif
}

} // namespace codegen
} // namespace snowball
