
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
    auto enumType = utils::cast<types::EnumType>(switchStmt->getExpr()->getType());
    auto parent = ctx->getCurrentFunction();
    assert(parent);
    auto expr = build(switchStmt->getExpr().get());
    auto exprIndex = builder->CreateStructGEP(getLLVMType(enumType), expr, 0);
    auto exprValue = builder->CreateLoad(builder->getInt8Ty(), exprIndex, ".switch-index");

    std::vector<llvm::BasicBlock*> blocks;
    for (auto& c : switchStmt->getCases()) {
        blocks.push_back(h.create<llvm::BasicBlock>(*context, "switch-case-" + c.name, parent));
    }
    auto defaultBlock = h.create<llvm::BasicBlock>(*context, "switch-default", parent);
    auto continueBlock = h.create<llvm::BasicBlock>(*context, "switch-continue", parent);
    auto switchInst = builder->CreateSwitch(exprValue, defaultBlock, blocks.size());

    for (size_t i = 0; i < switchStmt->getCases().size(); i++) {
        auto c = switchStmt->getCases()[i];
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
            auto enumGep = builder->CreateStructGEP(createEnumFieldType(enumType, field), expr, j);
            auto enumValue = builder->CreateLoad(getLLVMType((*enumField).types[j - 1]), enumGep);
            builder->CreateStore(enumValue, var);
            j++;
        }
        build(c.block.get());
        if (!builder->GetInsertBlock()->getTerminator()) { builder->CreateBr(continueBlock); }
        switchInst->addCase(builder->getInt8(enumIndex), block);
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
