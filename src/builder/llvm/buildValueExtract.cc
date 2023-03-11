
#include "../../ir/values/ValueExtract.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm-14/llvm/IR/Type.h>
#include <llvm-14/llvm/IR/Value.h>
#include <memory>

namespace snowball {
namespace codegen {

void LLVMBuilder::visit(ptr<ir::ValueExtract> extract) {
    auto var = extract->getValue();

    ptr<llvm::Value> value = nullptr;
    if (auto f = std::dynamic_pointer_cast<ir::Func>(var)) {
        auto fn = funcs.at(f->getId());
        value   = fn;
    } else if (auto v = std::dynamic_pointer_cast<ir::IdMixin>(var)) {
        auto id = v->getId();
        value   = ctx->getSymbol(id);
    } else {
        assert(false && "BUG: Value extract type not supported!");
    }

    this->value = builder->CreateLoad(getLLVMType(var->getType()), value);
}

} // namespace codegen
} // namespace snowball
