#include "BaseType.h"
#include "../../common.h"
#include "../../constants.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "../syntax/common.h"
#include "../syntax/nodes.h"
#include "Type.h"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace snowball {
namespace types {

BaseType::BaseType(Kind t, std::string name) : Type(t, name) { }
std::shared_ptr<ir::Module> BaseType::getModule() const { return module; }
std::string BaseType::getUUID() const { return uuid; }
void BaseType::setUUID(std::string uuid) { this->uuid = uuid; }
void BaseType::setModule(std::shared_ptr<ir::Module> m) { module = m; }

} // namespace types
} // namespace snowball
