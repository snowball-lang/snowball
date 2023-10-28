
#include "../../ast/errors/error.h"
#include "../../ast/types/Interface.h"
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

  if (is<types::IntType>(ty)) {
    return dbg.builder->createBasicType(ty->getName(), ty->sizeOf() * 8, llvm::dwarf::DW_ATE_signed);
  } else if (is<types::FloatType>(ty)) {
    return dbg.builder->createBasicType(ty->getName(), ty->sizeOf() * 8, llvm::dwarf::DW_ATE_float);
  } else if (cast<types::VoidType>(ty)) {
    return nullptr;
  } else if (auto x = cast<types::ReferenceType>(ty)) {
    auto type = getDIType(x->getPointedType());
    return dbg.builder->createPointerType(type, ty->sizeOf() * 8);
  } else if (auto x = cast<types::PointerType>(ty)) {
    auto type = getDIType(x->getPointedType());
    return dbg.builder->createPointerType(type, ty->sizeOf() * 8);
  }

  else if (auto f = cast<types::FunctionType>(ty)) {
    std::vector<llvm::Metadata*> argTypes = {getDIType(f->getRetType())};

    for (auto argType : f->getArgs()) { argTypes.push_back(getDIType(argType)); }

    auto subroutineType = dbg.builder->createSubroutineType(llvm::MDTuple::get(*context, argTypes));
    return dbg.builder->createPointerType(subroutineType, ty->sizeOf() * 8);
  } else if (auto c = cast<types::TypeAlias>(ty)) {
    return getDIType(c->getBaseType());
  } else if (auto c = cast<types::BaseType>(ty)) {
    auto asDefinedType = utils::cast<types::DefinedType>(c);
    auto asInterfaceType = utils::cast<types::InterfaceType>(c);

    // TODO: add "VTableHolder" as argument
    auto dbgInfo = c->getDBGInfo();
    auto file = dbg.getFile(dbgInfo->getSourceInfo()->getPath());

    std::vector<llvm::Metadata*> generatedFields;
    llvm::DICompositeType* debugType;
    if (asDefinedType) {
      generatedFields = vector_iterate<types::DefinedType::ClassField*, llvm::Metadata*>(
              asDefinedType->getFields(),
              [&](types::DefinedType::ClassField* t) {
                // TODO: custom line for fields?
                return dbg.builder->createMemberType(
                        nullptr,
                        t->name,
                        file,
                        dbgInfo->line,
                        t->type->sizeOf() * 8,
                        /*AlignInBits=*/0,
                        0,
                        llvm::DINode::FlagZero,
                        getDIType(t->type)
                );
              }
      );
    } else if (asInterfaceType) {
      generatedFields = vector_iterate<types::InterfaceType::Member*, llvm::Metadata*>(
              asInterfaceType->getFields(),
              [&](types::InterfaceType::Member* t) {
                // TODO: custom line for fields?
                return dbg.builder->createMemberType(
                        nullptr,
                        t->name,
                        file,
                        dbgInfo->line,
                        t->type->sizeOf() * 8,
                        /*AlignInBits=*/0,
                        0,
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
      if (auto p = asDefinedType->getParent()) { parentDIType = getDIType(asDefinedType->getParent()); }
    // TODO: create struct type if it's a struct
    debugType = dbg.builder->createClassType(
            file,
            c->getPrettyName(),
            file,
            dbgInfo->line,
            /* TODO: */ 0,
            0,
            0,
            llvm::DINode::FlagZero,
            parentDIType,
            dbg.builder->getOrCreateArray(generatedFields)
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
