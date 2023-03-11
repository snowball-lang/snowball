

#include "../../SourcedObject.h"
#include "../syntax/nodes.h"

#include <assert.h>
#include <string>
#include <vector>

#ifndef __SNOWBALL_AST_CACHE_H_
#define __SNOWBALL_AST_CACHE_H_

#include "FunctionCache.h"
#include "TypeCache.h"

namespace snowball {
namespace Syntax {

/**
 * @brief The cache class
 *
 * This class is used for temporal storage where
 * it can't affect for the real one. It also adds
 * some extra context to the ast visitor.
 */
class Cache : public cacheComponents::Functions,
              public cacheComponents::Types {};

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_AST_CACHE_H_
