
#include "compiler/backend/llvm/builder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace backend {

void LLVMBuilder::emit(const sil::ConstInt* node) {
  value = llvm::ConstantInt::get(get_type(node->get_type()), node->get_value());
}

void LLVMBuilder::emit(const sil::ConstString* node) {
  auto str = builder->CreateGlobalStringPtr(node->get_value(), ".__str." + utils::gen_random_string<30>());
  auto arr = llvm::ArrayType::get(builder->getInt8Ty(), node->get_value().size() + 1);
  value = builder->CreateConstInBoundsGEP1_32(arr, str, 0);
  builder_ctx.dont_load = true;
}

}
} // namespace snowball
