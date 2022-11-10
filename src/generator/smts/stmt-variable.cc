
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
    llvm::Value* Generator::generate_variable_decl(VarNode* p_node) {
        // TODO: check if variable is global

        Scope* scope = _enviroment->current_scope();

        if (scope->item_exists( p_node->name) || p_node->name == _enviroment->current_scope()->name()) {
            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("'%s' has already been declared", p_node->name.c_str()))
        }

        if (p_node->isGlobal) {
            if (!(p_node->value->type == Node::Ty::CONST_VALUE)) {
                auto mangled_name = ((std::string)"_GLOBAL__I") + mangle("$SN.$GlobalInit$");
                auto fn = _module->getFunction(mangled_name);

                if (!fn) {
                    auto prototype = llvm::FunctionType::get(_builder->getVoidTy(), {});
                    fn = llvm::Function::Create(
                            prototype,
                            llvm::Function::ExternalLinkage,
                            mangled_name,
                            _module);

                    // Create CTors
                    auto ctors_ty = llvm::StructType::get(_builder->getInt32Ty(), prototype->getPointerTo(), _builder->getInt8PtrTy());
                    llvm::GlobalVariable* ctors_gvar = new llvm::GlobalVariable(/*Module=*/*_module,
                        /*Type=*/llvm::ArrayType::get(ctors_ty, 1),
                        /*isConstant=*/true,
                        /*Linkage=*/llvm::GlobalValue::AppendingLinkage,
                        /*Initializer=*/llvm::ConstantArray::get(llvm::ArrayType::get(ctors_ty, 1),
                            llvm::ConstantStruct::get(ctors_ty, {
                                llvm::ConstantInt::get(_builder->getInt32Ty(), 65535),
                                fn,
                                llvm::ConstantPointerNull::get(_builder->getInt8PtrTy())
                            })
                        ), // has initializer, specified below
                        /*Name=*/"llvm.global_ctors");

                    ctors_gvar->setSection(".ctor");

                    // Create function
                    llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder->getContext(), "body", fn);
                    _builder->SetInsertPoint(body);

                    _builder->CreateRetVoid();

                }

                llvm::BasicBlock& block = fn->getEntryBlock();
                block.back().eraseFromParent();

                _builder->SetInsertPoint(&block);

                auto g_value = generate(p_node->value);
                auto g_type = g_value->getType();
                llvm::GlobalVariable* gvar_ptr = new llvm::GlobalVariable(/*Module=*/*_module,
                    /*Type=*/g_type,
                    /*isConstant=*/false,
                    /*Linkage=*/llvm::GlobalValue::CommonLinkage,
                    /*Initializer=*/0, // has initializer, specified below
                    /*Name=*/(ADD_MODULE_NAME_IF_EXISTS("::") ADD_NAMESPACE_NAME_IF_EXISTS("::") p_node->name));

                gvar_ptr->setInitializer(llvm::Constant::getNullValue(g_type));

                std::unique_ptr<ScopeValue*> scope_val = std::make_unique<ScopeValue*>(
                    new ScopeValue(
                        std::make_shared<llvm::Value*>(
                            gvar_ptr
                        )
                    )
                );

                (*scope_val)->isPublic = p_node->isPublic;
                SET_TO_GLOBAL_OR_CLASS(p_node->name, scope_val);

                _builder->CreateStore(g_value, gvar_ptr);
                _builder->CreateRetVoid();

                return gvar_ptr;
            }

            auto g_value = generate(p_node->value);
            llvm::GlobalVariable* gvar_ptr = new llvm::GlobalVariable(/*Module=*/*_module,
                /*Type=*/TypeChecker::type2llvm(_builder, g_value->getType()),
                /*isConstant=*/false,
                /*Linkage=*/llvm::GlobalValue::ExternalLinkage,
                /*Initializer=*/static_cast<llvm::Constant *>(g_value), // has initializer, specified below
                /*Name=*/(ADD_MODULE_NAME_IF_EXISTS("::") ADD_NAMESPACE_NAME_IF_EXISTS("::") p_node->name));

            std::unique_ptr<ScopeValue*> scope_val = std::make_unique<ScopeValue*>(new ScopeValue(std::make_shared<llvm::Value*>(gvar_ptr)));
            (*scope_val)->isPublic = p_node->isPublic;
            SET_TO_GLOBAL_OR_CLASS(p_node->name, scope_val);

            return gvar_ptr;
        } else {
            llvm::Value* value = generate(p_node->value);
            auto* alloca = _builder->CreateAlloca (value->getType(), nullptr, p_node->name );

            std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(value)));
            _enviroment->current_scope()->set(p_node->name, std::move(scope_value));

            return _builder->CreateStore (value, alloca, /*isVolatile=*/false);
        }

    }
}