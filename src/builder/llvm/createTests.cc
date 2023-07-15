
#include "../../errors.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::createTests(llvm::Function* mainFunction) {
    assert(ctx->testMode);
    auto printFunction = getPrintfFunction();

    mainFunction->addFnAttr(llvm::Attribute::NoInline);
    mainFunction->addFnAttr(llvm::Attribute::OptimizeNone);

    builder->CreateCall(printFunction,
                        {builder->CreateGlobalStringPtr(FMT("\nExecuting %s%i%s test(s)...\n", BBLU,
                                                            ctx->tests.size(), RESET),
                                                        "test.msg")});

    auto successCount = builder->CreateAlloca(builder->getInt32Ty(), nullptr, "success.count");
    auto failCount = builder->CreateAlloca(builder->getInt32Ty(), nullptr, "fail.count");
    auto skipCount = 0;

    builder->CreateStore(builder->getInt32(0), successCount);
    builder->CreateStore(builder->getInt32(0), failCount);

    auto end = llvm::BasicBlock::Create(builder->getContext(), "end", mainFunction);
    auto testFunction = module->getFunction("sn.test.try"); // Always match this
    for (auto [fn, llvmFunc] : ctx->tests) {
        auto name = fn->getNiceName();
        auto attrArgs = fn->getAttributeArgs(Attributes::TEST);
        auto shouldSkip = attrArgs.find("skip") != attrArgs.end();
        auto namePtr = builder->CreateGlobalStringPtr(name, "test.alloca");
        auto call = builder->CreateCall(testFunction,
                                        {llvmFunc, namePtr, builder->getInt1(shouldSkip)});
        auto shouldContinue = builder->CreateICmpEQ(call, builder->getInt32(0));
        if (shouldSkip) {
            skipCount++;
        } else {
            auto successBlock = llvm::BasicBlock::Create(builder->getContext(), "success", mainFunction);
            auto failBlock = llvm::BasicBlock::Create(builder->getContext(), "fail", mainFunction);
            auto continueBlock = llvm::BasicBlock::Create(builder->getContext(), "continue", mainFunction);
            builder->CreateCondBr(shouldContinue, successBlock, failBlock);

            builder->SetInsertPoint(successBlock);
            builder->CreateStore(builder->CreateAdd(builder->CreateLoad(builder->getInt32Ty(), successCount), builder->getInt32(1)),
                                successCount);
            builder->CreateBr(continueBlock);

            builder->SetInsertPoint(failBlock);
            builder->CreateStore(builder->CreateAdd(builder->CreateLoad(builder->getInt32Ty(), failCount), builder->getInt32(1)),
                                failCount);
            builder->CreateBr(continueBlock);
            builder->SetInsertPoint(continueBlock);
        }
    }

    builder->CreateCall(
        printFunction,
        {builder->CreateGlobalStringPtr(FMT("\nTest results:\n "), "test.msg")});
    builder->CreateCall(
        printFunction,
        {builder->CreateGlobalStringPtr(FMT("%s%%i%s test(s) passed; ", BGRN, RESET), "test.msg"),
         builder->CreateLoad(builder->getInt32Ty(), successCount)});
    builder->CreateCall(
        printFunction,
        {builder->CreateGlobalStringPtr(FMT("%s%%i%s test(s) failed; ", BRED, RESET), "test.msg"),
         builder->CreateLoad(builder->getInt32Ty(), failCount)});
    builder->CreateCall(
        printFunction,
        {builder->CreateGlobalStringPtr(FMT("%s%%i%s test(s) skipped; ", BYEL, RESET), "test.msg"),
         builder->getInt32(skipCount)});
    builder->CreateCall(
        printFunction,
        {builder->CreateGlobalStringPtr(FMT("%s%%i%s test(s) total\n\n", BOLD, RESET), "test.msg"),
         builder->CreateAdd(builder->CreateLoad(builder->getInt32Ty(), successCount),
                            builder->CreateLoad(builder->getInt32Ty(), failCount))});

    builder->CreateBr(end);
    builder->SetInsertPoint(end);
    // TODO: dynamic if tests fail
    builder->CreateRet(builder->getInt32(0));

    // auto DISubprogram = llvmFn->getSubprogram();
    // dbg.builder->finalizeSubprogram(DISubprogram);

    std::string module_error_string;
    llvm::raw_string_ostream module_error_stream(module_error_string);
    llvm::verifyFunction(*mainFunction, &module_error_stream);

    if (!module_error_string.empty()) {
#ifdef _SNOWBALL_BYTECODE_DEBUG
        dump();
#endif
        throw SNError(Error::LLVM_INTERNAL, module_error_string);
    }
}

} // namespace codegen
} // namespace snowball
