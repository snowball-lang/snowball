
#include "../../errors.h"
#include "../../ir/values/Argument.h"
#include "../../utils/utils.h"
#include "LLVMBuilder.h"

#include <llvm/AsmParser/Parser.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Linker/Linker.h>
#include <llvm/Support/SourceMgr.h>

namespace snowball {
namespace codegen {

llvm::Function *LLVMBuilder::buildLLVMFunction(llvm::Function *llvmFn, ir::Func *fn) {
    ctx->setCurrentFunction(nullptr);

    // llvmFn->getDe
    std::string bufStr;
    llvm::raw_string_ostream buf(bufStr);

    buf << "define ";
    llvmFn->getReturnType()->print(buf);
    buf << " @\"" << llvmFn->getName() << "\"(";

    auto args = fn->getArgs();
    for (int i = 0; i < args.size(); i++) {
        auto l_front = args.begin();
        std::advance(l_front, i);

        llvmFn->getArg(i)->getType()->print(buf);
        buf << " %" << l_front->first;

        if (i < (args.size() - 1)) buf << ", ";
    }

    buf << ") { \nentry:\n\t";
    buf << fn->getLLVMBody();
    buf << "\n}";

    auto code = buf.str();
    bufStr.clear();

    auto llvmBuffer = llvm::MemoryBuffer::getMemBuffer(code);

    llvm::SMDiagnostic err;
    std::unique_ptr<llvm::Module> sub =
        llvm::parseIR(llvmBuffer->getMemBufferRef(), err, *context);
    if (!sub) {
        std::string bufStr;
        llvm::raw_string_ostream buf(bufStr);
        err.print("LLVM", buf);
        DUMP_S(code.c_str())

        DUMP_S(buf.str().c_str())
        assert(false && "TODO: (LLVM ERROR)");
    }

    sub->setDataLayout(module->getDataLayout());

    llvm::Linker linker(*module);
    const bool fail = linker.linkInModule(std::move(sub));
    assert(!fail);

    auto func = module->getFunction(fn->getMangle());
    assert(func && "function not linked in");
    func->setLinkage(llvm::GlobalValue::PrivateLinkage);
    func->addFnAttr(llvm::Attribute::AttrKind::NoInline); // TODO: user decides,
                                                          // this is default
    func->setSubprogram(getDISubprogramForFunc(fn));

    func->takeName(llvmFn);
    func->setName(fn->getMangle());

    llvmFn->replaceAllUsesWith(llvmFn);
    if (fn->isStatic() && (!fn->hasParent())) llvmFn->removeFromParent();

    setDebugInfoLoc(nullptr);
    return func;
}

} // namespace codegen
} // namespace snowball
