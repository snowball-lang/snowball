
#include "../../DBGSourceInfo.h"
#include "../../common.h"
#include "../values/Func.h"
#include "Module.h"

#ifndef __SNOWBALL_MAIN_MODULE_H_
#define __SNOWBALL_MAIN_MODULE_H_

/**
 * @brief Main module
 *
 * The main module is considered as the "top level"
 * version of the program.
 *
 * This module contains extra information such as;
 * a pointer to the main function and untit tests.
 */
namespace snowball {
namespace ir {

/// @brief The main module compiled from a snowball project
class MainModule : public Module {

    /// @brief Main function called to start the program.
    ptr<Func> entryPoint;
    /// @brief a list of generated modules through the whole project
    std::vector<std::shared_ptr<ir::Module>> modules;

  public:
    /**
     * @brief Utility method to easily downcast.
     * Useful when a child doesn't inherit directly from enable_shared_from_this
     * but wants to use the feature.
     *
     * @todo move this to a generic class parent
     */
    template <class Down> std::shared_ptr<Down> downcasted_shared_from_this() {
        return std::dynamic_pointer_cast<Down>(Module::shared_from_this());
    }

  public:
    MainModule() : Module("$main"){};

    /// @return true because it's the entry point
    bool isMain() override { return true; }
    /// @return a list of generated modules through the whole project
    std::vector<std::shared_ptr<ir::Module>> getModules() const {
        return modules;
    }
    /// @brief add all the modules to the global generated modules list
    void setModules(std::vector<std::shared_ptr<ir::Module>> m) { modules = m; }
};
} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_MAIN_MODULE_H_
