
#include "../../errors.h"
#include "../../sourceInfo/SourcedObject.h"
#include "../syntax/nodes.h"

#include <assert.h>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_ERROR_H_
#define __SNOWBALL_AST_ERROR_H_

namespace snowball {
namespace Syntax {

template <Error e = Error::BUG, class Val>
auto EI(Val item, std::string msg = "", ErrorInfo info = {}) {
  auto i = item->getDBGInfo();
  auto error = new CompilerError(e, msg, i, info);
  return error;
}

template <Error e, class Val>
void E(Val item, std::string msg, ErrorInfo info = {}) {
  throw *EI<e>(item, msg, info);
}

template <Error e>
void E(std::string msg) {
  throw SNError(e, msg);
}

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_ERROR_H_
