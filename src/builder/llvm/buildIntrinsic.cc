
#include "../../ir/values/IndexExtract.h"
#include "../../ir/values/Call.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

namespace snowball {
namespace codegen {

bool LLVMBuilder::buildIntrinsic(ir::Call* call) {
  auto callee = utils::dyn_cast<ir::Func>(call->getCallee());
  if (!callee) return false;
  if (!callee->hasAttribute(Attributes::INTRINSIC)) return false;
  auto name = callee->getMangle();
  auto& args = call->getArguments();
  if (name == "write_via_move") {
    assert(args.size() == 2);
    auto ptr = expr(args[0].get());
    auto value = expr(args[1].get());
    //auto load = builder->CreateLoad(value->getType()->getPointerTo(), ptr);
    builder->CreateStore(value, ptr);
  } else if (name == "sn.memcpy") {
    assert(args.size() == 3);
    auto dest = expr(args[0].get());
    auto src = expr(args[1].get());
    auto count = expr(args[2].get());
    builder->CreateMemCpy(dest, llvm::MaybeAlign(1), src, llvm::MaybeAlign(1), count);
  } else if (name == "sn.memmove") {
    assert(args.size() == 3);
    auto dest = expr(args[0].get());
    auto src = expr(args[1].get());
    auto count = expr(args[2].get());
    builder->CreateMemMove(dest, llvm::MaybeAlign(1), src, llvm::MaybeAlign(1), count);
  } else if (name == "sn.memset") {
    assert(args.size() == 3);
    auto dest = expr(args[0].get());
    auto value = expr(args[1].get());
    auto count = expr(args[2].get());
    builder->CreateMemSet(dest, value, count, llvm::MaybeAlign(1));
  } else if (name == "sn.debugbreak") {
    assert(args.size() == 0);
    builder->CreateIntrinsic(llvm::Intrinsic::debugtrap, {}, {});
  } else if (name == "sn.discriminant") {
    assert(args.size() == 1);
    auto val = expr(args[0].get());
    if (val->getType()->isPointerTy()) {
      this->value = builder->CreateStructGEP(getLLVMType(args[0]->getType()), val, 0); // the analyser should have ensured this is an enum
      this->value = builder->CreateLoad(builder->getInt32Ty(), this->value);
    } else {
      this->value = builder->CreateExtractValue(val, 0);
    }
  } else Syntax::E<BUG>(call, FMT("unknown intrinsic: %s", name.c_str()));
  return true;
}

} // namespace codegen
} // namespace snowball
