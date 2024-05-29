
#ifndef __SNOWBALL_FRONTEND_AST_OPERATORS_H__
#define __SNOWBALL_FRONTEND_AST_OPERATORS_H__

namespace snowball {
namespace frontend {

enum class Operator
{
#define DEFINE_OP(_, n, _2) n,
#include "compiler/frontend/ast/operators.def"
#undef DEFINE_OP
};

} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_AST_OPERATORS_H__
