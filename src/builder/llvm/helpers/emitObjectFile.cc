
#include "../../../errors.h"
#include "../../../utils/utils.h"
#include "../LLVMBuilder.h"

#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/Host.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Scalar/Reassociate.h>

namespace snowball {
namespace codegen {

int LLVMBuilder::emitObjectFile(std::string out, bool log, bool object) {
    std::error_code EC;
    llvm::raw_fd_ostream dest(out, EC, llvm::sys::fs::OF_None);

    if (EC) { throw SNError(Error::IO_ERROR, FMT("Could not open file: %s", EC.message().c_str())); }

    llvm::legacy::PassManager pass;
    auto FileType = object ? llvm::CGFT_ObjectFile : llvm::CGFT_AssemblyFile;
    if (target->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        remove(out.c_str());
        throw SNError(Error::LLVM_INTERNAL, "TargetMachine can't emit a file of this type");
    }

    if (log) Logger::success("Snowball project compiled to an object file! ✨\n");

    pass.run(*module.get());
    dest.flush();

    return EXIT_SUCCESS;
}

} // namespace codegen
} // namespace snowball
