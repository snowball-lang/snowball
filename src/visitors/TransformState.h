#include "../ir/module/Module.h"
#include "TransformItem.h"

#include <deque>
#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_TRANSFORM_STATE_H_
#define __SNOWBALL_TRANSFORM_STATE_H_

namespace snowball {
namespace Syntax {
namespace transform {

/// @brief Representation of a saved state for the context
struct ContextState {
    std::deque<std::map<std::string, std::shared_ptr<Item>>> stack;
    std::shared_ptr<ir::Module> module               = nullptr;
    std::shared_ptr<types::DefinedType> currentClass = nullptr;
};
} // namespace transform
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_TRANSFORM_STATE_H_
