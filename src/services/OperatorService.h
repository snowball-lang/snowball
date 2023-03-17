
#include "../common.h"

#include <vector>
#include <string>

#ifndef __SNOWBALL_SERVICES_OPERATORS_H_
#define __SNOWBALL_SERVICES_OPERATORS_H_

namespace snowball {
namespace services {

/**
 * @brief It manages all of the operator-related
 *  stuff such as operator name, etc...
 * @note It will only contain static functions for
 *  utility-related things
 */
class OperatorService {
public:

#define OPERATOR(o, n, s) o = n,
    /**
     * @brief A list containing all of the possible overload-able
     *  operators that a class can define.
     */
    enum OperatorType {
#include "../defs/operators.def"
    };
#undef OPERATOR
    /**
     * @brief A list containing the respective operator identifier
     *  as a list of strings
     */
    static const std::vector<std::string> operators;

public:
    /// @brief Get the respective operator identifier
    static std::string getOperatorId(OperatorType id);
    /// @brief Get operator identifier but with an "#"
    ///  prepended to it.
    static std::string getOperatorMangle(OperatorType id);
};

#define OPERATOR(o, n, s) s,
inline const std::vector<std::string> OperatorService::operators = {
#include "../defs/operators.def"
    };
#undef OPERATOR

} // namespace services
} // namespace snowball

#endif // __SNOWBALL_SERVICES_OPERATORS_H_
