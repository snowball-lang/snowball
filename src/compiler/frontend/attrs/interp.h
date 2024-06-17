
#ifndef __SNOWBALL_FRONTEND_SEMA_ATTRS_INTER_H__
#define __SNOWBALL_FRONTEND_SEMA_ATTRS_INTER_H__

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

#include "compiler/ctx.h"
#include "compiler/utils/utils.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/nodes.h"

#include "compiler/reports/reporter.h"
#include "compiler/frontend/attrs/attr.h"

#include <llvm/ADT/DenseMap.h>

#undef F
#include <llvm/ADT/StringRef.h>
#define SNOWBALL_UTILS_REDEFINE_F__
#include "compiler/utils/utils.h"
#undef SNOWBALL_UTILS_REDEFINE_F__

namespace snowball {
namespace frontend {
namespace ast::attrs {

#ifndef SNOWBALL_ATTRS_CALL_STACK_SIZE
#define SNOWBALL_ATTRS_CALL_STACK_SIZE 128
#endif

class AttrInstance;
class AttrInterpreter;

struct ParentArgs {
  // Callback used to run back from the parent.
  // e.g. cfg(not(target_os = "windows")). `not` will
  // call the parent (cfg) with the attribute (target_os, "windows").
  std::optional<std::function<bool(const std::string&, std::optional<std::string>,
    Reporter&, AttrInterpreter&, const Attr&)>> callback;
};

class AttrInterpreter final {
  std::unordered_map<std::string, AttrInstance*> instances;
  std::vector<AttrInstance*> call_stack;

public:
  using Target = std::optional<ast::Node*>;

  AttrInterpreter() = default;
  ~AttrInterpreter() = default;

  /// @return true if the attribute is valid. E.g. target os is the same as the current os.
  bool interpret(Reporter& reporter, const Attr& attrs, 
                Target target = std::nullopt, const ParentArgs& args = {});
  bool interpret(Reporter& reporter, const std::vector<Attr>& attrs, 
                Target target = std::nullopt, const ParentArgs& args = {});

  void register_instance(const std::string& name, AttrInstance* instance);
  void unregister_instance(const std::string& name);

  void register_builtin_instances();
  void error(Reporter& reporter, const std::string& message, Error::Info info = Error::Info(),
            const SourceLocation& loc = SourceLocation::dummy());

  static auto create() { return AttrInterpreter(); }
  static std::string get_attr_name(const Attr& attr) { 
    return utils::replace_all(attr.get_key(), ".", "::"); 
  }
};

class AttrInstance {
  std::string name;

public:
  AttrInstance(const std::string& name) : name(name) {}
  virtual ~AttrInstance() = default;

  virtual bool interpret(const Attr& attr, AttrInterpreter::Target target,
                        Reporter& reporter, AttrInterpreter& interpreter,
                        const ParentArgs& args = {}) = 0;
                        
};

} // namespace sema::attrs
} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_SEMA_ATTRS_INTER_H__
