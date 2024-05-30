
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::Call* node) {
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

}
} // namespace snowball

