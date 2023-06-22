
#include "../../ast/errors/error.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>

using namespace snowball::utils;

namespace snowball
{
namespace codegen
{

void
LLVMBuilder::setDebugInfoLoc(ir::Value* v) {
    if (v) {
        auto info = v->getDBGInfo();
        if (auto f = ctx->getCurrentFunction(); (info != nullptr && f != nullptr)) {
            auto loc = llvm::DILocation::get(*context, info->line, info->pos.second,
                                             f->getSubprogram());

            builder->SetCurrentDebugLocation(loc);
            return;
        }
    }

    builder->SetCurrentDebugLocation(llvm::DebugLoc());
}

} // namespace codegen
} // namespace snowball
