
#include "../../ir/values/Call.h"
#include "../../ir/values/Func.h"
#include "../../ir/values/IndexExtract.h"
#include "../../ir/values/ReferenceTo.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define OPERATOR_INSTANCE(x, f)                                                                                        \
  case services::OperatorService::x:                                                                                   \
    this->value = builder->f(left, right);                                                                             \
    break;
#define OPERATOR_UINSTANCE(x, f)                                                                                       \
  case services::OperatorService::x: this->value = builder->f(left); break;

namespace snowball {
namespace codegen {

bool LLVMBuilder::buildOperator(ir::Call* call) {
  if (auto fn = utils::dyn_cast<ir::Func>(call->getCallee())) {
    if (!fn->hasAttribute(Attributes::BUILTIN)) return false;
    auto args = call->getArguments();
    auto opName = fn->getName(true);
    if (services::OperatorService::isOperator(opName) &&
        !services::OperatorService::opEquals<services::OperatorService::CONSTRUCTOR>(opName)) {
      auto leftVal = args.at(0);
      if (auto x = utils::dyn_cast<ir::ReferenceTo>(leftVal)) 
        leftVal = x->getValue();
      auto left = build(leftVal.get());
      llvm::Value* right = nullptr;
      if (args.size() > 1) right = build(args.at(1).get());
      auto baseType = args.at(0)->getType();
      if (llvm::isa<llvm::AllocaInst>(left)) {
        auto l = llvm::cast<llvm::AllocaInst>(left);
        left = builder->CreateLoad(l->getAllocatedType(), l, ".load");
      }
      
      if (auto x = utils::cast<types::ReferenceType>(baseType)) baseType = x->getPointedType();
      if (utils::cast<types::BoolType>(baseType) || utils::cast<types::Int8Type>(baseType) ||
          utils::cast<types::Int16Type>(baseType) || utils::cast<types::Int32Type>(baseType) ||
          utils::cast<types::Int64Type>(baseType) || utils::cast<types::CharType>(baseType) ||
          utils::cast<types::CObjectType>(baseType)) {
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
          OPERATOR_INSTANCE(BIT_RSHIFT, CreateAShr)
          OPERATOR_INSTANCE(BIT_OR, CreateOr)
          OPERATOR_INSTANCE(BIT_AND, CreateAnd)
          OPERATOR_INSTANCE(BIT_XOR, CreateXor)
          OPERATOR_INSTANCE(LT, CreateICmpSLT)
          OPERATOR_INSTANCE(GT, CreateICmpSGT)
          OPERATOR_INSTANCE(LTEQ, CreateICmpSLE)
          OPERATOR_INSTANCE(GTEQ, CreateICmpSGE)

          OPERATOR_UINSTANCE(UMINUS, CreateNeg)
          case services::OperatorService::NOT: {
            auto size_in_bits = ((llvm::IntegerType*)left->getType())->getBitWidth();
            this->value = builder->CreateICmpEQ(
                    left, llvm::ConstantInt::get(builder->getIntNTy((unsigned)size_in_bits), 0, false));
            break;
          }

          // TODO: remainder oeprators (!, +=, etc...)
          case services::OperatorService::EQ: {
            if (auto index = utils::dyn_cast<ir::IndexExtract>(args.at(0))) {
              createInsertValue(right, index->getIndex(), left, baseType);
            } else {
              auto v = left;
              if (llvm::isa<llvm::LoadInst>(v)) {
                auto l = llvm::cast<llvm::LoadInst>(left);
                v = l->getOperand(0);
              }

              builder->CreateStore(right, v);
            }

            break;
          }

          case services::OperatorService::PLUSEQ:
          case services::OperatorService::MOD_EQ:
          case services::OperatorService::MULEQ:
          case services::OperatorService::DIVEQ:
          case services::OperatorService::BIT_LSHIFT_EQ:
          case services::OperatorService::BIT_RSHIFT_EQ:
          case services::OperatorService::BIT_OR_EQ:
          case services::OperatorService::BIT_AND_EQ:
          case services::OperatorService::BIT_XOR_EQ:
          case services::OperatorService::MINUSEQ: {
            auto l = llvm::cast<llvm::LoadInst>(left);
            auto v = l->getOperand(0);
            llvm::Value* op;

            switch (services::OperatorService::operatorID(opName)) {
              case services::OperatorService::MINUSEQ: op = builder->CreateSub(l, right); break;
              case services::OperatorService::PLUSEQ: op = builder->CreateAdd(l, right); break;
              case services::OperatorService::MULEQ: op = builder->CreateMul(l, right); break;
              case services::OperatorService::DIVEQ: op = builder->CreateSDiv(l, right); break;
              case services::OperatorService::MOD_EQ: op = builder->CreateSRem(l, right); break;
              case services::OperatorService::BIT_LSHIFT_EQ: op = builder->CreateShl(l, right); break;
              case services::OperatorService::BIT_RSHIFT_EQ: op = builder->CreateAShr(l, right); break;
              case services::OperatorService::BIT_OR_EQ: op = builder->CreateOr(l, right); break;
              case services::OperatorService::BIT_AND_EQ: op = builder->CreateAnd(l, right); break;
              case services::OperatorService::BIT_XOR_EQ: op = builder->CreateXor(l, right); break;
              default: assert(false);
            }

            builder->CreateStore(op, v);
            this->value = v;
            break;
          }

          default: assert(false);
        }

        return true;
      } else if (utils::cast<types::Float32Type>(baseType) || utils::cast<types::Float64Type>(baseType)) {
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
          OPERATOR_INSTANCE(BIT_RSHIFT, CreateAShr)
          OPERATOR_INSTANCE(BIT_OR, CreateOr)
          OPERATOR_INSTANCE(BIT_AND, CreateAnd)
          OPERATOR_INSTANCE(BIT_XOR, CreateXor)
          OPERATOR_INSTANCE(LT, CreateFCmpOLT)
          OPERATOR_INSTANCE(GT, CreateFCmpOGT)
          OPERATOR_INSTANCE(LTEQ, CreateFCmpOLE)
          OPERATOR_INSTANCE(GTEQ, CreateFCmpOGE)

          OPERATOR_UINSTANCE(UMINUS, CreateNeg)
          case services::OperatorService::NOT: {
            this->value = builder->CreateFCmpOEQ(left, llvm::ConstantFP::get(builder->getFloatTy(), 0.0f));
            break;
          }

          case services::OperatorService::MINUSEQ:
          case services::OperatorService::MOD_EQ:
          case services::OperatorService::MULEQ:
          case services::OperatorService::DIVEQ:
          case services::OperatorService::BIT_LSHIFT_EQ:
          case services::OperatorService::BIT_RSHIFT_EQ:
          case services::OperatorService::BIT_OR_EQ:
          case services::OperatorService::BIT_AND_EQ:
          case services::OperatorService::BIT_XOR_EQ:
          case services::OperatorService::PLUSEQ: {
            auto l = llvm::cast<llvm::LoadInst>(left);
            auto v = l->getOperand(0);
            llvm::Value* op;

            switch (services::OperatorService::operatorID(opName)) {
              case services::OperatorService::MINUSEQ: op = builder->CreateFSub(l, right); break;
              case services::OperatorService::PLUSEQ: op = builder->CreateFAdd(l, right); break;
              case services::OperatorService::MULEQ: op = builder->CreateFMul(l, right); break;
              case services::OperatorService::DIVEQ: op = builder->CreateFDiv(l, right); break;
              case services::OperatorService::MOD_EQ: op = builder->CreateFRem(l, right); break;
              case services::OperatorService::BIT_LSHIFT_EQ: op = builder->CreateShl(l, right); break;
              case services::OperatorService::BIT_RSHIFT_EQ: op = builder->CreateAShr(l, right); break;
              case services::OperatorService::BIT_OR_EQ: op = builder->CreateOr(l, right); break;
              case services::OperatorService::BIT_AND_EQ: op = builder->CreateAnd(l, right); break;
              case services::OperatorService::BIT_XOR_EQ: op = builder->CreateXor(l, right); break;
              default: assert(false);
            }

            builder->CreateStore(op, v);
            this->value = v;
            break;
          }

          // TODO: remainder oeprators (!, +=, etc...)
          case services::OperatorService::EQ: {
            if (auto index = utils::dyn_cast<ir::IndexExtract>(args.at(0))) {
              createInsertValue(right, index->getIndex(), left, baseType);
            } else {
              auto l = llvm::cast<llvm::LoadInst>(left);
              auto v = l->getOperand(0);

              builder->CreateStore(right, v);
            }

            break;
          }

          default: assert(false);
        }

        return true;
      } else {
        switch (services::OperatorService::operatorID(opName)) {
          case services::OperatorService::EQ: {
            llvm::Value* leftValue = left;
            llvm::Value* rightValue = right;
            if (llvm::isa<llvm::LoadInst>(leftValue)) {
              auto l = llvm::cast<llvm::LoadInst>(leftValue);
              leftValue = l->getOperand(0);
            }
            if (auto index = utils::dyn_cast<ir::IndexExtract>(args.at(0))) {
              createInsertValue(rightValue, index->getIndex(), leftValue, baseType);
            } else {
              // builder->CreateMemCpy(rightValue, llvm::MaybeAlign(), leftValue, llvm::MaybeAlign(),
              // module->getDataLayout().getTypeAllocSize(leftValue->getType()), 0);
              if (!utils::cast<types::ReferenceType>(baseType) && !llvm::isa<llvm::LoadInst>(rightValue))
                rightValue = builder->CreateLoad(getLLVMType(baseType), rightValue, ".load");
              builder->CreateStore(rightValue, leftValue);
            }

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
