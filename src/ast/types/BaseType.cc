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
void BaseType::unsafeSetUUID(std::string uuid) { this->uuid = uuid; }
void BaseType::unsafeSetModule(std::shared_ptr<ir::Module> m) { module = m; }
void BaseType::setDefaultGenerics(std::vector<Type*> generics) { defaultGenerics = generics; }
void BaseType::setDefaultGenericStart(std::size_t start) { defaultGenericStart = start; }
std::vector<Type*> BaseType::getDefaultGenerics() const { return defaultGenerics; }
std::size_t BaseType::getDefaultGenericStart() const { return defaultGenericStart; }
int BaseType::getVtableSize() { return classVtable.size(); }
void BaseType::unsafeOverrideVtable(std::vector<std::shared_ptr<ir::Func>> vtable) { classVtable = vtable; }
int BaseType::addVtableItem(std::shared_ptr<ir::Func> f) {
  classVtable.push_back(f);
  return getVtableSize() - 1;
}
std::vector<std::shared_ptr<ir::Func>>& BaseType::getVTable() { return classVtable; }

} // namespace types
} // namespace snowball
