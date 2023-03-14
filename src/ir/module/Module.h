
#include "../../DBGSourceInfo.h"
#include "../../ast/types/PrimitiveTypes.h"
#include "../../common.h"

#include <list>

#ifndef __SNOWBALL_MODULE_H_
#define __SNOWBALL_MODULE_H_

namespace snowball {
namespace ir {

class Func;

/// @brief The representation of a programm
class Module : public AcceptorExtend<Module, SrcObject>,
               public std::enable_shared_from_this<Module> {

    // Module's name. The main modules has
    // a default name.
    std::string name;

    // Unique identifier given to the module
    // as string.
    std::string uniqueName;

    // A list containing all the functions that need to
    // be generated.
    std::vector<std::shared_ptr<ir::Func>> functions;

    // Parent module that contains this module.
    std::shared_ptr<Module> parent = nullptr;

  public:
    Module(std::string name, std::string uuid = "", std::shared_ptr<Module> parent = nullptr);

    /// @return module's name
    std::string getName() const;
    /// @return module's unique identifier
    std::string getUniqueName() const;

    // Boolean representing whether the module is global or not
    virtual bool isMain() { return false; }

    // Return a list of defined functions used for our program
    virtual std::vector<std::shared_ptr<ir::Func>> getFunctions() {
        return functions;
    }
    // Return a list of defined functions used for our program
    virtual void addFunction(std::shared_ptr<ir::Func> fn) {
        functions.push_back(fn);
    }

    /// @brief Utility function to create a new instruction
    template <typename DesiredType, typename... Args>
    std::shared_ptr<DesiredType> N(ptr<DBGSourceInfo> dbg, Args&&...args) {
        auto ret = std::shared_ptr<DesiredType>(
            new DesiredType(std::forward<Args>(args)...));
        ret->setModule(shared_from_this());
        ret->setSourceInfo(getSourceInfo());
        ret->setDBGInfo(dbg);

        return ret;
    }
};
} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_MODULE_H_
