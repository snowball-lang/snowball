
#include "../../ast/errors/error.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/DebugInfoMetadata.h>
#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

ptr<llvm::DISubprogram> LLVMBuilder::getDISubprogramForFunc(ptr<ir::Func> x) {
    auto srcInfo = x->getDBGInfo();

    auto file           = dbg.getFile(srcInfo->getSourceInfo()->getPath());
    auto subroutineType = getDIType(x->getType().get());

    std::string baseName = x->getNiceName();

    llvm::DISubprogram *subprogram = dbg.builder->createFunction(
        file, baseName, x->getMangle(), file, srcInfo->line,
        llvm::cast<llvm::DISubroutineType>(subroutineType),
        /*ScopeLine=*/0, llvm::DINode::FlagZero,
        llvm::DISubprogram::toSPFlags(/*IsLocalToUnit=*/true,
                                      /*IsDefinition=*/true,
                                      /*IsOptimized=*/!dbg.debug));
    return subprogram;
}

ptr<llvm::DIType> LLVMBuilder::getDIType(ptr<types::Type> ty) {
    auto llvmType = getLLVMType(ty);

    auto& layout = module->getDataLayout();

    if (cast<types::Int64Type>(ty) || cast<types::Int32Type>(ty) ||
        cast<types::Int16Type>(ty) || cast<types::Int8Type>(ty) ||
        cast<types::BoolType>(ty)) {
        return dbg.builder->createBasicType(
            ty->getName(), layout.getTypeAllocSizeInBits(llvmType),
            llvm::dwarf::DW_ATE_signed);
    } else if (cast<types::CObjectType>(ty)) {
        return dbg.builder->createPointerType(getDIType(new types::Int8Type()),
                                              8);
    } else if (cast<types::StringType>(ty)) {
        return dbg.builder->createStringType(
            ty->getName(), layout.getTypeAllocSizeInBits(llvmType));
    } else if (cast<types::Float32Type>(ty) || cast<types::Float64Type>(ty)) {
        return dbg.builder->createBasicType(
            ty->getName(), layout.getTypeAllocSizeInBits(llvmType),
            llvm::dwarf::DW_ATE_float);
    } else if (cast<types::VoidType>(ty)) {
        return nullptr;
    }

    else if (auto f = cast<types::FunctionType>(ty)) {
        std::vector<ptr<llvm::Metadata>> argTypes = {
            getDIType(f->getRetType().get())};

        for (auto argType : f->getArgs()) {
            argTypes.push_back(getDIType(argType.get()));
        }

        auto subroutineType = dbg.builder->createSubroutineType(
            llvm::MDTuple::get(*context, argTypes));
        return subroutineType;
    } else {
        Syntax::E<BUG>(FMT("Undefined type! ('%s')", ty->getName().c_str()));
    }

    return nullptr; // to avoid warnings
}

} // namespace codegen
} // namespace snowball
