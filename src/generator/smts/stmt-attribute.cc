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
    llvm::Value* Generator::generate_attribute(AttributeNode* p_node) {
        auto attrs = _api->get_attributes();

        for (auto node_attrs : p_node->attributes) {
            bool attr_exists = false;
            for (auto attr : attrs) {
                if (attr->get_name() == node_attrs.name) {
                    attr_exists = true;

                    if (attr->start(_api->context)) {
                        auto generated = generate(p_node->node);

                        if (generated->getType()->isPointerTy() ?
                            generated->getType()->getPointerElementType()->isFunctionTy() :
                            generated->getType()->isFunctionTy()) {
                            Attribute::ResponseValue response;
                            response.type = Attribute::ResponseValue::ResponseType::LLVM_FUNCTION;
                            response.function.llvm_value = generated;

                            auto result = unmangle(generated->getName().str());
                            Enviroment::FunctionStore* function_store;

                            if ((function_store = _enviroment->find_function_if(result.name, [=](auto store) -> std::pair<bool, bool> {
                                if ((store.node->arguments.size() <= result.arguments.size()) && store.node->has_vargs) {}
                                else if (store.node->arguments.size() != result.arguments.size()) return {false, false};
                                return TypeChecker::functions_equal(
                                    store.node->name,
                                    store.node->name,
                                    TypeChecker::args2types(store.node->arguments),
                                    result.arguments,
                                    result.isPublic,
                                    store.node->is_public,
                                    store.node->has_vargs);
                            }, p_node))) {
                                response.function.store = function_store;
                            } else {
                                COMPILER_ERROR(BUG, "Coudn't find function in attribute")
                            }

                            attr->end(response, _api);
                        } else {
                            COMPILER_ERROR(BUG, "Unsuported type from attribute")
                        }
                    }

                    break;
                }
            }

            if (!attr_exists) {
                COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Attribute name not found: %s", node_attrs.name.c_str()))
            }
        }
    }
}