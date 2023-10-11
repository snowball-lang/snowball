
#include "../../ir/values/Call.h"
#include "../../ir/values/Dereference.h"
#include "../../ir/values/Func.h"
#include "../../ir/values/IndexExtract.h"
#include "../../ir/values/ReferenceTo.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define OPERATOR_INSTANCE(x, f)                                                                                        \
  case services::OperatorService::x:                                                                                   \
    this->value = builder->f(load(left, baseType), load(right, baseType));                                             \
    break;
#define OPERATOR_UINSTANCE(x, f)                                                                                       \
  case services::OperatorService::x: this->value = builder->f(load(left, baseType)); break;

namespace snowball {
namespace codegen {

bool LLVMBuilder::buildOperator(ir::Call* call) {
  if (auto fn = utils::dyn_cast<ir::Func>(call->getCallee())) {
    if (!fn->hasAttribute(Attributes::BUILTIN)) return false;
    auto args = call->getArguments();
    auto opName = fn->getName(true);
    if (services::OperatorService::isOperator(opName) &&
        !services::OperatorService::opEquals<services::OperatorService::CONSTRUCTOR>(opName)) {
      auto left = build(args.at(0).get());
      llvm::Value* right = nullptr;
      {
        if (args.size() > 1) {
          ctx->doNotLoadInMemory = false;
          right = build(args.at(1).get());
        }
        if (services::OperatorService::opEquals<services::OperatorService::EQ>(opName)) {
          if (utils::is<ir::DereferenceTo>(args.at(0).get()) && !left->getType()->isPointerTy() &&
              llvm::isa<llvm::LoadInst>(left)) {
            left = builder->CreateLoad(left->getType()->getPointerTo(), ((llvm::LoadInst*) left)->getPointerOperand());
          }
        }
      }
      auto baseType = args.at(0)->getType();
      auto unchangedBaseType = baseType;
      auto realType = baseType;
      if (auto x = utils::cast<types::ReferenceType>(baseType)) {
        baseType = x->getPointedType();
        realType = x->getBaseType();
      }
      if (utils::cast<types::IntType>(realType) || utils::cast<types::CharType>(realType)) {
        switch (services::OperatorService::operatorID(opName)) {
          OPERATOR_INSTANCE(EQEQ, CreateICmpEQ)
          OPERATOR_INSTANCE(PLUS, CreateAdd)
          OPERATOR_INSTANCE(MINUS, CreateSub)
          OPERATOR_INSTANCE(MUL, CreateMul)
          OPERATOR_INSTANCE(DIV, CreateSDiv)
          OPERATOR_INSTANCE(MOD, CreateSRem)
          OPERATOR_INSTANCE(AND, CreateAnd)
          OPERATOR_INSTANCE(OR, CreateOr)
          OPERATOR_INSTANCE(NOTEQ, CreateICmpNE)
          OPERATOR_INSTANCE(BIT_LSHIFT, CreateShl)
          OPERATOR_INSTANCE(BIT_LSHIFT_EQ, CreateShl)
          OPERATOR_INSTANCE(BIT_RSHIFT, CreateAShr)
          OPERATOR_INSTANCE(BIT_RSHIFT_EQ, CreateAShr)
          OPERATOR_INSTANCE(BIT_OR, CreateOr)
          OPERATOR_INSTANCE(BIT_OR_EQ, CreateOr)
          OPERATOR_INSTANCE(BIT_AND, CreateAnd)
          OPERATOR_INSTANCE(BIT_AND_EQ, CreateAnd)
          OPERATOR_INSTANCE(BIT_XOR, CreateXor)
          OPERATOR_INSTANCE(BIT_XOR_EQ, CreateXor)
          OPERATOR_INSTANCE(LT, CreateICmpULT)
          OPERATOR_INSTANCE(GT, CreateICmpSGT)
          OPERATOR_INSTANCE(LTEQ, CreateICmpSLE)
          OPERATOR_INSTANCE(GTEQ, CreateICmpSGE)

          OPERATOR_UINSTANCE(UMINUS, CreateNeg)
          case services::OperatorService::NOT: {
            left = load(left, baseType);
            auto size_in_bits = ((llvm::IntegerType*) left->getType())->getBitWidth();
            if (left->getType()->isPointerTy())
              this->value = builder->CreateICmpEQ(
                      left, llvm::ConstantPointerNull::get(builder->getIntNTy((unsigned) size_in_bits)->getPointerTo())
              );
            else
              this->value = builder->CreateICmpEQ(
                      left, llvm::ConstantInt::get(builder->getIntNTy((unsigned) size_in_bits), 0, false)
              );
            break;
          }

          // TODO: remainder oeprators (!, +=, etc...)
          case services::OperatorService::EQ: {
            ctx->doNotLoadInMemory = false;
            right = load(right, args.at(1)->getType());
            builder->CreateStore(right, left);
            break;
          }

          default: assert(false);
        }

        return true;
      } else if (utils::is<types::FloatType>(realType)) {
        // this->value = builder->Create
        switch (services::OperatorService::operatorID(opName)) {
          OPERATOR_INSTANCE(EQEQ, CreateFCmpUEQ)
          OPERATOR_INSTANCE(PLUS, CreateFAdd)
          OPERATOR_INSTANCE(MINUS, CreateFSub)
          OPERATOR_INSTANCE(MUL, CreateFMul)
          OPERATOR_INSTANCE(DIV, CreateFDiv)
          OPERATOR_INSTANCE(MOD, CreateFRem)
          OPERATOR_INSTANCE(AND, CreateAnd)
          OPERATOR_INSTANCE(OR, CreateOr)
          OPERATOR_INSTANCE(NOTEQ, CreateFCmpUNE)
          OPERATOR_INSTANCE(BIT_LSHIFT, CreateShl)
          OPERATOR_INSTANCE(BIT_LSHIFT_EQ, CreateShl)
          OPERATOR_INSTANCE(BIT_RSHIFT, CreateAShr)
          OPERATOR_INSTANCE(BIT_RSHIFT_EQ, CreateAShr)
          OPERATOR_INSTANCE(BIT_OR, CreateOr)
          OPERATOR_INSTANCE(BIT_OR_EQ, CreateOr)
          OPERATOR_INSTANCE(BIT_AND, CreateAnd)
          OPERATOR_INSTANCE(BIT_AND_EQ, CreateAnd)
          OPERATOR_INSTANCE(BIT_XOR, CreateXor)
          OPERATOR_INSTANCE(BIT_XOR_EQ, CreateXor)
          OPERATOR_INSTANCE(LT, CreateFCmpOLT)
          OPERATOR_INSTANCE(GT, CreateFCmpOGT)
          OPERATOR_INSTANCE(LTEQ, CreateFCmpOLE)
          OPERATOR_INSTANCE(GTEQ, CreateFCmpOGE)

          OPERATOR_UINSTANCE(UMINUS, CreateNeg)
          case services::OperatorService::NOT: {
            this->value =
                    builder->CreateFCmpOEQ(load(left, baseType), llvm::ConstantFP::get(builder->getFloatTy(), 0.0f));
            break;
          }

          // TODO: remainder oeprators (!, +=, etc...)
          case services::OperatorService::EQ: {
            ctx->doNotLoadInMemory = false;
            right = load(right, baseType);
            builder->CreateStore(right, left);
            break;
          }

          default: assert(false);
        }

        return true;
      } else {
        switch (services::OperatorService::operatorID(opName)) {
          case services::OperatorService::EQ: {
            ctx->doNotLoadInMemory = false;
            right = load(right, baseType);
            // TODO: check carefully specific places where we NEED to copy instead of moving
            // if (utils::is<types::PointerType>(args.at(0)->getType())) {
            //  auto a = createAlloca(left->getType(), ".move-temp");
            //  auto align = args.at(0)->getType()->alignmentOf();
            //  builder->CreateLifetimeStart(a, builder->getInt64(args.at(0)->getType()->sizeOf()));
            //  builder->CreateStore(right, a);
            //
            //  builder->CreateMemCpy(left, llvm::MaybeAlign(align), a, llvm::MaybeAlign(align),
            //  builder->getInt64(args.at(0)->getType()->sizeOf()), 0); builder->CreateLifetimeEnd(a,
            //  builder->getInt64(args.at(0)->getType()->sizeOf()));
            //} else {
            builder->CreateStore(right, left);
            //}
            break;
          }

          default: return false;
        }

        return true;
      }
    }
  }

  return false;
}

} // namespace codegen
} // namespace snowball
