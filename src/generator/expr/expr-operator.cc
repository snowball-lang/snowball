
#include "snowball/libs.h"

#include "snowball/types.h"
#include "snowball/nodes.h"
#include "snowball/token.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"
#include "snowball/operators.h"

#include <cstdio>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

#include <memory>
#include <pthread.h>
#include <sstream>
#include <optional>
#include <fstream>

#include <dlfcn.h>

namespace snowball {
    llvm::Value* Generator::generate_operator(BinaryOp* p_node) {
        #define FNAME(opty) GET_FUNCTION_FROM_CLASS(\
            (ADD_MODULE_NAME_IF_EXISTS(".") TypeChecker::get_type_name(left_type)).c_str(), \
                (((std::string)"#") + op2str(opty)).c_str(), { \
                    TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first, \
                    TypeChecker::to_type(TypeChecker::get_type_name(right_type)).first \
                }, true)
        #define FNAME_NO_MANGLE(opty) GET_FUNCTION_FROM_CLASS_NO_MANGLE( \
            (ADD_MODULE_NAME_IF_EXISTS(".") TypeChecker::get_type_name(left_type)), \
                (((std::string)"#") + op2str(opty)))

        llvm::Value* left = generate(p_node->left);

        if (p_node->unary) {
            llvm::Type* left_type = left->getType()->isPointerTy() ? left->getType()->getPointerElementType() : left->getType();

            llvm::Function* function;
            switch (p_node->op_type)
            {
                case BinaryOp::OpType::OP_NOT: {
                    if (TypeChecker::is_bool(left_type) || TypeChecker::is_number(left_type)) {
                        return _builder->CreateNot(left);
                    }

                    CALL_UNARY_OPERATOR(OperatorType::NOT)
                    break;
                }

                default: {
                    COMPILER_ERROR(BUG, Logger::format("The unary operator with type '%i' has not been handled.", p_node->op_type))
                }
            }

            return _builder->CreateCall(function,
                {left});
        } else {
            llvm::Value* right = generate(p_node->right);

            // get names with type checker
            llvm::Type* left_type = left->getType()->isPointerTy() ? left->getType()->getPointerElementType() : left->getType();
            llvm::Type* right_type = right->getType()->isPointerTy() ? right->getType()->getPointerElementType() : right->getType();

            llvm::Function* function;
            switch (p_node->op_type)
            {
                case BinaryOp::OpType::OP_PLUS: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFAdd(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateAdd(left, new_right);
                    }

                    CALL_OPERATOR(OperatorType::PLUS)
                    break;
                }

                case BinaryOp::OpType::OP_EQEQ: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFCmpOEQ(left, new_right);
                    } else if (TypeChecker::both_number(left_type, new_right_type, true)) {
                        return _builder->CreateICmpEQ(left, new_right);
                    }

                    CALL_OPERATOR(OperatorType::EQEQ)
                    break;
                }

                case BinaryOp::OpType::OP_NOTEQ: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFCmpONE(left, new_right);
                    } else if (TypeChecker::both_number(left_type, new_right_type, true)) {
                        return _builder->CreateICmpNE(left, new_right);
                    }

                    CALL_OPERATOR(OperatorType::NOTEQ)
                    break;
                }

                case BinaryOp::OpType::OP_EQ: {
                    auto [new_right, succ] = TypeChecker::implicit_cast(_builder, left_type, right);
                    if (!succ) {
                        COMPILER_ERROR(TYPE_ERROR, Logger::format("can't store new value (%s) to '%s'", "TODO", "TODO"))
                    }

                    // TODO: make this work
                    return _builder->CreateStore(right, left);

                    // TODO: call operator "eq" if exists
                    break;
                }

                case BinaryOp::OpType::OP_LTEQ: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFCmpOLE(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateICmpULE(left, new_right);
                    }

                    CALL_OPERATOR(OperatorType::LTEQ)
                    break;
                }

                case BinaryOp::OpType::OP_MINUS: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFSub(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateSub(left, new_right);
                    }


                    CALL_OPERATOR(OperatorType::MINUS)
                    break;
                }

                case BinaryOp::OpType::OP_MUL: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFMul(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateMul(left, new_right);
                    }

                    CALL_OPERATOR(OperatorType::MUL)
                    break;
                }

                case BinaryOp::OpType::OP_DIV: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFDiv(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateSDiv(left, new_right);
                    }


                    CALL_OPERATOR(OperatorType::DIV)
                    break;
                }

                case BinaryOp::OpType::OP_GT: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFCmpOGT(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateICmpSGT(left, new_right);
                    }


                    CALL_OPERATOR(OperatorType::GT)
                    break;
                }

                default: {
                    COMPILER_ERROR(BUG, Logger::format("The operator with type '%i' has not been handled.", p_node->op_type))
                }
            }

            return _builder->CreateCall(function,
                {left, right});

            #undef FNAME
            #undef FNAME_NO_MANGLE

        }
    }
}