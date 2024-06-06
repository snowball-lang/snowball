
#include "compiler/utils/utils.h"
#include "compiler/backend/llvm/builder.h"

#include "compiler/frontend/ast/operators.h"

namespace snowball {
namespace backend {

#define OPERATOR(t, f) case frontend::Operator::t: \
  value = builder->f(left, right); break;
#define UIOP(t, uf, if) case frontend::Operator::t: \
  value = (is_signed) ? builder->uf(left, right) : builder->if(left, right); break;

void LLVMBuilder::emit(const sil::BinaryOp* node) {
  // TODO: Support unary operators
  auto left = expr(node->get_lhs());
  auto right = expr(node->get_rhs().value());
  auto type = node->get_type();
  auto op = node->get_op();

  if (type->is_int() || type->is_pointer()) {
    bool is_signed = type->is_pointer() ? false : type->as_int()->is_signed();
    switch (op) {
      UIOP(Plus, CreateAdd, CreateNSWAdd)
      UIOP(Minus, CreateSub, CreateNSWSub)
      UIOP(Mul, CreateMul, CreateNSWMul)
      UIOP(Div, CreateSDiv, CreateUDiv)
      UIOP(Mod, CreateSRem, CreateURem)
      UIOP(BitRshift, CreateAShr, CreateLShr)
      UIOP(BitAnd, CreateAnd, CreateAnd)
      UIOP(BitOr, CreateOr, CreateOr)
      UIOP(BitXor, CreateXor, CreateXor)
      OPERATOR(BitLshift, CreateShl)
      OPERATOR(Eqeq, CreateICmpEQ)
      OPERATOR(Noteq, CreateICmpNE)
      OPERATOR(Lt, CreateICmpSLT)
      OPERATOR(Gt, CreateICmpSGT)
      OPERATOR(Lteq, CreateICmpSLE)
      OPERATOR(Gteq, CreateICmpSGE)
      case frontend::Operator::Eq: {
        if (llvm::isa<llvm::LoadInst>(left)) {
          left = llvm::cast<llvm::LoadInst>(left)->getPointerOperand();
        }
        value = builder->CreateStore(right, left);
        break;
      }
      default: sn_unreachable();
    }
  } else if (type->is_float()) {
    switch (op) {
      OPERATOR(Plus, CreateFAdd)
      OPERATOR(Minus, CreateFSub)
      OPERATOR(Mul, CreateFMul)
      OPERATOR(Div, CreateFDiv)
      OPERATOR(Eqeq, CreateFCmpOEQ)
      OPERATOR(Noteq, CreateFCmpONE)
      OPERATOR(Lt, CreateFCmpOLT)
      OPERATOR(Gt, CreateFCmpOGT)
      OPERATOR(Lteq, CreateFCmpOLE)
      OPERATOR(Gteq, CreateFCmpOGE)
      case frontend::Operator::Eq: {
        if (llvm::isa<llvm::LoadInst>(left)) {
          left = llvm::cast<llvm::LoadInst>(left)->getPointerOperand();
        }
        value = builder->CreateStore(right, left);
        break;
      }
      default: sn_unreachable();
    }
  } else {
    sn_unreachable();
  }
}

}
} // namespace snowball
