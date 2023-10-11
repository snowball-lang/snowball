

#include "FunctionCache.h"

#include "../types/DefinedType.h"
#include "../types/TypeAlias.h"

namespace snowball {
using namespace services;

namespace Syntax {
namespace cacheComponents {

std::shared_ptr<transform::ContextState>& Functions::getFunctionState(id_t id) { return functionStates.at(id); }
void Functions::setFunctionState(id_t id, std::shared_ptr<transform::ContextState>& s) { functionStates[id] = s; }
void Functions::setFunction(
        const std::string& name, Statement::FunctionDef* p_fn, std::shared_ptr<transform::ContextState> state
) {
  functions[name].push_front({p_fn, state});
}

std::optional<std::deque<Functions::FunctionStore>> Functions::getFunction(const std::string name) {
  auto f = functions.find(name);
  if (f != functions.end()) return f->second;

  return std::nullopt;
}

void Functions::setTransformedFunction(const std::string& uuid, std::shared_ptr<transform::Item> p_fn) {
  if (createdFunctions.count(uuid)) {
    auto x = createdFunctions.at(uuid);
    for (auto f : p_fn->getFunctions()) { x->addFunction(f); }
    return;
  }
  createdFunctions[uuid] = p_fn;
}

std::optional<std::shared_ptr<transform::Item>> Functions::getTransformedFunction(const std::string uuid) {
  auto f = createdFunctions.find(uuid);
  if (f != createdFunctions.end()) return f->second;

  return std::nullopt;
}

namespace {
template <typename T>
std::map<std::string, T> getAllFunctionsByUUID(std::string uuid, std::map<std::string, T>& functions) {
  std::map<std::string, T> result;
  for (auto f : functions) {
    if (utils::startsWith(f.first + ".", uuid)) { result[f.first] = f.second; }
  }
  return result;
}
} // namespace

void Functions::performInheritance(types::DefinedType* ty, types::DefinedType* parent, bool allowConstructor) {
  // Inherit all the way down
  if (parent->getParent() != nullptr) performInheritance(ty, parent->getParent(), allowConstructor);
  auto parentUUID = parent->getUUID();
  auto childUUID = ty->getUUID();
  auto createdFuncs = getAllFunctionsByUUID(parentUUID, createdFunctions);
  auto nonGeneratedFunctions = getAllFunctionsByUUID(parentUUID, functions);

  for (auto f : createdFuncs) {
    auto name = f.first;
    auto item = f.second;
    auto functions = item->getFunctions();
    utils::replaceAll(name, parentUUID + ".", "");
    if (OperatorService::opEquals<OperatorType::CONSTRUCTOR>(name) && !allowConstructor) continue;
    name = childUUID + "." + name;
    setTransformedFunction(name, std::make_shared<transform::Item>(*item));
    for (auto x : functions) {
      if (x->inVirtualTable()) { ty->addVtableItem(x); }
    }
  }

  for (auto f : nonGeneratedFunctions) {
    auto name = f.first;
    auto item = f.second;
    auto functions = item;
    // TODO: avoid constructors?
    utils::replaceAll(name, parentUUID + ".", "");
    if (OperatorService::opEquals<OperatorType::CONSTRUCTOR>(name) && !allowConstructor) continue;
    name = childUUID + "." + name;
    for (auto fn : functions) { setFunction(name, fn.function, fn.state); }
  }

  return;
}

} // namespace cacheComponents
} // namespace Syntax
} // namespace snowball
