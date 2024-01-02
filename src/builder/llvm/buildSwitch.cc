
#include "../../ir/values/Variable.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"
#include "varFetchImpl.h"
#include "../../ast/errors/error.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ir::Switch* switchStmt) {
//    auto expr = build(switchStmt->getExpr());
//    auto exprIndex = builder->CreateStructGEP(expr, 0);
//    auto exprValue = builder->CreateLoad(builder->getInt8Ty(), exprIndex, ".switch-index");
//
//    std::vector<llvm::BasicBlock*> blocks;
//    for (auto& c : switchStmt->getCases()) {
//        blocks.push_back(h.create<llvm::BasicBlock>("switch-case-" + c.name));
//    }
//    auto defaultBlock = h.create<llvm::BasicBlock>("switch-default");
//    auto continueBlock = h.create<llvm::BasicBlock>("switch-continue");
//    auto switchInst = builder->CreateSwitch(exprValue, defaultBlock, blocks.size());
//
//    for (auto i = 0; i < (int)switchStmt->getCases().size(); i++) {
//        auto& c = switchStmt->getCases()[i];
//        auto vars = c.
    assert(false);
}

} // namespace codegen
} // namespace snowball
