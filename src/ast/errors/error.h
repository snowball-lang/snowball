
#include "../../SourcedObject.h"
#include "../../errors.h"
#include "../syntax/nodes.h"

#include <assert.h>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_ERROR_H_
#define __SNOWBALL_AST_ERROR_H_

namespace snowball {
namespace Syntax {

template <Error e, class Val>
void E(Val item, std::string msg, ErrorInfo info = {}) {
    auto i = item->getDBGInfo();
    throw CompilerError(e, msg, i, info);
}

template <Error e> void E(std::string msg) { throw SNError(e, msg); }

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_ERROR_H_
