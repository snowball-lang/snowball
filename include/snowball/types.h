
#include <memory>
#include <algorithm>

#include <map>

#include "constants.h"
#include <llvm/IR/IRBuilder.h>

#ifndef __SNOWBALL_BUILDIN_TYPES_H_
#define __SNOWBALL_BUILDIN_TYPES_H_

namespace snowball {

    class Node;
    class FunctionNode;
    class ArgumentNode;

    class ScopeValue;
    class Enviroment;

    class Type;

    enum class BuildinTypes {
        BOOL,
        NUMBER,
        FLOAT,
        DOUBLE,
        STRING,
        VOID,
        // TODO: i32, i64, i16
    };

    class TypeChecker {
        public:


            static bool has_less_width(llvm::IntegerType* p_src, llvm::IntegerType* p_comp);
            static std::pair<llvm::Value*, bool> implicit_cast(std::shared_ptr<llvm::IRBuilder<>> p_builder, llvm::Type* p_left, llvm::Value* p_right);

            static std::string to_mangle(Type* p_type);
            static std::string to_mangle(std::string p_name, std::vector<Type*> p_generics = {});

            static llvm::Type* type2llvm(std::shared_ptr<llvm::IRBuilder<>> p_builder, llvm::Type* p_type);
            static Type* llvm2type(llvm::Type* p_type);

            static bool is_castable(llvm::Type* p_left, llvm::Type* p_right);
            static bool is_castable(      Type* p_left,       Type* p_right);

            static bool is_float(llvm::Type* p_type);
            static bool is_float(      Type* p_type);

            static bool both_number(llvm::Type* p_left, llvm::Type* p_right, bool p_allow_bools = false);
            static bool both_number(      Type* p_left,       Type* p_right, bool p_allow_bools = false);

            static bool is_number(llvm::Type* p_type);
            static bool is_number(      Type* p_type);

            static bool is_bool(llvm::Type* p_type);
            static bool is_bool(      Type* p_type);

            static bool is_class(ScopeValue* p_value);

            static std::vector<Type*> args2types(std::vector<ArgumentNode*> p_args);
            static std::string get_type_name(llvm::Type* p_ty);

            static std::string string_mangle(std::string p_type);

            static std::tuple<std::map<std::string, Type*>,std::vector<Type*>,bool> deduce_template_args(
                FunctionNode* def, std::vector<Type*> params, std::vector<Type*> gparams);

            static std::string args_to_string(std::vector<Type*> p_args);
            static std::pair<Type*, int> to_type(std::string p_type);
            static ScopeValue* get_type(Enviroment* p_enviroment, Type* p_type, Node* p_node = nullptr, std::string p_err = "");
            static std::pair<bool, bool> functions_equal(std::string p_name, std::string p_name2, std::vector<Type*> p_args, std::vector<Type*> p_args2, bool p_public, bool p_public2, bool has_varg=false);
    };

    struct Type {
        std::string name;
        std::vector<Type*> generics = {};

        bool is_array = false;

        std::string to_string() const {
            return name; // TODO: generics or array
        }

        std::string mangle() const {
            return TypeChecker::to_mangle((Type*)this);
        }

        bool equals(Type* p_comp, bool with_generics = true) const {
            if (!with_generics) return name == p_comp->name;

            bool gens_equal = p_comp->generics.size() == 0;

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

    inline Type* BOOL_TYPE    = new Type("Bool");
    inline Type* STRING_TYPE  = new Type("String");
    inline Type* NUMBER_TYPE  = new Type("Int");
    inline Type* INT16_TYPE   = new Type("i16");
    inline Type* INT32_TYPE   = new Type("i32");
    inline Type* INT64_TYPE   = new Type("i64");
    inline Type* FLOAT32_TYPE = new Type("f32");
    inline Type* FLOAT64_TYPE = new Type("f64");
    inline Type* VOID_TYPE    = new Type("Void");

    llvm::Type* get_llvm_type_from_sn_type(BuildinTypes type, std::shared_ptr<llvm::IRBuilder<>> builder);
    llvm::Function* get_alloca(llvm::Module* p_module, std::shared_ptr<llvm::IRBuilder<>> p_builder);
    llvm::Function* get_puts(llvm::Module* p_module, std::shared_ptr<llvm::IRBuilder<>> p_builder);
}

#endif // __SNOWBALL_BUILDIN_TYPES_H_
