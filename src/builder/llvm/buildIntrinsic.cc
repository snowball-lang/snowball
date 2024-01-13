
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
    } else assert(false);

    return true;
}

} // namespace codegen
} // namespace snowball
