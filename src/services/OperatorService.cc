
#include "OperatorService.h"

namespace snowball {
namespace services {

std::string OperatorService::getOperatorId(OperatorService::OperatorType id) {
    return operators.at(id);
}

std::string OperatorService::getOperatorMangle(OperatorService::OperatorType id) {
    return "#" + getOperatorId(id);
}

} // namespace services
} // namespace snowball
