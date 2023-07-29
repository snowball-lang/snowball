
#include "../../../../ast/errors/error.h"
#include "../../../../errors.h"
#include "../../DefinitveAssigment.h"

namespace snowball {
namespace Syntax {

SN_DEFINITE_ASSIGMENT_VISIT(Expression::LambdaFunction) {
  auto f = p_node->getFunc();
  // TODO: check for the assigned lambda values, e.g.:
  //          [a=b, c=2+5, ...]
  for (auto a : f->getArgs()) { this->scopes.front().insert({a->getName(), Initialized}); }

  auto body = f->getBody();
  body->accept(this);
}

} // namespace Syntax
} // namespace snowball
