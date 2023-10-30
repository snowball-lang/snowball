
#include "../../ir/values/Call.h"
#include "../../ir/values/Dereference.h"
#include "../../ir/values/Func.h"
#include "../../ir/values/IndexExtract.h"
#include "../../ir/values/ReferenceTo.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define OPERATOR_CALL(f) \
  this->value = builder->f(load(left, baseType), right);
#define U_OPERATOR_CALL(f) \
  this->value = builder->f(load(left, baseType));

#define SIGNED_DEPENDANT(x, s, u) \
  case services::OperatorService::x: \
    if (utils::cast<types::IntType>(realType)->isSigned()) { \
      OPERATOR_CALL(s) \
    } else { \
      OPERATOR_CALL(u) \
    } \
    break;

#define U_SIGNED_DEPENDANT(x, s, u) \
  case services::OperatorService::x: \
    if (utils::cast<types::IntType>(realType)->isSigned()) { \
      U_OPERATOR_CALL(s) \
    } else { \
      U_OPERATOR_CALL(u) \
    } \
    break;

#define OPERATOR_INSTANCE(x, f)                                                                                        \
  case services::OperatorService::x:                                                                                   \
    OPERATOR_CALL(f)                                             \
    break;
#define OPERATOR_UINSTANCE(x, f)                                                                                       \
  case services::OperatorService::x: U_OPERATOR_CALL(f); break;

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
        if (args.size() > 1 && !services::OperatorService::opEquals<services::OperatorService::OR>(opName) && !services::OperatorService::opEquals<services::OperatorService::AND>(opName)) {
          ctx->doNotLoadInMemory = false;
          right = expr(args.at(1).get());
        }
        if (services::OperatorService::opEquals<services::OperatorService::EQ>(opName)) {
          if (utils::is<ir::DereferenceTo>(args.at(0).get()) && !left->getType()->isPointerTy() &&
              llvm::isa<llvm::LoadInst>(left)) {
            left = ((llvm::LoadInst*) left)->getPointerOperand();
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
      if (utils::is<types::IntType>(realType)) {
        switch (services::OperatorService::operatorID(opName)) {
          OPERATOR_INSTANCE(EQEQ, CreateICmpEQ)
          OPERATOR_INSTANCE(PLUS, CreateAdd)
          OPERATOR_INSTANCE(MINUS, CreateSub)
          OPERATOR_INSTANCE(MUL, CreateMul)
          OPERATOR_INSTANCE(DIV, CreateSDiv)
          OPERATOR_INSTANCE(MOD, CreateSRem)
          OPERATOR_INSTANCE(NOTEQ, CreateICmpNE)
          OPERATOR_INSTANCE(BIT_LSHIFT, CreateShl)
          //OPERATOR_INSTANCE(BIT_LSHIFT_EQ, CreateShl)
          OPERATOR_INSTANCE(BIT_RSHIFT, CreateLShr)
          //OPERATOR_INSTANCE(BIT_RSHIFT_EQ, CreateAShr)
          OPERATOR_INSTANCE(BIT_OR, CreateOr)
          //OPERATOR_INSTANCE(BIT_OR_EQ, CreateOr)
          OPERATOR_INSTANCE(BIT_AND, CreateAnd)
          //OPERATOR_INSTANCE(BIT_AND_EQ, CreateAnd)
          OPERATOR_INSTANCE(BIT_XOR, CreateXor)
          //OPERATOR_INSTANCE(BIT_XOR_EQ, CreateXor)

          SIGNED_DEPENDANT(LT, CreateICmpSLT, CreateICmpULT)
          SIGNED_DEPENDANT(GT, CreateICmpSGT, CreateICmpUGT)
          SIGNED_DEPENDANT(LTEQ, CreateICmpSLE, CreateICmpULE)
          SIGNED_DEPENDANT(GTEQ, CreateICmpSGE, CreateICmpUGE)

          U_SIGNED_DEPENDANT(UMINUS, CreateNSWNeg, CreateNUWNeg)

          case services::OperatorService::AND: {
            left = toBool(load(left, baseType), utils::cast<types::IntType>(realType)->isSigned());
            auto currentBlock = builder->GetInsertBlock();
            auto trueBlock = h.create<llvm::BasicBlock>(*context, "and.true", ctx->getCurrentFunction());
            auto continueBlock = h.create<llvm::BasicBlock>(*context, "and.cont", ctx->getCurrentFunction());

            builder->CreateCondBr(left, trueBlock, continueBlock);
            builder->SetInsertPoint(trueBlock);
            right = toBool(expr(args.at(1).get()), utils::cast<types::IntType>(realType)->isSigned());
            auto trueNode = builder->GetInsertBlock();
            auto cmp = builder->CreateICmpNE(right, llvm::ConstantInt::get(right->getType(), 0, utils::cast<types::IntType>(realType)->isSigned()));
            builder->CreateBr(continueBlock);
            builder->SetInsertPoint(continueBlock);
            auto phi = builder->CreatePHI(builder->getInt1Ty(), 2);
            phi->addIncoming(builder->getFalse(), currentBlock);
            phi->addIncoming(cmp, trueNode);
            this->value = phi;
            break;
          }

          case services::OperatorService::OR: {
            left = toBool(load(left, baseType), utils::cast<types::IntType>(realType)->isSigned());
            auto currentBlock = builder->GetInsertBlock();
            auto trueBlock = h.create<llvm::BasicBlock>(*context, "or.true", ctx->getCurrentFunction());
            auto continueBlock = h.create<llvm::BasicBlock>(*context, "or.cont", ctx->getCurrentFunction());

            builder->CreateCondBr(left, continueBlock, trueBlock);
            builder->SetInsertPoint(trueBlock);
            right = toBool(expr(args.at(1).get()), utils::cast<types::IntType>(realType)->isSigned());
            auto trueNode = builder->GetInsertBlock();
            auto cmp = builder->CreateICmpNE(right, llvm::ConstantInt::get(right->getType(), 0, utils::cast<types::IntType>(realType)->isSigned()));
            builder->CreateBr(continueBlock);
            builder->SetInsertPoint(continueBlock);
            auto phi = builder->CreatePHI(builder->getInt1Ty(), 2);
            phi->addIncoming(builder->getTrue(), currentBlock);
            phi->addIncoming(cmp, trueNode);
            this->value = phi;
            break;
          }

          case services::OperatorService::NOT: {
            left = toBool(load(left, baseType));
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
          OPERATOR_INSTANCE(NOTEQ, CreateFCmpUNE)
          OPERATOR_INSTANCE(BIT_LSHIFT, CreateShl)
          //OPERATOR_INSTANCE(BIT_LSHIFT_EQ, CreateShl)
          OPERATOR_INSTANCE(BIT_RSHIFT, CreateLShr)
          //OPERATOR_INSTANCE(BIT_RSHIFT_EQ, CreateAShr)
          OPERATOR_INSTANCE(BIT_OR, CreateOr)
          //OPERATOR_INSTANCE(BIT_OR_EQ, CreateOr)
          OPERATOR_INSTANCE(BIT_AND, CreateAnd)
          //OPERATOR_INSTANCE(BIT_AND_EQ, CreateAnd)
          OPERATOR_INSTANCE(BIT_XOR, CreateXor)
          //OPERATOR_INSTANCE(BIT_XOR_EQ, CreateXor)
          OPERATOR_INSTANCE(LT, CreateFCmpOLT)
          OPERATOR_INSTANCE(GT, CreateFCmpOGT)
          OPERATOR_INSTANCE(LTEQ, CreateFCmpOLE)
          OPERATOR_INSTANCE(GTEQ, CreateFCmpOGE)

          case services::OperatorService::AND: {
            left = toBool(load(left, baseType));
            auto currentBlock = builder->GetInsertBlock();
            auto trueBlock = h.create<llvm::BasicBlock>(*context, "and.true", ctx->getCurrentFunction());
            auto continueBlock = h.create<llvm::BasicBlock>(*context, "and.cont", ctx->getCurrentFunction());

            builder->CreateCondBr(left, trueBlock, continueBlock);
            builder->SetInsertPoint(trueBlock);
            right = toBool(expr(args.at(1).get()));
            auto trueNode = builder->GetInsertBlock();
            auto cmp = builder->CreateFCmpUNE(right, llvm::ConstantFP::get(right->getType(), 0));
            builder->CreateBr(continueBlock);
            builder->SetInsertPoint(continueBlock);
            auto phi = builder->CreatePHI(builder->getInt1Ty(), 2);
            phi->addIncoming(builder->getFalse(), currentBlock);
            phi->addIncoming(cmp, trueNode);
            this->value = phi;
            break;
          }

          case services::OperatorService::OR: {
            left = toBool(load(left, baseType));
            auto currentBlock = builder->GetInsertBlock();
            auto trueBlock = h.create<llvm::BasicBlock>(*context, "or.true", ctx->getCurrentFunction());
            auto continueBlock = h.create<llvm::BasicBlock>(*context, "or.cont", ctx->getCurrentFunction());

            builder->CreateCondBr(left, continueBlock, trueBlock);
            builder->SetInsertPoint(trueBlock);
            right = toBool(expr(args.at(1).get()));
            auto trueNode = builder->GetInsertBlock();
            auto cmp = builder->CreateFCmpUNE(right, llvm::ConstantFP::get(right->getType(), 0));
            builder->CreateBr(continueBlock);
            builder->SetInsertPoint(continueBlock);
            auto phi = builder->CreatePHI(builder->getInt1Ty(), 2);
            phi->addIncoming(builder->getTrue(), currentBlock);
            phi->addIncoming(cmp, trueNode);
            this->value = phi;
            break;
          }

          OPERATOR_UINSTANCE(UMINUS, CreateFNeg)
          case services::OperatorService::NOT: {
            this->value =
                    builder->CreateFCmpOEQ(load(left, baseType), llvm::ConstantFP::get(builder->getFloatTy(), 0.0f));
            break;
          }

          // TODO: remainder oeprators (!, +=, etc...)
          case services::OperatorService::EQ: {
            builder->CreateStore(right, left);
            break;
          }

          default: assert(false);
        }

        return true;
      } else {
        switch (services::OperatorService::operatorID(opName)) {
          case services::OperatorService::EQ: {
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
