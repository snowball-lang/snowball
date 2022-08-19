
#include <llvm-10/llvm/IR/DerivedTypes.h>
#include <memory>
#include <vector>
#include <algorithm>

#include <llvm/IR/IRBuilder.h>

#include <sstream>
#include <string.h>

#include "snowball/types.h"
#include "snowball/constants.h"
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

        return {new Type(name, generics), index};
    }

    ScopeValue* TypeChecker::get_type(Enviroment* p_enviroment, Type* p_type, Node* p_node) {
        return p_enviroment->get(to_mangle(p_type), p_node);
    }

    std::string TypeChecker::get_type_name(llvm::Type* p_ty) {

        if (llvm::IntegerType *intType = llvm::dyn_cast<llvm::IntegerType>(p_ty)) {
            unsigned int width = intType->getBitWidth();
            switch (width)
            {
                case 1:
                    return BOOL_TYPE->mangle();

                default:
                    return NUMBER_TYPE->mangle();
            }
        }

        return p_ty->isPointerTy() ?
            p_ty->getPointerElementType()->getStructName() :
            p_ty->getStructName();
    }

    llvm::Type* TypeChecker::type2llvm(llvm::IRBuilder<> p_builder, llvm::Type* p_type) {
        // TODO: bool
        if (get_type_name(p_type) == BOOL_TYPE->mangle()) {
            return get_llvm_type_from_sn_type(BuildinTypes::BOOL, p_builder);
        } else if (p_type->isIntegerTy() || (get_type_name(p_type) == NUMBER_TYPE->mangle())) {
            return get_llvm_type_from_sn_type(BuildinTypes::NUMBER, p_builder);
        }

        return p_type->getPointerTo();
    }

    bool TypeChecker::is_class(ScopeValue* p_value) { return p_value->type == ScopeType::CLASS; }
    bool TypeChecker::functions_equal(
        std::string p_name,
        std::string p_name2,

        std::vector<Type*> p_args,
        std::vector<Type*> p_args2,

        bool p_public,
        bool p_public2) {
            bool args_equal = ((p_args.size() == p_args2.size()) && (p_args.size() == 0));

            if (p_args.size() == p_args2.size()) {
                for (int i = 0; i < p_args.size(); i++) {
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

    llvm::Value* get_alloca(llvm::Module* p_module, llvm::IRBuilder<> p_builder) {
        llvm::FunctionType* function_type = llvm::FunctionType::get(p_builder.getInt8PtrTy(), { p_builder.getInt32Ty() }, false);
        return p_module->getOrInsertFunction("_SNalc", function_type).getCallee();
    }

    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, llvm::IRBuilder<> builder) {

        switch (type)
        {
            #define RETURN_LLVM_TYPE_IF_SN_TYPE_IS(type, llvm_type) case BuildinTypes::type: {return llvm_type; };
                #if _SNOWBALL_ENABLE_INT64
                    RETURN_LLVM_TYPE_IF_SN_TYPE_IS(NUMBER, builder.getInt64Ty())
                #else
                    RETURN_LLVM_TYPE_IF_SN_TYPE_IS(NUMBER, builder.getInt32Ty())
                #endif
                RETURN_LLVM_TYPE_IF_SN_TYPE_IS(STRING, builder.getInt8PtrTy())
                RETURN_LLVM_TYPE_IF_SN_TYPE_IS(BOOL, builder.getInt1Ty())
            #undef RETURN_LLVM_TYPE_IF_SN_TYPE_IS
            default:
                // TODO: throw error
                abort();
        }
    }
}
