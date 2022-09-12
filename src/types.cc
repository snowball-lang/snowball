
#include <llvm/IR/DerivedTypes.h>
#include <memory>
#include <vector>
#include <algorithm>

#include <llvm/IR/IRBuilder.h>

#include <sstream>
#include <string.h>

#include "snowball/types.h"
#include "snowball/constants.h"
#include "snowball/errors.h"
#include "snowball/logger.h"
#include "snowball/enviroment.h"
#include "snowball/utils/mangle.h"
#include "snowball/utils/utils.h"

namespace snowball {
    std::string TypeChecker::to_mangle(Type* p_type) {
        return to_mangle(p_type->name, p_type->generics);
    }

    std::string TypeChecker::to_mangle(std::string p_name, std::vector<Type*> p_generics) {
        std::stringstream result;
        result << "@";
        result << p_name.size();
        result << p_name;

        if (p_generics.size() > 0) {
            result << "[";

            for (Type* generic : p_generics) {
                result << to_mangle(generic);
            }

            result << "]";
        }

        return result.str();
    }

    std::pair<Type*, int> TypeChecker::to_type(std::string p_type) {
        ASSERT(p_type.at(0) == '@')

        std::string name;
        std::vector<Type*> generics;

        int index = 1;

        std::stringstream _length;
        _length << p_type[index];
        index++;

        while (p_type[index] >= '0' && p_type[index] <= '9') {
            _length << (p_type[index]);
            index++;
        }

        int length = std::stoi(_length.str());
        name = p_type.substr(index, length);

        index += length;

        if (p_type[index+1] == '[') {
            index++;

            while (p_type[index] == '@') {
                auto [type, next_index] = to_type(p_type.substr(index, p_type.length()-1));
                index += next_index;
                generics.push_back(type);
            }

            // ASSERT(p_type[index] == ']')
            index++;
        }

        // Int should actually be i32
        // TODO: check if there is a better way to do this
        if (name == "Int") name = "i32";

        return {new Type(name, generics), index};
    }

    ScopeValue* TypeChecker::get_type(Enviroment* p_environment, Type* p_type, Node* p_node) {
        return p_enviroment->get(to_mangle(p_type), p_node);
    }

    bool TypeChecker::both_number(llvm::Type* p_left, llvm::Type* p_right, bool p_allow_bools) {
        return (is_number(p_left) || (is_bool(p_left) && p_allow_bools)) &&
              (is_number(p_right) || (is_bool(p_right) && p_allow_bools));
    }

    bool TypeChecker::is_float(llvm::Type* p_type) {
        return p_type->isFloatTy() || p_type->isDoubleTy();
    }

    bool TypeChecker::has_less_width(llvm::IntegerType* p_src, llvm::IntegerType* p_comp) {
        return p_src->getBitWidth() < p_comp->getBitWidth();
    }

    // NOTE: the function returns false if types contain integer types
    //       checkout TypeChecker::both_number as an alternative to this
    //       function for integer types.
    bool TypeChecker::is_castable(llvm::Type* p_left, llvm::Type* p_right) {
        // TODO: check for inheritance of classes
        return false;
    }

    std::pair<llvm::Value*, bool> TypeChecker::implicit_cast(std::shared_ptr<llvm::IRBuilder<>> p_builder, llvm::Type* p_left, llvm::Value* p_right) {

        // TODO: if left or right is float, convert the other side to float.
        llvm::Type* right_type = p_right->getType();

        if (right_type == p_left) return {p_right, true};

        if (is_float(p_left) && is_number(right_type)) {
            return {p_builder->CreateSIToFP(p_right, p_left), true};
        } if (p_left->isDoubleTy() && right_type->isFloatTy()) {
            return {p_builder->CreateFPCast(p_right, p_left), true};
        } if (p_left->isFloatTy() && right_type->isDoubleTy()) {
            return {p_builder->CreateFPTrunc(p_right, p_left), true};
        } else if (is_number(p_left) && is_float(right_type)) {
            return {p_builder->CreateFPToSI(p_right, p_left), true};
        } else if (both_number(p_left, right_type, true)) {

            if (has_less_width(llvm::dyn_cast<llvm::IntegerType>(right_type), llvm::dyn_cast<llvm::IntegerType>(p_left))) {
                return {p_builder->CreateTrunc(p_right, p_left), true};
            }

            return {p_builder->CreateIntCast(p_right, p_left, true), true};
        } else if (is_castable(p_left, right_type)) {
            throw SNError(Error::TODO, "Bit casts for non-integer types are not allowed!");
        }

        return {p_right, false};
    }

    bool TypeChecker::is_bool(llvm::Type* p_type) {
        if (llvm::IntegerType *intType = llvm::dyn_cast<llvm::IntegerType>(p_type)) {
            return intType->getBitWidth() == 1;
        }

        // Int is supposed to represent as i32
        return get_type_name(p_type) == BOOL_TYPE->mangle();
    }

    bool TypeChecker::is_number(llvm::Type* p_type) {
        if (llvm::IntegerType *intType = llvm::dyn_cast<llvm::IntegerType>(p_type->isPointerTy() ? p_type->getPointerElementType() : p_type)) {
            return (intType->getBitWidth() != 1) && (intType->getBitWidth() != 8);
        }

        // Int is supposed to represent as i32
        return get_type_name(p_type) == INT32_TYPE->mangle();
    }

    std::string TypeChecker::get_type_name(llvm::Type* p_ty) {

        llvm::Type* base_type = p_ty->isPointerTy() ?
            p_ty->getPointerElementType() : p_ty;

        if (base_type->isVoidTy()) {
            return VOID_TYPE->mangle();
        } else if (llvm::IntegerType *intType = llvm::dyn_cast_or_null<llvm::IntegerType>(base_type)) {
            unsigned int width = intType->getBitWidth();
            switch (width)
            {
                case 1:
                    return BOOL_TYPE->mangle();

                case 8:
                    return STRING_TYPE->mangle();

                case 16:
                    return INT16_TYPE->mangle();

                case 64:
                    return INT64_TYPE->mangle();

                case 32:
                default:
                    return INT32_TYPE->mangle();
            }
        } else if (base_type->isFloatTy()) {
            return FLOAT32_TYPE->mangle();
        } else if (base_type->isDoubleTy()) {
            return FLOAT64_TYPE->mangle();
        } else if (base_type->isStructTy()) {
            return base_type->getStructName().str();
        }

        throw SNError(Error::BUG, Logger::format("Type with ID %i could not be decided!", base_type->getTypeID()));
    }

    llvm::Type* TypeChecker::type2llvm(std::shared_ptr<llvm::IRBuilder<>> p_builder, llvm::Type* p_type) {
        if (get_type_name(p_type) == BOOL_TYPE->mangle()) {
            return get_llvm_type_from_sn_type(BuildinTypes::BOOL, std::move(p_builder));
        } else if (get_type_name(p_type) == NUMBER_TYPE->mangle()) {
            return get_llvm_type_from_sn_type(BuildinTypes::NUMBER, std::move(p_builder));
        } else if (get_type_name(p_type) == FLOAT32_TYPE->mangle()) {
            return p_builder->getFloatTy();
        } else if (get_type_name(p_type) == FLOAT64_TYPE->mangle()) {
            return p_builder->getDoubleTy();
        } else if (get_type_name(p_type) == INT16_TYPE->mangle()) {
            return p_builder->getInt16Ty();
        } else if (get_type_name(p_type) == STRING_TYPE->mangle()) {
            return p_builder->getInt8PtrTy();
        } else if (get_type_name(p_type) == VOID_TYPE->mangle()) {
            return p_builder->getVoidTy();
        } else if (get_type_name(p_type) == INT32_TYPE->mangle()) {
            return p_builder->getInt32Ty();
        } else if (get_type_name(p_type) == INT64_TYPE->mangle()) {
            return p_builder->getInt64Ty();
        } else if (is_number(p_type)) {
            return p_type;
        }

        return p_type->isPointerTy() ? p_type : p_type->getPointerTo();
    }

    bool TypeChecker::is_class(ScopeValue* p_value) { return p_value->type == ScopeType::CLASS; }
    bool TypeChecker::functions_equal(
        std::string p_name,
        std::string p_name2,

        std::vector<Type*> p_args,
        std::vector<Type*> p_args2,

        bool p_public,
        bool p_public2,

        bool has_varg) {

            // check if both functions have 0 arguments or if the function call has less
            // arguments than the declaration
            bool args_equal = ((p_args.size() == p_args2.size()) && (p_args.size() == 0));

            // Iterate each argument and check if they match types.
            // We only iterate only if the function call has the same
            // number of arguments or more (because the variadic arguments).
            if ((p_args.size() >= p_args2.size() && has_varg) || p_args.size() <= p_args2.size()) {
                for (int i = 0; i < p_args.size(); i++) {

                    // Check if the function has variadic arguments
                    if ((i == p_args2.size()) && has_varg) {
                        break;
                    }

                    args_equal = p_args.at(i)->equals(p_args2.at(i));
                }
            }

            return (args_equal && (p_name == p_name2) && (p_public == p_public2));
    }

    std::pair<std::vector<Type*>,bool> TypeChecker::deduce_template_args(
                FunctionNode* def, std::vector<Type*> params, std::vector<Type*> gparams) {
        std::vector<Type*> deduced_types;
        int garg_idx = 0; // The first given generic argument of the func call expr
        for (int i = 0; i < def->generics.size(); i++)
        {
            auto garg = def->generics[i];
            // We have a generic type parameter garg
            // 1. Look up the idx where the generic type is used in the args
            // 2. Look up the type of the arg at the idx in the function call expr.
            // 3. The type of the arg in the function call expr is the deduced type

            // -> 1.
            auto it = std::find_if(def->generics.begin(), def->generics.end(), [&](Type* arg) {
                return arg->equals(garg);
                });

            // -> 2.
            if (it != def->generics.end())
            {
                int arg_idx = std::distance(def->generics.begin(), it);
                auto deduced_type = params[arg_idx];
                // -> 3.
                deduced_types.push_back(deduced_type);
            }

            // Generic Type was not found in arg list
            // See if it was given
            else if (garg_idx < gparams.size())
            {
                auto type_spec = gparams[garg_idx];
                deduced_types.push_back(type_spec);
            }

            // TODO:
            // else if (garg->default_type != nullptr)
            // {
            //     auto type_spec = garg->default_type;
            //     deduced_types.push_back(type_spec);
            // }

            else
            {
                return { {},false };
            }
        }
        return { deduced_types,true };
    }

    llvm::Function* get_alloca(llvm::Module* p_module, std::shared_ptr<llvm::IRBuilder<>> p_builder) {
        llvm::FunctionType* function_type = llvm::FunctionType::get(p_builder->getInt8PtrTy(), { p_builder->getInt32Ty() }, false);
        return (llvm::Function*)p_module->getOrInsertFunction("_SNalc", function_type).getCallee();
    }

    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, std::shared_ptr<llvm::IRBuilder<>> builder) {

        switch (type)
        {
            #define RETURN_LLVM_TYPE_IF_SN_TYPE_IS(type, llvm_type) case BuildinTypes::type: {return llvm_type; };
                #if _SNOWBALL_ENABLE_INT64
                    RETURN_LLVM_TYPE_IF_SN_TYPE_IS(NUMBER, builder->getInt64Ty())
                #else
                    RETURN_LLVM_TYPE_IF_SN_TYPE_IS(NUMBER, builder->getInt32Ty())
                #endif
                RETURN_LLVM_TYPE_IF_SN_TYPE_IS(FLOAT, builder->getFloatTy())
                RETURN_LLVM_TYPE_IF_SN_TYPE_IS(DOUBLE, builder->getDoubleTy())
                RETURN_LLVM_TYPE_IF_SN_TYPE_IS(STRING, builder->getInt8PtrTy())
                RETURN_LLVM_TYPE_IF_SN_TYPE_IS(BOOL, builder->getInt1Ty())
            #undef RETURN_LLVM_TYPE_IF_SN_TYPE_IS
            default:
                // TODO: throw error
                abort();
        }
    }
}
