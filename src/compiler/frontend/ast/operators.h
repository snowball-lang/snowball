
namespace snowball {
namespace frontend {

enum class Operator {
#define DEFINE_OP(_, n, _2) \
  n,
#include "compiler/frontend/ast/operators.def"
#undef DEFINE_OP
};

}
}
