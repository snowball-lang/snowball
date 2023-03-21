
#include "OperatorService.h"

#include <algorithm>
#include <cassert>

namespace snowball {
namespace services {

std::string OperatorService::getOperatorId(OperatorService::OperatorType id) {
    return operators.at(id);
}

bool OperatorService::isOperator(const std::string& name) {
    return name.rfind("#", 0) == 0;
}

const std::string& OperatorService::operatorID(OperatorType id) {
    return operatorNames.at(id);
}

OperatorService::OperatorType
OperatorService::operatorID(const std::string& n) {
    std::string name = n;
    if (isOperator(name)) {
        name = name.substr(1, name.size() - 1);
    }

    auto it = std::find(operators.begin(), operators.end(), name);
    assert(it != operators.end());

    return (OperatorService::OperatorType)std::distance(operators.begin(), it);
}

std::string
OperatorService::getOperatorMangle(OperatorService::OperatorType id) {
    return "#" + getOperatorId(id);
}

} // namespace services
} // namespace snowball
