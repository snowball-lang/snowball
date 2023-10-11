
#include "OperatorService.h"

#include <algorithm>
#include <cassert>

namespace snowball {
namespace services {
using OpType = services::OperatorService::OperatorType;

std::string OperatorService::getOperatorId(OperatorService::OperatorType id) { return operators.at(id); }

bool OperatorService::isOperator(const std::string& name) { return utils::startsWith(name, "#"); }

const std::string& OperatorService::operatorName(OperatorType id) { return operatorNames.at(id); }

OperatorService::OperatorType OperatorService::operatorID(const std::string& n) {
  std::string name = n;
  if (isOperator(name)) { name = name.substr(1, name.size() - 1); }

  auto it = std::find(operators.begin(), operators.end(), name);
  assert(it != operators.end());

  return (OperatorService::OperatorType) std::distance(operators.begin(), it);
}

std::string OperatorService::getOperatorMangle(OperatorService::OperatorType id) { return "#" + getOperatorId(id); }

bool OperatorService::isUnary(OperatorService::OperatorType op_type) {
  return op_type == OpType::NOT || op_type == OpType::BIT_NOT || op_type == OpType::UPLUS ||
          op_type == OpType::UMINUS || op_type == OpType::REFERENCE || op_type == OpType::DEREFERENCE;
}

} // namespace services
} // namespace snowball
