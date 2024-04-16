
#include "../../ast/errors/error.h"
#include "../../ast/types/Interface.h"
#include "../../ast/types/EnumType.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"
#include "../../visitors/Transformer.h"
#include "../../../runtime/libs/exceptions.h"
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
  llvm::DISubprogram* subprogram = dbg.builder->createFunction(
                                     file,
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
                                       /*IsOptimized=*/!dbg.debug
                                     )
                                   );
  return subprogram;
}

llvm::DIType* LLVMBuilder::getDIType(types::Type* ty) {
  auto llvmType = getLLVMType(ty);
  auto layout = module->getDataLayout();
  if (auto intTy = cast<types::IntType>(ty)) {
    return dbg.builder->createBasicType(ty->getName(), llvmType->getPrimitiveSizeInBits(),
                                        intTy->isSigned() ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned);
  } else if (is<types::FloatType>(ty)) {
    return dbg.builder->createBasicType(ty->getName(), llvmType->getPrimitiveSizeInBits(), llvm::dwarf::DW_ATE_float);
  } else if (cast<types::VoidType>(ty)) {
    return nullptr;
  } else if (auto x = cast<types::ReferenceType>(ty)) {
    auto type = getDIType(x->getPointedType());
    return dbg.builder->createReferenceType(llvm::dwarf::DW_TAG_reference_type, type, x->sizeOf() * 8);
  } else if (auto x = cast<types::PointerType>(ty)) {
    auto type = getDIType(x->getPointedType());
    return dbg.builder->createPointerType(type, ty->sizeOf() * 8, ty->alignmentOf(), std::nullopt, ty->getPrettyName());
  } else if (auto f = Syntax::Transformer::getFunctionType(ty)) {
    std::vector<llvm::Metadata*> argTypes = {getDIType(f->getRetType())};
    for (auto argType : f->getArgs()) { argTypes.push_back(getDIType(argType)); }
    auto subroutineType = dbg.builder->createSubroutineType(llvm::MDTuple::get(*context, argTypes));
    return dbg.builder->createPointerType(subroutineType, ty->sizeOf());
  } else if (auto c = cast<types::TypeAlias>(ty)) {
    return getDIType(c->getBaseType());
  } else if (auto e = cast<types::EnumType>(ty)) {
    auto dbgInfo = e->getDBGInfo();
    auto file = dbg.getFile(dbgInfo->getSourceInfo()->getPath());
    int enumIndex = 0;
    auto debugType = dbg.builder->createEnumerationType(
                       file,
                       e->getPrettyName(),
                       file,
                       dbgInfo->line,
                       8,
                       ty->alignmentOf(),
                       dbg.builder->getOrCreateArray(vector_iterate<types::EnumType::EnumField, llvm::Metadata*>(
                           e->getFields(),
                           [&](types::EnumType::EnumField t) {
                             return dbg.builder->createEnumerator(t.name, enumIndex++);
                           }
                         )),
                       nullptr
                     );
    return debugType;
  } else if (auto c = cast<types::BaseType>(ty)) {
    auto asDefinedType = utils::cast<types::DefinedType>(c);
    auto asInterfaceType = utils::cast<types::InterfaceType>(c);
    // TODO: add "VTableHolder" as argument
    auto dbgInfo = c->getDBGInfo();
    auto file = dbg.getFile(dbgInfo->getSourceInfo()->getPath());
    std::vector<llvm::Metadata*> generatedFields;
    llvm::DICompositeType* debugType;
    auto structLayout = layout.getStructLayout(llvm::cast<llvm::StructType>(llvmType));
    int fieldIndex = (-1) + c->hasVtable;
    if (asDefinedType) {
      generatedFields = vector_iterate<types::DefinedType::ClassField*, llvm::Metadata*>(
                          asDefinedType->getFields(),
                          [&](types::DefinedType::ClassField * t) {
                            fieldIndex++;
                            return dbg.builder->createMemberType(
                                     nullptr,
                                     t->name,
                                     file,
                                     dbgInfo->line,
                                     layout.getTypeAllocSizeInBits(getLLVMType(t->type)),
                                     0,
                                     fieldIndex < llvmType->getStructNumElements() ?
                                       structLayout->getElementOffsetInBits(fieldIndex) : 0,
                                     llvm::DINode::FlagZero,
                                     getDIType(t->type)
                                   );
                          }
                        );
    } else if (asInterfaceType) {
      generatedFields = vector_iterate<types::InterfaceType::Member*, llvm::Metadata*>(
                          asInterfaceType->getFields(),
                          [&](types::InterfaceType::Member * t) {
                            fieldIndex++;
                            return dbg.builder->createMemberType(
                                     nullptr,
                                     t->name,
                                     file,
                                     dbgInfo->line,
                                     layout.getTypeAllocSizeInBits(getLLVMType(t->type)),
                                     0,
                                     structLayout->getElementOffsetInBits(fieldIndex),
                                     llvm::DINode::FlagZero,
                                     getDIType(t->type)
                                   );
                          }
                        );
    } else {
      Syntax::E<BUG>(FMT("Undefined fields type! (dbg) ('%s')", ty->getName().c_str()));
    }
    llvm::DIType* parentDIType = nullptr;
    if (asDefinedType)
      if (auto p = asDefinedType->getParent()) { parentDIType = getDIType(p); }
    // TODO: create struct type if it's a struct
    debugType = dbg.builder->createStructType(
                  file,
                  c->getPrettyName(),
                  file,
                  dbgInfo->line,
                  c->sizeOf() * 8,
                  0,
                  llvm::DINode::FlagZero,
                  parentDIType,
                  dbg.builder->getOrCreateArray(generatedFields),
                  0,
                  c->hasVtable ?
                  dbg.builder->createPointerType(
                    dbg.builder->createBasicType("void", 8, llvm::dwarf::DW_ATE_signed),
                    8,
                    0
                  ) : nullptr,
                  c->getUUID()
                );
    return debugType;
  } else {
    Syntax::E<BUG>(FMT("Undefined type! (dbg) ('%s')", ty->getName().c_str()));
  }
  assert(false);
  return nullptr; // to avoid warnings
}

} // namespace codegen
} // namespace snowball
