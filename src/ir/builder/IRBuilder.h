
#include "../../DBGSourceInfo.h"
#include "../../ast/types/PrimitiveTypes.h"
#include "../../common.h"

#include "../values/Value.h"
#include "../ModuleHolder.h"

#include <list>
#include <unordered_map>

#ifndef __SNOWBALL_IR_BUILDER_H_
#define __SNOWBALL_IR_BUILDER_H_

namespace snowball {
namespace ir {

/// @brief IRBuilder is a utility class to create new instructions
class IRBuilder : public AcceptorExtend<IRBuilder, ModuleHolder>{
  public:
    IRBuilder() = default;

    /// @brief Utility function to create a new instruction
    template <typename DesiredType, typename... Args>
    std::shared_ptr<DesiredType> N(DBGSourceInfo* dbg, Args&&... args) {
        auto ret = std::shared_ptr<DesiredType>(new DesiredType(std::forward<Args>(args)...));
        ret->setModule(shared_from_this());
        ret->setSourceInfo(getSourceInfo());
        ret->setDBGInfo(dbg);

        return ret;
    }
};
} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_MODULE_H_
