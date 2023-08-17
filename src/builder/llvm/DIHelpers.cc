
#include "../../ast/errors/error.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/BinaryFormat/Dwarf.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

using namespace snowball::utils;

namespace snowball {
namespace codegen {

llvm::DISubprogram* LLVMBuilder::getDISubprogramForFunc(ir::Func* x) {
  const auto& srcInfo = x->getDBGInfo();

  auto file = dbg.getFile(srcInfo->getSourceInfo()->getPath());
  auto derivedType = llvm::cast<llvm::DIDerivedType>(getDIType(x->getType()));
  auto subroutineType = llvm::cast<llvm::DISubroutineType>(derivedType->getRawBaseType());

  std::string baseName = x->getNiceName();

  llvm::DISubprogram* subprogram = dbg.builder->createFunction(file,
                                                               baseName,
                                                               x->getMangle(),
                                                               file,
                                                               srcInfo->line,
                                                               llvm::cast<llvm::DISubroutineType>(subroutineType),
                                                               /*ScopeLine=*/0,
                                                               llvm::DINode::FlagPrototyped,
                                                               llvm::DISubprogram::toSPFlags(
                                                                       /*IsLocalToUnit=*/true,
                                                                       /*IsDefinition=*/true,
                                                                       /*IsOptimized=*/!dbg.debug));
  return subprogram;
}

llvm::DIType* LLVMBuilder::getDIType(types::Type* ty) {
  auto llvmType = getLLVMType(ty);

  auto& layout = module->getDataLayout();

  if (cast<types::Int64Type>(ty) || cast<types::Int32Type>(ty) || cast<types::Int16Type>(ty) ||
      cast<types::Int8Type>(ty) || cast<types::BoolType>(ty) || cast<types::CharType>(ty)) {
    return dbg.builder->createBasicType(
            ty->getName(), layout.getTypeAllocSizeInBits(llvmType), llvm::dwarf::DW_ATE_signed);
  } else if (cast<types::CObjectType>(ty)) {
    return dbg.builder->createPointerType(getDIType(new types::Int8Type()), 8);
  } else if (cast<types::Float32Type>(ty) || cast<types::Float64Type>(ty)) {
    return dbg.builder->createBasicType(
            ty->getName(), layout.getTypeAllocSizeInBits(llvmType), llvm::dwarf::DW_ATE_float);
  } else if (cast<types::VoidType>(ty)) {
    return nullptr;
  } else if (auto x = cast<types::ReferenceType>(ty)) {
    auto type = getDIType(x->getPointedType());
    return dbg.builder->createPointerType(type, layout.getTypeAllocSizeInBits(llvmType));
  }

  else if (auto f = cast<types::FunctionType>(ty)) {
    std::vector<llvm::Metadata*> argTypes = {getDIType(f->getRetType())};

    for (auto argType : f->getArgs()) { argTypes.push_back(getDIType(argType)); }

    auto subroutineType = dbg.builder->createSubroutineType(llvm::MDTuple::get(*context, argTypes));
    return dbg.builder->createPointerType(subroutineType, layout.getTypeAllocSizeInBits(llvmType));
  } else if (auto c = cast<types::TypeAlias>(ty)) {
    return getDIType(c->getBaseType());
  } else if (auto c = cast<types::DefinedType>(ty)) {
    // TODO: add "VTableHolder" as argument
    auto dbgInfo = c->getDBGInfo();
    auto file = dbg.getFile(dbgInfo->getSourceInfo()->getPath());

    auto fields = c->getFields();
    std::vector<llvm::Metadata*> generatedFields;
    llvm::DIType* parentDIType = nullptr;
    if (auto p = c->getParent()) { parentDIType = getDIType(c->getParent()); }
    // TODO: create struct type if it's a struct
    auto debugType = dbg.builder->createClassType(file,
                                                  c->getPrettyName(),
                                                  file,
                                                  dbgInfo->line,
                                                  /* TODO: */ 0,
                                                  0,
                                                  0,
                                                  llvm::DINode::FlagZero,
                                                  parentDIType,
                                                  dbg.builder->getOrCreateArray(generatedFields));

    generatedFields = vector_iterate<types::DefinedType::ClassField*, llvm::Metadata*>(
            fields, [&](types::DefinedType::ClassField* t) {
              // TODO: custom line for fields?
              return dbg.builder->createMemberType(debugType,
                                                   t->name,
                                                   file,
                                                   dbgInfo->line,
                                                   layout.getTypeAllocSizeInBits(getLLVMType(t->type)),
                                                   /*AlignInBits=*/0,
                                                   0,
                                                   llvm::DINode::FlagZero,
                                                   getDIType(t->type));
            });

    return debugType;
  } else {
    Syntax::E<BUG>(FMT("Undefined type! (dbg) ('%s')", ty->getName().c_str()));
  }

  assert(false);
  return nullptr; // to avoid warnings
}

} // namespace codegen
} // namespace snowball
