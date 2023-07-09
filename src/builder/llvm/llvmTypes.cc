
#include "../../ast/errors/error.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <memory>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

llvm::Type* LLVMBuilder::getLLVMType(std::shared_ptr<types::Type> t) {
    return getLLVMType(t.get());
}

llvm::Type* LLVMBuilder::getLLVMType(types::Type* t) {
    if (cast<types::Int64Type>(t)) {
        return builder->getInt64Ty();
    } else if (cast<types::Int32Type>(t)) {
        return builder->getInt32Ty();
    } else if (cast<types::Int16Type>(t)) {
        return builder->getInt16Ty();
    } else if (cast<types::Int8Type>(t)) {
        return builder->getInt8Ty();
    } else if (cast<types::CObjectType>(t)) {
        return builder->getInt8PtrTy();
    } else if (cast<types::Float32Type>(t)) {
        return builder->getFloatTy();
    } else if (cast<types::Float64Type>(t)) {
        return builder->getDoubleTy();
    } else if (cast<types::BoolType>(t)) {
        return builder->getInt1Ty();
    } else if (cast<types::VoidType>(t)) {
        return builder->getVoidTy();
    } else if (cast<types::CharType>(t)) {
        return builder->getInt8Ty();
    } else if (auto x = cast<types::ReferenceType>(t)) {
        return getLLVMType(x->getPointedType())->getPointerTo();
    }

    else if (auto f = cast<types::FunctionType>(t)) {
        return getLLVMFunctionType(f)->getPointerTo();
    } else if (auto c = cast<types::DefinedType>(t)) {
        if (auto it = types.find(c->getId()); it != types.end()) { return it->second; }

        auto fields = c->getFields();
        auto generatedFields = vector_iterate<types::DefinedType::ClassField*, llvm::Type*>(
                fields, [&](types::DefinedType::ClassField* t) { return getLLVMType(t->type); });

        auto s = llvm::StructType::create(*context,
                                          (c->isStruct() ? _SN_STRUCT_PREFIX : _SN_CLASS_PREFIX) +
                                                  c->getMangledName());
        types.insert({c->getId(), s});

        if (!c->isStruct()) { // Ignore vtables for structs
            if (auto v = ctx->getVtableTy(c->getId())) {
                generatedFields.insert(generatedFields.begin(), v);
            } else {
                auto structName = (std::string)_SN_VTABLE_PREFIX + c->getMangledName();
                std::vector<llvm::Type*> types;

                for (auto fn : c->getVTable()) { types.push_back(getLLVMType(fn->getType())); }

                auto vtable = llvm::StructType::create(module->getContext(), structName);

                vtable->setBody(types);
                generatedFields.insert(generatedFields.begin(), vtable->getPointerTo());

                ctx->addVtableTy(c->getId(), vtable);
            }
        }

        s->setBody(generatedFields);
        return s;
    } else {
        Syntax::E<BUG>(FMT("Undefined type! ('%s')", t->getName().c_str()));
    }

    return nullptr; // to avoid warnings
}

llvm::FunctionType* LLVMBuilder::getLLVMFunctionType(types::FunctionType* fn) {
    auto argTypes = vector_iterate<std::shared_ptr<types::Type>, llvm::Type*>(
            fn->getArgs(), [&](std::shared_ptr<types::Type> arg) { return getLLVMType(arg); });

    auto ret = getLLVMType(fn->getRetType());
    return llvm::FunctionType::get(ret, argTypes, fn->isVariadic());
}

} // namespace codegen
} // namespace snowball
