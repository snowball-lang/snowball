
#include "../../ast/errors/error.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

namespace {
void setDereferenceableAttribute(llvm::Argument& arg, unsigned bytes) {
    auto dereferenceable =
            llvm::Attribute::get(arg.getContext(), llvm::Attribute::Dereferenceable, bytes);
    auto nonull = llvm::Attribute::get(arg.getContext(), llvm::Attribute::NonNull);
    auto noundef = llvm::Attribute::get(arg.getContext(), llvm::Attribute::NoUndef);
    auto aligment = llvm::Attribute::get(arg.getContext(), llvm::Attribute::Alignment, 8);
    arg.addAttr(nonull);
    arg.addAttr(dereferenceable);
    arg.addAttr(noundef);
    arg.addAttr(aligment);
}
} // namespace

llvm::Function* LLVMBuilder::createLLVMFunction(ir::Func* func) {
    auto innerFnType = cast<types::FunctionType>(func->getType().get());
    assert(innerFnType != nullptr);

    auto fnType = llvm::cast<llvm::FunctionType>(getLLVMFunctionType(innerFnType));
    auto name = func->getMangle();
    auto fn = llvm::Function::Create(fnType,
                                     ((func->isStatic() && (!func->hasParent())) ||
                                      func->hasAttribute(Attributes::INTERNAL_LINKAGE))
                                             ? llvm::Function::InternalLinkage
                                             : llvm::Function::ExternalLinkage,
                                     name,
                                     module.get());
    auto& layout = module->getDataLayout();
    for (int i = 0; i < func->getArgs().size(); ++i) {
        auto llvmArg = fn->arg_begin() + i;
        auto arg = utils::at(func->getArgs(), i);
        if (utils::dyn_cast<types::ReferenceType>((arg).second->getType())) {
            setDereferenceableAttribute(*llvmArg, layout.getTypeSizeInBits(llvmArg->getType()));
        }
    }
    auto callee = (llvm::Function*)fn;

    auto attrSet = callee->getAttributes();

    if (func->hasAttribute(Attributes::INLINE)) {
        auto newAttrSet =
                attrSet.addFnAttribute(callee->getContext(), llvm::Attribute::AlwaysInline);
        callee->setAttributes(newAttrSet);
        // TODO: other attributes
    }

    if (!ir::Func::isExternal(func->getMangle()) || func->hasAttribute(Attributes::Fn::NO_MANGLE) 
        || func->getMangle() == "main") {
        auto DISubprogram = getDISubprogramForFunc(func);
        callee->setSubprogram(DISubprogram);
    }

    return callee;
}

} // namespace codegen
} // namespace snowball
