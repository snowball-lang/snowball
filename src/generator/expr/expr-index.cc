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
    llvm::Value* Generator::generate_index(IndexNode* p_node) {
        llvm::Value* gen_result = generate(p_node->base); // TODO: check if base points to a type
        llvm::Type* type = gen_result->getType();

        ScopeValue* value = _enviroment->get(TypeChecker::get_type_name(type), p_node);
        switch (value->type)
        {
            case ScopeType::CLASS: {
                std::vector<ScopeValue::ClassPropertie> properties = value->properties;

                ptrdiff_t pos = std::find_if(properties.begin(), properties.end(), [&](ScopeValue::ClassPropertie p_prop) {
                    return p_prop.name == p_node->member->name;
                }) - properties.begin();

                if (pos >= (properties.size())) {

                    // TODO: index error
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format(
                        "Class %s%s%s does not have a member called %s%s%s!",
                        BBLU, TypeChecker::to_type(TypeChecker::get_type_name(type)).first->to_string().c_str(), RESET,
                        BBLU, p_node->member->name.c_str(), RESET))
                }

                if ((!properties.at(pos).is_public) && _context._current_class == nullptr) {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format(
                        "Trying to access member private %s%s%s from class %s%s%s!",
                        BBLU, p_node->member->name.c_str(), RESET,
                        BBLU, TypeChecker::to_type(TypeChecker::get_type_name(type)).first->to_string().c_str(), RESET))
                }

                // We asume it's a pointer since raw types does not have any attriute
                auto GEP = _builder->CreateInBoundsGEP(gen_result->getType()->getPointerElementType(), gen_result, {llvm::ConstantInt::get(_builder->getInt32Ty(), 0), llvm::ConstantInt::get(_builder->getInt32Ty(), pos+value->parents.size())});
                return convert_to_right_value(_builder, GEP);
            }

            case ScopeType::MODULE: {
                std::string name = (value->module_name + ".") + TypeChecker::string_mangle(p_node->member->name);

                ScopeValue* result = nullptr;
                if (_enviroment->item_exists((value->module_name + ".") + p_node->member->name)) {
                    result = _enviroment->get((value->module_name + ".") + p_node->member->name, p_node);
                } else if (_enviroment->item_exists(name)) {
                    result = _enviroment->get(name, p_node);
                } else {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Module '%s' does not contain member '%s'", TypeChecker::to_type(value->module_name).first->to_string().c_str(), p_node->member->name.c_str()))
                }

                switch (result->type) {
                    case ScopeType::MODULE:
                    case ScopeType::CLASS:
                    case ScopeType::NAMESPACE: {

                        // TODO: check if namespaces are actually the same.
                        if ((
                            (_context._current_module == nullptr && result->type == ScopeType::MODULE) ||
                            (_context._current_class == nullptr && result->type == ScopeType::CLASS ) ||
                            (_context._current_namespace == nullptr && result->type == ScopeType::NAMESPACE)) && !result->isPublic) {
                            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Trying to access a private variable from '%s'", value->module_name.c_str()))
                        }

                        llvm::StructType* type = *result->llvm_struct;
                        auto alloca = _builder->CreateAlloca(type);
                        alloca->eraseFromParent();
                        return alloca;
                    }

                    case ScopeType::FUNC:
                        return (llvm::Value*)(*result->llvm_function);

                    case ScopeType::LLVM: {
                        llvm::Value* llvalue = *result->llvm_value;
                        if (llvm::GlobalValue* G = llvm::dyn_cast<llvm::GlobalValue>(llvalue)) {

                            if (p_node->member->name.find(".") != std::string::npos) {
                                std::string split = snowball_utils::split(p_node->member->name, ".").at(0);
                                if ((_context._current_module == nullptr ? true : _context._current_module->module_name != split)) {
                                    if (!value->isPublic) {
                                        COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Trying to access a private variable from '%s'", split.c_str()))
                                    }
                                }
                            }

                            return convert_to_right_value(_builder, G);
                        }

                        return llvalue;
                    }

                    default: {
                        COMPILER_ERROR(BUG, Logger::format("Invalid Scope Value (idnt: %s, ty: %i).", p_node->member->name.c_str(), value->type))
                    }
                }

                return nullptr;
            }

            case ScopeType::NAMESPACE: {
                // TODO: custom error if no member exists
                std::string name = (value->module_name + ".") + TypeChecker::string_mangle(p_node->member->name);

                ScopeValue* result = nullptr;
                if (_enviroment->item_exists((value->module_name + ".") + p_node->member->name)) {
                    result = _enviroment->get((value->module_name + ".") + p_node->member->name, p_node);
                } else if (_enviroment->item_exists(name)) {
                    result = _enviroment->get(name, p_node);
                } else {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Namespace '%s' does not contain member '%s'", TypeChecker::to_type(value->module_name).first->to_string().c_str(), p_node->member->name.c_str()))
                }

                switch (result->type) {
                    case ScopeType::MODULE:
                    case ScopeType::CLASS:
                    case ScopeType::NAMESPACE: {

                        if ((
                            (_context._current_module == nullptr && result->type == ScopeType::MODULE) ||
                            (_context._current_class == nullptr && result->type == ScopeType::CLASS ) ||
                            (_context._current_namespace == nullptr && result->type == ScopeType::NAMESPACE)) && !result->isPublic) {
                            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Trying to access a private variable from '%s'", value->module_name.c_str()))
                        }

                        llvm::StructType* type = *result->llvm_struct;
                        auto alloca = _builder->CreateAlloca(type);
                        alloca->eraseFromParent();
                        return alloca;
                    }

                    case ScopeType::FUNC:

                        if ((
                            (_context._current_module == nullptr && result->type == ScopeType::MODULE) ||
                            (_context._current_class == nullptr && result->type == ScopeType::CLASS ) ||
                            (_context._current_namespace == nullptr && result->type == ScopeType::NAMESPACE)) && !result->isPublic) {
                            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Trying to access a private function from '%s'", value->module_name.c_str()))
                        }

                        return (llvm::Value*)(*result->llvm_function);

                    case ScopeType::LLVM: {
                        llvm::Value* llvalue = *result->llvm_value;
                        if (llvm::GlobalValue* G = llvm::dyn_cast<llvm::GlobalValue>(llvalue)) {

                            if (p_node->member->name.find(".") != std::string::npos) {
                                std::string split = snowball_utils::split(p_node->member->name, ".").at(0);
                                if ((_context._current_namespace == nullptr ? true : _context._current_namespace->module_name != split)) {
                                    if (!value->isPublic) {
                                        COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Trying to access a private variable from '%s'", split.c_str()))
                                    }
                                }
                            }

                            return convert_to_right_value(_builder, G);
                        }

                        return llvalue;
                    }

                    default: {
                        COMPILER_ERROR(BUG, Logger::format("Invalid Scope Value (idnt: %s, ty: %i).", p_node->member->name.c_str(), value->type))
                    }
                }

                return nullptr;
            }

            case ScopeType::FUNC: {
                COMPILER_ERROR(TODO, "Function index!")
            }

            case ScopeType::LLVM: {
                COMPILER_ERROR(TODO, "LLVM Index!")
            }

            default: {
                COMPILER_ERROR(BUG, Logger::format("Scope with type ::SCOPE has been fetched in Generator::generate_index (idnt: %s).", p_node->member->name.c_str()))
            }
        }
    }
}