
#include "../../ir/values/Call.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

bool LLVMBuilder::buildOperator(std::shared_ptr<ir::Call> call) {
    if (auto fn = utils::dyn_cast<ir::Func>(call->getCallee())) {
        auto args = call->getArguments();
        if (utils::startsWith(fn->getName(), "#") && args.size() == 2) {
            auto left  = build(args.at(0).get());
            auto right = build(args.at(1).get());
            if (utils::dyn_cast<types::Int8Type>(args.at(0)) ||
                utils::dyn_cast<types::Int16Type>(args.at(0)) ||
                utils::dyn_cast<types::Int32Type>(args.at(0)) ||
                utils::dyn_cast<types::Int64Type>(args.at(0)) ||
                utils::dyn_cast<types::CharType>(args.at(0))) {
                // this->value = builder->Create
                switch (services::OperatorService::operatorID(fn->getName())) {
#define OPERATOR_INSTANCE(x, f)                                                \
    case services::OperatorService::x:                                         \
        builder->f(left, right);                                               \
        break;
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
                    // TODO: remainder oeprators (!, +=, etc...)
#undef OPERATOR_INSTANCE
                    case services::OperatorService::EQ:
                    default:
                        assert(false);
                }
            } else {
                assert(false && "Unhandled operator!");
            }
        }
    }

    return false;
}

} // namespace codegen
} // namespace snowball
