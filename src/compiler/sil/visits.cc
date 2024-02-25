
#include "compiler/sil/insts.h"
#include "compiler/sil/visitor.h"

namespace snowball {
namespace sil {

#define SN_REGISTER_ACCEPT(n) void n::emit(SilVisitor* v) { v->emit(this); }
#include "compiler/sil/insts.def"

}
}

