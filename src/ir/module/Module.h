
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/PrimitiveTypes.h"
#include "../../common.h"
#include "../../sourceInfo/DBGSourceInfo.h"

#include <list>
#include <unordered_map>

#ifndef __SNOWBALL_MODULE_H_
#define __SNOWBALL_MODULE_H_

namespace snowball {
namespace Syntax::transform {
class MacroInstance;
} // namespace Syntax::transform
namespace types {
class BaseType;
}
namespace ir {

class Func;
class VariableDeclaration;

/// @brief The representation of a programm
class Module : public SrcObject, public std::enable_shared_from_this<Module> {
  // Module's name. The main modules has
  // a default name.
  std::string name;
  // Unique identifier given to the module
  // as string.
  std::string uniqueName;
  // A list containing all the functions that need to
  // be generated.
  std::vector<std::shared_ptr<ir::Func>> functions;
  // A list of declared variables used for this module
  std::vector<std::shared_ptr<ir::VariableDeclaration>> variables;
  // A list of exported macros
  std::unordered_map<std::string, Syntax::transform::MacroInstance*> exportedMacros = {};

public:
  Module(std::string name, std::string uuid = "");

  /// @return module's name
  std::string getName() const;
  /// @return module's unique identifier (UUID)
  std::string getUniqueName() const;

  // Boolean representing whether the module is global or not
  virtual bool isMain() { return false; }

  // Return a list of defined functions used for our program
  virtual std::vector<std::shared_ptr<ir::Func>> getFunctions() const { return functions; }
  // Push a new function to the module
  virtual void addFunction(std::shared_ptr<ir::Func> fn) { functions.push_back(fn); }
  // Append a new variable to the variable list
  virtual void addVariable(std::shared_ptr<ir::VariableDeclaration> v) { variables.push_back(v); }
  // Get a list of user-declared variables for this module
  const auto& getVariables() const { return variables; }
  // Get a list of exported macros
  const auto getExportedMacros() const { return exportedMacros; }
  // Add a new exported macro
  void addExportedMacro(std::string name, Syntax::transform::MacroInstance* macro) { exportedMacros[name] = macro; }

  /// @brief Utility function to create a new instruction
  template <typename DesiredType, typename... Args>
  std::shared_ptr<DesiredType> N(DBGSourceInfo* dbg, Args&&... args) {
    auto ret = std::shared_ptr<DesiredType>(new DesiredType(std::forward<Args>(args)...));
    ret->setModule(shared_from_this());
    ret->setSourceInfo(getSourceInfo());
    ret->setDBGInfo(dbg);

    return ret;
  }

  /// @brief A list containing the definitive type information
  std::map<id_t, std::shared_ptr<types::BaseType>> typeInformation;
};
} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_MODULE_H_
