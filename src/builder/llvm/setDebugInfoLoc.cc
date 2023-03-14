
#include "../../ast/errors/error.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/DerivedTypes.h>
#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>
#include <memory>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

void LLVMBuilder::setDebugInfoLoc(ptr<ir::Value> v) {
    // TODO: handle inside functions
    auto info = v->getDBGInfo();
    if (auto f = ctx->getCurrentFunction()) {
        auto loc = llvm::DILocation::get(*context, info->line, info->pos.second,
                                         f->getSubprogram());

        builder->SetCurrentDebugLocation(loc);
        return;
    }

    builder->SetCurrentDebugLocation(llvm::DebugLoc());
}

} // namespace codegen
} // namespace snowball