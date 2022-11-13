#include "snowball/libs.h"

#include "snowball/types.h"
#include "snowball/nodes.h"
#include "snowball/token.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include "snowball/generator/stmt/stmt-class.h"

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
    llvm::Value* Generator::generate_class(ClassNode* p_node) {
        Type* class_type = new Type(p_node->name);
        std::string struct_name = (ADD_MODULE_NAME_IF_EXISTS("::") ADD_NAMESPACE_NAME_IF_EXISTS("::") /*+*/ class_type->mangle());

        // TODO: check for generics
        // TODO: class name mangled if module exists
        Scope* class_scope = new Scope(p_node->name, _source_info);

        auto class_struct = llvm::StructType::create(_builder->getContext(), "struct." + struct_name);
        ScopeValue* class_scope_val = new ScopeValue(class_scope, std::make_shared<llvm::StructType*>(class_struct));

        std::vector<llvm::Type*> var_types;

        for (auto var : p_node->vars) {
            ScopeValue* type = TypeChecker::get_type(_enviroment, var->vtype, p_node);
            if (!TypeChecker::is_class(type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("'%s' does not reference a class", var->vtype->name.c_str()))
            }

            auto _type = TypeChecker::type2llvm(_builder, (llvm::Type*)(*type->llvm_struct));
            class_scope_val->properties.push_back({ .name = var->name, .type = _type, .is_public = var->isPublic });
            var_types.push_back(_type);
        }

        if (p_node->parent != nullptr) {
            ScopeValue* type = TypeChecker::get_type(_enviroment, p_node->parent, p_node);
            if (!TypeChecker::is_class(type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("'%s' does not reference a class", p_node->parent->name.c_str()))
            }

            for (auto var_propertie : type->properties) {
                auto parent_property = std::find_if(class_scope_val->properties.begin(), class_scope_val->properties.end(),
                    [&](const ScopeValue::ClassPropertie p) -> bool { return p.name == var_propertie.name; });

                if (parent_property == class_scope_val->properties.end()) {

                    auto _type = TypeChecker::type2llvm(_builder, var_propertie.type);

                    class_scope_val->properties.insert(class_scope_val->properties.begin(), var_propertie);
                    var_types.insert(var_types.begin(), _type);

                    p_node->_parent_props_count++;
                } else {
                    if (parent_property->type != var_propertie.type) {
                        auto p1_name = TypeChecker::llvm2type(var_propertie.type)->to_string();
                        auto p2_name = TypeChecker::llvm2type(parent_property->type)->to_string();

                        COMPILER_ERROR(TYPE_ERROR, Logger::format("Conflict types between '%s' (from parent) and '%s'", p1_name.c_str(), p2_name.c_str()))
                    }
                }
            }
        }

        std::unique_ptr<ScopeValue*> class_value = std::make_unique<ScopeValue*>(class_scope_val);
        SET_TO_GLOBAL_OR_CLASS(class_type->mangle(), class_value)

        p_node->_llvm_struct = class_struct;
        _context._current_class = p_node;
        _context._current_class->name = class_type->mangle();

        std::vector<FunctionNode*> virtual_functions;
        int possition_in_vtable = 0;
        for (FunctionNode* func : p_node->functions) {
            if (func->is_virtual) {
                func->_possition_in_vtable = possition_in_vtable;
                virtual_functions.push_back(func);
                possition_in_vtable++;
            }
        }

        if (virtual_functions.size() > 0) {
            class_scope_val->has_vtable = true;
            auto vtable = create_virtual_table(_module, struct_name, class_scope, virtual_functions, [&](FunctionNode* fn) -> llvm::Function* {
                return (llvm::Function*)generate_function(fn);
            });

            var_types.insert(var_types.begin(), vtable->getType());
            class_scope_val->vtable = vtable;
        }

        class_struct->setBody(var_types);

        for (FunctionNode* func : p_node->functions) {

            if (func->is_virtual)
                func->_vtable = class_scope_val->vtable;

            generate_function(func, func->is_virtual);
        }

        for (OperatorNode* func : p_node->operators) {
            generate(func);
        }

        _context._current_class = nullptr;
        return (llvm::Value*)class_struct;
    }

    llvm::Value* create_virtual_table(llvm::Module* module, std::string p_className, Scope* p_class, std::vector<FunctionNode*> p_nodes, std::function<llvm::Function* (FunctionNode*)> p_callback) {
        auto stuct_name = Logger::format(_SN_VTABLE_PREFIX "_Vt%sNf%iSt", p_className.c_str(), p_nodes.size());

        std::vector<llvm::Type*> types;
        std::vector<llvm::Constant*> functions;

        for (auto fn : p_nodes) {
            auto result = p_callback(fn);

            functions.push_back(result);
            types.push_back(result->getType());
        }

        auto vtable = llvm::StructType::create(module->getContext(), stuct_name);

        vtable->setBody(types);

        module->getOrInsertGlobal(stuct_name, vtable);

        llvm::GlobalVariable *vTable = module->getNamedGlobal(stuct_name);
        vTable->setInitializer(llvm::ConstantStruct::get(vtable, functions));

        return vTable;
    }
}