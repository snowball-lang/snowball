
#include <memory>
#include <algorithm>

#include <llvm/IR/IRBuilder.h>

#ifndef __SNOWBALL_BUILDIN_TYPES_H_
#define __SNOWBALL_BUILDIN_TYPES_H_

namespace snowball {

    class Node;
    class FunctionNode;

    class ScopeValue;
    class Enviroment;

    class Type;

    enum BuildinTypes {
        NUMBER,
        STRING,
    };

    class TypeChecker {
        public:

            static bool is_class(ScopeValue* p_value);
            static std::string to_mangle(Type* p_type);
            static std::string to_mangle(std::string p_name, std::vector<Type*> p_generics);
            static llvm::Type* type2llvm(llvm::IRBuilder<> p_builder, llvm::Type* p_type);

            static std::string get_type_name(llvm::Type* p_ty);

            static std::pair<std::vector<Type*>,bool> deduce_template_args(
                FunctionNode* def, std::vector<Type*> params, std::vector<Type*> gparams);

            static std::pair<Type*, int> to_type(std::string p_type);
            static ScopeValue* get_type(Enviroment* p_enviroment, Type* p_type, Node* p_node = nullptr);
            static bool functions_equal(std::string p_name, std::string p_name2, std::vector<Type*> p_args, std::vector<Type*> p_args2, bool p_public, bool p_public2);
    };

    struct Type {
        std::string name;
        std::vector<Type*> generics;

        bool is_array = false;

        std::string to_string() const {
            return name; // TODO: generics or array
        }

        std::string mangle() const {
            return TypeChecker::to_mangle((Type*)this);
        }

        bool equals(Type* p_comp) {
            bool gens_equal;

            if (p_comp->generics.size() == generics.size()) {
                for (int i = 0; i < generics.size(); i++) {
                    gens_equal = generics.at(i)->equals(p_comp->generics.at(i));
                }
            }

            return (gens_equal && (name == p_comp->name));
        }

        Type(std::string p_name)  {
            name = p_name;
        }

        Type(std::string p_name, std::vector<Type*> p_generics)  {
            name = p_name;
            generics = p_generics;
        }
    };

    inline Type* BOOL_TYPE = new Type("Bool");
    inline Type* STRING_TYPE = new Type("String");
    inline Type* NUMBER_TYPE = new Type("Number");

    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, llvm::IRBuilder<> builder);
    llvm::Value* get_alloca(llvm::Module* p_module, llvm::IRBuilder<> p_builder);
}

#endif // __SNOWBALL_BUILDIN_TYPES_H_
