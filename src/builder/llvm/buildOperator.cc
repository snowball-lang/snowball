
#include "../../ir/values/Call.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#define OPERATOR_INSTANCE(x, f)                                                \
    case services::OperatorService::x:                                         \
        this->value = builder->f(left, right);                                 \
        break;

namespace snowball {
namespace codegen {

bool LLVMBuilder::buildOperator(ir::Call *call) {
    if (auto fn = utils::dyn_cast<ir::Func>(call->getCallee())) {
        auto args   = call->getArguments();
        auto opName = fn->getName(true);
        if (utils::startsWith(opName, "#") && args.size() == 2) {
            auto left  = build(args.at(0).get());
            auto right = build(args.at(1).get());
            if (utils::dyn_cast<types::Int8Type>(args.at(0)->getType()) ||
                utils::dyn_cast<types::Int16Type>(args.at(0)->getType()) ||
                utils::dyn_cast<types::Int32Type>(args.at(0)->getType()) ||
                utils::dyn_cast<types::Int64Type>(args.at(0)->getType()) ||
                utils::dyn_cast<types::CharType>(args.at(0)->getType())) {
                // this->value = builder->Create
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
                    OPERATOR_INSTANCE(LT, CreateICmpSLT)
                    OPERATOR_INSTANCE(GT, CreateICmpSGT)
                    OPERATOR_INSTANCE(LTEQ, CreateICmpSLE)
                    OPERATOR_INSTANCE(GTEQ, CreateICmpSGE)

                    // TODO: remainder oeprators (!, +=, etc...)
                    case services::OperatorService::EQ: {
                        auto l = llvm::cast<llvm::LoadInst>(left);
                        auto v = l->getOperand(0);

                        builder->CreateStore(right, v);
                        break;
                    }

                    default:
                        assert(false);
                }

                return true;

            } else if (utils::dyn_cast<types::Float32Type>(
                           args.at(0)->getType()) ||
                       utils::dyn_cast<types::Float64Type>(
                           args.at(0)->getType())) {
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

                    // TODO: remainder oeprators (!, +=, etc...)
                    case services::OperatorService::EQ: {
                        auto l = llvm::cast<llvm::LoadInst>(left);
                        auto v = l->getOperand(0);

                        builder->CreateStore(right, v);
                        break;
                    }

                    default:
                        assert(false);
                }

                return true;

            } else {
                assert(false && "Unhandled operator!");
            }
        }
    }

    return false;
}

} // namespace codegen
} // namespace snowball
