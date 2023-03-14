
#include "../../ast/errors/error.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>
#include <llvm-14/llvm/IR/Verifier.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::Func> func) {
    setDebugInfoLoc(func);
    auto fn = createLLVMFunction(func);

    funcs.insert({func->getId(), fn});
    this->value = fn;
}

void LLVMBuilder::buildBodiedFunction(ptr<llvm::Function> llvmFn,
                                      ptr<ir::Func> fn) {
    ctx->setCurrentFunction(llvmFn);

    auto returnType = getLLVMType(fn->getRetTy());

    auto entry = h.create<llvm::BasicBlock>(*context, "entry", llvmFn);
    auto body  = h.create<llvm::BasicBlock>(*context, "body", llvmFn);

    // mark: entry block
    builder->SetInsertPoint(entry);

    auto fnArgs       = fn->getArgs();
    auto llvmArgsIter = llvmFn->arg_begin();
    for (auto varIter = fnArgs.begin(); varIter != fnArgs.end(); ++varIter) {
        auto var     = varIter->second;
        auto storage = builder->CreateAlloca(getLLVMType(var->getType()));
        builder->CreateStore(llvmArgsIter, storage);

        // note: We sum "1" to the ID because each "Variable" has the argument
        // stored.
        //  variable searches for it's ID and not the argument ID (aka: var id -
        //  1). basically, we sum 1 because thats the ID when we store it as a
        //  variable.
        ctx->addSymbol(var->getId() + 1, storage);

        // debug info
        auto src     = var->getSourceInfo();
        auto dbgInfo = var->getDBGInfo();

        auto file     = dbg.getFile(src->getPath());
        auto scope    = llvmFn->getSubprogram();
        auto debugVar = dbg.builder->createParameterVariable(
            scope, var->getName(), var->getIndex(), file, dbgInfo->line,
            getDIType(var->getType().get()), dbg.debug);
        dbg.builder->insertDeclare(
            storage, debugVar, dbg.builder->createExpression(),
            llvm::DILocation::get(*context, dbgInfo->line, dbgInfo->pos.second,
                                  scope),
            entry);

        ++llvmArgsIter;
    }

    // Generate all the used variables
    for (auto v : fn->getSymbols()) {
        auto llvmType = getLLVMType(v->getType());
        auto storage  = builder->CreateAlloca(llvmType);
        ctx->addSymbol(v->getId(), storage);

        // debug info
        auto src     = v->getSourceInfo();
        auto dbgInfo = v->getDBGInfo();

        auto file     = dbg.getFile(src->getPath());
        auto scope    = llvmFn->getSubprogram();
        auto debugVar = dbg.builder->createAutoVariable(
            scope, v->getIdentifier(), file, dbgInfo->line,
            getDIType(v->getType().get()), dbg.debug);
        dbg.builder->insertDeclare(
            storage, debugVar, dbg.builder->createExpression(),
            llvm::DILocation::get(*context, dbgInfo->line, dbgInfo->pos.second,
                                  scope),
            entry);
    }

    builder->CreateBr(body);

    // mark: body block
    builder->SetInsertPoint(body);

    // Codegen for the current body
    fn->getBody()->visit(this);

    // Create return type
    if ((!builder->GetInsertBlock()->getInstList().back().isTerminator()) ||
        builder->GetInsertBlock()->getInstList().size() == 0) {

        if (utils::cast<types::VoidType>(fn->getRetTy().get())) {
            builder->CreateRetVoid();
        } else {
            // TODO: warning
            builder->CreateRet(llvm::Constant::getNullValue(returnType));
        }
    }

    // mark: clean up
    ctx->clearCurrentFunction();
}

} // namespace codegen
} // namespace snowball