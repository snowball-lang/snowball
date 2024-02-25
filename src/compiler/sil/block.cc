
#include "compiler/sil/insts.h"
#include "compiler/sil/binder.h"

namespace snowball {
namespace sil {

void Binder::visit(ast::Block* node) {
  std::vector<Inst*> insts;
  for (auto& item : node->get_stmts()) {
    insts.push_back(accept(item));
  }
  value = sil::Block::create(ast::types::VoidType::create(), insts);
}

}
}
