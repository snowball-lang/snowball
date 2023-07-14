
#include "../../errors.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::createTests() {
    assert(ctx->testMode);
    auto testFunction = module->getFunction("sn.test.try"); // Always match this
    for (auto [name, fn] : ctx->tests) {
        auto namePtr = builder->CreateGlobalStringPtr(name, "test.alloca");
        builder->CreateCall(testFunction, {fn, namePtr});
    }
}

} // namespace codegen
} // namespace snowball
