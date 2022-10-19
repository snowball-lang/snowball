
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
    llvm::Value* Generator::generate_identifier(IdentifierNode* p_node) {

        ScopeValue* value;
        std::string name = ADD_MODULE_NAME_IF_EXISTS(".") (new Type(p_node->name))->mangle();

        bool found_value = false;
        if (_enviroment->item_exists(p_node->name)) {
            value = _enviroment->get(p_node->name, p_node);

            if (!(_context._current_module != nullptr && value->parent_scope->name() == SN_GLOBAL_SCOPE)) {
                found_value = true;
            }
        } else if (_enviroment->item_exists(name)) {
            value = _enviroment->get(name, p_node);

            if (!(_context._current_module != nullptr && value->parent_scope->name() == SN_GLOBAL_SCOPE)) {
                found_value = true;
            }
        }

        if ((!found_value) && _enviroment->item_exists(ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") p_node->name)) {
            value = _enviroment->get(ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") p_node->name, p_node);
        } else if ((!found_value) && _enviroment->item_exists(ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") name)) {
            value = _enviroment->get(ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") name, p_node);
        } else {
            if (!found_value) {
                COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Identifier '%s' does not exist!", p_node->name.c_str()))
            }
        }

        switch (value->type)
        {
            case ScopeType::MODULE:
            case ScopeType::NAMESPACE:
            case ScopeType::CLASS: {
                llvm::StructType* type = *value->llvm_struct;
                auto alloca = _builder->CreateAlloca(type);
                alloca->eraseFromParent();
                return alloca;
            }

            case ScopeType::FUNC:
                return (llvm::Value*)(*value->llvm_function);

            case ScopeType::LLVM: {
                llvm::Value* llvalue = *value->llvm_value;
                if (llvm::GlobalValue* G = llvm::dyn_cast<llvm::GlobalValue>(llvalue)) {

                    if (p_node->name.find(".") != std::string::npos) {
                        std::string split = snowball_utils::split(p_node->name, ".").at(0);
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
                COMPILER_ERROR(BUG, Logger::format("Invalid Scope Value (idnt: %s, ty: %i).", p_node->name.c_str(), value->type))
            }
        }
    }
}