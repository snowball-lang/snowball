
#include "module/Module.h"

#ifndef __SNOWBALL_MODULE_HOLDER_H_
#define __SNOWBALL_MODULE_HOLDER_H_

namespace snowball {
namespace ir {

/// Container class that holds a module pointer
class ModuleHolder {
  protected:
    std::shared_ptr<Module> module;

  public:
    ModuleHolder() = default;

    /// @brief Setter for a module pointer
    void
    setModule(std::shared_ptr<Module> p_mod) {
        module = p_mod;
    }
    /// @return A module pointer
    std::shared_ptr<Module>
    getModule() {
        return module;
    }
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_MODULE_HOLDER_H_
