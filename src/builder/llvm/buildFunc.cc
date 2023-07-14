
#include "../../errors.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Func* func) {
    if (auto it = funcs.find(func->getId()); it != funcs.end()) {
        this->value = it->second;
        return;
    }

    setDebugInfoLoc(func);
    auto fn = createLLVMFunction(func);
    if (func->hasAttribute(Attributes::ALLOW_FOR_TEST)) {
        fn->addFnAttr(llvm::Attribute::NoInline);
        ctx->tests[func->getNiceName()] = fn;
    }

    funcs.insert({func->getId(), fn});
    this->value = fn;
}

llvm::Function* LLVMBuilder::buildBodiedFunction(llvm::Function* llvmFn, ir::Func* fn) {
    ctx->setCurrentFunction(llvmFn);

    auto returnType = getLLVMType(fn->getRetTy());

    auto entry = h.create<llvm::BasicBlock>(*context, "entry", llvmFn);
    auto body = h.create<llvm::BasicBlock>(*context, "body", llvmFn);

    // mark: entry block
    builder->SetInsertPoint(entry);
    setDebugInfoLoc(nullptr);

    auto fnArgs = fn->getArgs();
    auto llvmArgsIter = llvmFn->arg_begin();
    for (auto varIter = fnArgs.begin(); varIter != fnArgs.end(); ++varIter) {
        auto var = varIter->second;
        auto storage = builder->CreateAlloca(getLLVMType(var->getType()));
        builder->CreateStore(llvmArgsIter, storage);

        // note: We sum "1" to the ID because each "Variable" has the
        // argument stored.
        //  variable searches for it's ID and not the argument ID (aka:
        //  var id - 1). basically, we sum 1 because thats the ID when
        //  we store it as a variable.
        ctx->addSymbol(var->getId() + 1, storage);

        // debug info
        auto src = var->getSourceInfo();
        auto dbgInfo = var->getDBGInfo();

        auto file = dbg.getFile(src->getPath());
        auto scope = llvmFn->getSubprogram();
        auto debugVar = dbg.builder->createParameterVariable(scope,
                                                             var->getName(),
                                                             var->getIndex(),
                                                             file,
                                                             dbgInfo->line,
                                                             getDIType(var->getType().get()),
                                                             dbg.debug);
        dbg.builder->insertDeclare(
                storage,
                debugVar,
                dbg.builder->createExpression(),
                llvm::DILocation::get(*context, dbgInfo->line, dbgInfo->pos.second, scope),
                entry);

        ++llvmArgsIter;
    }

    // Generate all the used variables
    for (auto v : fn->getSymbols()) {
        auto llvmType = getLLVMType(v->getType());
        auto storage = builder->CreateAlloca(llvmType);
        ctx->addSymbol(v->getId(), storage);

        // debug info
        auto src = v->getSourceInfo();
        auto dbgInfo = v->getDBGInfo();

        auto file = dbg.getFile(src->getPath());
        auto scope = llvmFn->getSubprogram();
        auto debugVar = dbg.builder->createAutoVariable(scope,
                                                        v->getIdentifier(),
                                                        file,
                                                        dbgInfo->line,
                                                        getDIType(v->getType().get()),
                                                        dbg.debug);
        dbg.builder->insertDeclare(
                storage,
                debugVar,
                dbg.builder->createExpression(),
                llvm::DILocation::get(*context, dbgInfo->line, dbgInfo->pos.second, scope),
                entry);
    }

    builder->CreateBr(body);

    // mark: body block
    builder->SetInsertPoint(body);

    // Codegen for the current body
    fn->getBody()->visit(this);
    setDebugInfoLoc(nullptr);

    // Create return type
    if ((!builder->GetInsertBlock()->getInstList().back().isTerminator()) ||
        builder->GetInsertBlock()->getInstList().size() == 0) {
        if (utils::cast<types::VoidType>(fn->getRetTy().get())) {
            builder->CreateRetVoid();
        } else if (fn->isConstructor()) {
            // note: 0 should be always the "self" parameter
            assert(!llvmFn->args().empty());
            builder->CreateRet(llvmFn->getArg(0));
        } else {
            // TODO: warning
            builder->CreateRet(llvm::Constant::getNullValue(returnType));
        }
    }

    // mark: clean up
    ctx->clearCurrentFunction();

    auto DISubprogram = llvmFn->getSubprogram();
    dbg.builder->finalizeSubprogram(DISubprogram);

    std::string module_error_string;
    llvm::raw_string_ostream module_error_stream(module_error_string);
    llvm::verifyFunction(*llvmFn, &module_error_stream);

    if (!module_error_string.empty()) {
#ifdef _SNOWBALL_BYTECODE_DEBUG
        dump();
#endif
        throw SNError(Error::LLVM_INTERNAL, module_error_string);
    }

    return llvmFn;
}

} // namespace codegen
} // namespace snowball
