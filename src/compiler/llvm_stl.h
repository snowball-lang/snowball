
#undef F
#include <llvm/ADT/DenseMap.h>
#include <llvm/ADT/StringMap.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/ADT/TinyPtrVector.h>
#define SNOWBALL_UTILS_REDEFINE_F__
#include "compiler/utils/utils.h"

namespace snowball {

using FunctionsVector = llvm::SmallVector<frontend::ast::FnDecl*, 5>;
}
