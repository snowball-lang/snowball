
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::Call* node) {
  assert(node->get_callee() && "Call callee is null");
  auto callee = accept(node->get_callee());
  auto args = std::vector<sil::Inst*>();
  args.reserve(node->get_args().size());
  for (auto arg : node->get_args()) {
    args.push_back(accept(arg));
  }
  auto call = Call::create(node->get_location(), get_type(node), callee, args);
  optimize_virtual_call(call);
  value = call;
}

void Binder::visit(ast::NewExpr* node) {
  visit(node->as<ast::Call>());
}

std::optional<FuncDecl*> Call::get_callee_as_func() const {
  auto callee = get_callee();
  auto func_use = callee->as<ValueUse>();
  if (!func_use) return std::nullopt;
  auto func = func_use->get_value()->as<FuncDecl>();
  if (!func) return std::nullopt;
  return func;
}

}
} // namespace snowball

