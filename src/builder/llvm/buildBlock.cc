
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::Block> block) {
    for (auto i : block->getBlock()) {
        build(i.get());
    }
}

} // namespace codegen
} // namespace snowball
