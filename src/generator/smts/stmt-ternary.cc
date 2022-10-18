
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
    llvm::Value* Generator::generate_ternary(TernaryOperator* p_node) {
        llvm::Value* value = generate(p_node->expr);
        GET_BOOL_VALUE(condition, value)

        llvm::Function *TheFunction = _builder->GetInsertBlock()->getParent();
        llvm::BasicBlock* IfBB = llvm::BasicBlock::Create(_builder->getContext(), "", TheFunction);
        llvm::BasicBlock* ElseBB = llvm::BasicBlock::Create(_builder->getContext(), "", TheFunction);

        llvm::BasicBlock* ContinueBB = llvm::BasicBlock::Create(_builder->getContext(), "", TheFunction);

        _builder->CreateCondBr(condition, IfBB, ElseBB);

        // Generate if statement
        _builder->SetInsertPoint(IfBB);
        auto vtrue = generate(p_node->btrue);
        _builder->CreateBr(ContinueBB);

        // Generate else statement (if it exist)
        _builder->SetInsertPoint(ElseBB);
        auto vfalse = generate(p_node->bfalse);
        _builder->CreateBr(ContinueBB);

        if (vtrue->getType() != vfalse->getType()) {
            COMPILER_ERROR(TYPE_ERROR, Logger::format("Ternary operator types don't match ('%s' and '%s')",
                TypeChecker::to_type(TypeChecker::get_type_name(vtrue->getType())).first->to_string().c_str(),
                TypeChecker::to_type(TypeChecker::get_type_name(vfalse->getType())).first->to_string().c_str()
            ))
        }

        // Continue with rest of body
        _builder->SetInsertPoint(ContinueBB);

        // vtrue and vfalse types should be the same
        // TODO: maybe do implicit_casting?
        auto phi = _builder->CreatePHI(vtrue->getType(), 2);

        phi->addIncoming(vtrue, IfBB);
        phi->addIncoming(vfalse, ElseBB);

        return phi;
    }
}