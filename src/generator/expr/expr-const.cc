
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
    llvm::Value* Generator::generate_const_value(ConstantValue* p_node) {
        switch (p_node->const_type)
        {
            case TokenType::VALUE_NUMBER: {
                llvm::Type * i64 = get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder);
                snowball_int_t number_value;

                if ((p_node->value.rfind("0x", 0) == 0) || (p_node->value.rfind("0X", 0) == 0)) {
                    number_value = std::stoul(p_node->value, nullptr, 16);
                } else if ((p_node->value.rfind("0b", 0) == 0) || (p_node->value.rfind("0B", 0) == 0)) {
                    number_value = std::stoul(p_node->value.substr(2, (size_t)(p_node->value.size() - 2)), nullptr, 2);
                } else {
                    number_value = std::stoul(p_node->value);
                }

                llvm::Constant * num = llvm::ConstantInt::get(i64, (snowball_int_t)number_value);
                return num;
            }

            case TokenType::VALUE_STRING: {
                std::string str = p_node->value;
                str = str.substr(1, str.size() - 2);
                llvm::Constant* value = _builder->CreateGlobalStringPtr(str.c_str(), ".str");
                return value;
            }

            case TokenType::VALUE_BOOL: {
                llvm::Type * i1 = get_llvm_type_from_sn_type(BuildinTypes::BOOL, _builder);
                return llvm::ConstantInt::get(i1, p_node->value == "true");
            }

            case TokenType::VALUE_FLOAT: {
                llvm::Type * f = get_llvm_type_from_sn_type(BuildinTypes::FLOAT, _builder);
                return llvm::ConstantFP::get(f, std::stof(p_node->value));
            }

            default:
                throw SNError(Error::BUG, Logger::format("Const Value with type %s%i%s%s is not yet supported", BCYN, p_node->const_type, RESET, BOLD));
        }
    }
}