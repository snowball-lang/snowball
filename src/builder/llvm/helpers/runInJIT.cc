#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/TargetSelect.h>
#include <memory>

#include "../LLVMBuilder.h"

namespace snowball {
namespace codegen {
using namespace Syntax;

void LLVMBuilder::runInJit() {
    auto exec_engn = llvm::EngineBuilder(std::move(module)).setErrorStr(nullptr).create();

    if (!exec_engn) {
        E<LLVM_INTERNAL>("failed to create the exec engine");
    }

    auto main_fn = exec_engn->FindFunctionNamed("main");
    exec_engn->runFunction(main_fn, {});

    delete exec_engn;
}

}
}