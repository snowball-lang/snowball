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
    llvm::Value* Generator::generate_if_stmt(IfStatementNode *p_node) {
        #define ELSE_STMT_EXISTS() p_node->else_stmt != NULL

        llvm::Value* inital_value = generate(p_node->stmt);
        GET_BOOL_VALUE(condition, inital_value)

        llvm::Function *TheFunction = _builder->GetInsertBlock()->getParent();
        llvm::BasicBlock* IfBB = llvm::BasicBlock::Create(_builder->getContext(), "btrue", TheFunction);
        llvm::BasicBlock* ElseBB;

        if (ELSE_STMT_EXISTS()) {
            ElseBB = llvm::BasicBlock::Create(_builder->getContext(), "bfalse", TheFunction);
        }

        llvm::BasicBlock* ContinueBB = llvm::BasicBlock::Create(_builder->getContext(), "end", TheFunction);

        _builder->CreateCondBr(condition, IfBB, ELSE_STMT_EXISTS() ? ElseBB : ContinueBB);

        // Generate if statement
        _builder->SetInsertPoint(IfBB);
        _enviroment->create_scope("if$true");

        for (Node* node : p_node->body->exprs) {
            generate(node);
        }

        if (IfBB->size() == 0 || !IfBB->back().isTerminator()) {
            _builder->CreateBr(ContinueBB);
        }

        _enviroment->delete_scope();

        // Generate else statement (if it exist)
        if (ELSE_STMT_EXISTS()) {
            _builder->SetInsertPoint(ElseBB);
            _enviroment->create_scope("if$false");

            for (Node* node : p_node->else_stmt->exprs) {
                generate(node);
            }

            if (ElseBB->size() == 0 || !ElseBB->back().isTerminator()) {
                _builder->CreateBr(ContinueBB);
            }

            _enviroment->delete_scope();
        }

        // Continue with rest of body
        _builder->SetInsertPoint(ContinueBB);
        return ContinueBB;

        #undef ELSE_STMT_EXISTS
    }
}