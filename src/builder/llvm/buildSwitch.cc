
#include "../../ir/values/Variable.h"
#include "../../ir/values/Switch.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"
#include "varFetchImpl.h"
#include "../../ast/errors/error.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Switch* switchStmt) {
    auto parent = ctx->getCurrentFunction();
    assert(parent);
    auto initExpr = (llvm::Value*)nullptr;
    auto exprValue = (llvm::Value*)nullptr;
    auto enumType = utils::cast<types::EnumType>(switchStmt->getExpr()->getType());
    if (!switchStmt->isCStyleSwitch()) {
        assert(enumType != nullptr);
        initExpr = build(switchStmt->getExpr().get());
        auto exprIndex = builder->CreateStructGEP(getLLVMType(enumType), initExpr, 0);
        exprValue = builder->CreateLoad(builder->getInt8Ty(), exprIndex, ".switch-index");
    } else exprValue = expr(switchStmt->getExpr().get());

    std::vector<llvm::BasicBlock*> blocks;
    for (auto& c : switchStmt->getCases().first) {
        blocks.push_back(h.create<llvm::BasicBlock>(*context, "switch-case-" + c.name, parent));
    }
    for (size_t cSwitchIndex = 0; cSwitchIndex < switchStmt->getCases().second.size(); cSwitchIndex++) {
        blocks.push_back(h.create<llvm::BasicBlock>(*context, "switch-case-" + std::to_string(cSwitchIndex), parent));
    }
    auto defaultBlock = h.create<llvm::BasicBlock>(*context, "switch-default", parent);
    auto continueBlock = h.create<llvm::BasicBlock>(*context, "switch-continue", parent);
    auto switchInst = builder->CreateSwitch(exprValue, defaultBlock, blocks.size());

    // non-c-style switch
    for (size_t i = 0; i < switchStmt->getCases().first.size(); i++) {
        assert(enumType != nullptr);
        assert(initExpr != nullptr);
        auto c = switchStmt->getCases().first[i];
        size_t enumIndex = 0;
        for (size_t j = 0; j < enumType->getFields().size(); j++) {
            if (enumType->getFields()[j].name == c.name) {
                enumIndex = j;
                break;
            }
        }
        auto field = c.name;
        auto vars = c.args;
        auto block = blocks[i];
        auto enumField = std::find_if(enumType->getFields().begin(), enumType->getFields().end(), [&](auto f) {
            return f.name == field;
        });
        assert(enumField != enumType->getFields().end());
        builder->SetInsertPoint(block);
        size_t j = 1;
        for (auto& v : vars) {
            auto var = ctx->getSymbol(v->getVariable()->getId());
            auto enumGep = builder->CreateStructGEP(createEnumFieldType(enumType, field), initExpr, j);
            auto enumValue = builder->CreateLoad(getLLVMType((*enumField).types[j - 1]), enumGep);
            builder->CreateStore(enumValue, var);
            j++;
        }
        build(c.block.get());
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(continueBlock); }
        switchInst->addCase(builder->getInt8(enumIndex), block);
    }

    // c-style switch
    for (size_t i = 0; i < switchStmt->getCases().second.size(); i++) {
        auto c = switchStmt->getCases().second[i];
        auto block = blocks[switchStmt->getCases().first.size() + i];
        builder->SetInsertPoint(block);
        build(c.block.get());
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(continueBlock); }
        switchInst->addCase(llvm::cast<llvm::ConstantInt>(build(c.value.get())), block);
    }

    builder->SetInsertPoint(defaultBlock);
    if (auto defaultCase = switchStmt->getDefaultCase()) {
        build(defaultCase.get());
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(continueBlock); }
    } else {
        builder->CreateBr(continueBlock);
    }

    builder->SetInsertPoint(continueBlock);
}

} // namespace codegen
} // namespace snowball
