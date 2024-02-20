
#ifndef __SNOWBALL_FRONTEND_SEMA_CHECK_H__
#define __SNOWBALL_FRONTEND_SEMA_CHECK_H__

#include <string>
#include <vector>

#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/visitors.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/sema/universe.h"
#include "compiler/reports/reporter.h"
#include "compiler/utils/utils.h"
#include "compiler/ctx.h"

namespace snowball {
namespace frontend {
namespace sema {

// Used for fatal errors
class StopTypeChecking : public std::exception {
public:
  StopTypeChecking() = default;
  ~StopTypeChecking() = default;
};

class TypeCheckItem {
public:
  enum Kind { Func, Type, Var };
private:
  Kind kind;
  union {
    // TODO:
    ast::types::Type* type;
    //ast::Func* func;
    //ast::Var* var;
  };
public:
  ~TypeCheckItem() = default;
  TypeCheckItem(ast::types::Type* type) : kind(Kind::Type), type(type) {}

  Kind get_kind() const { return kind; }
  ast::types::Type* get_type() const { sn_assert(is_type(), "not a type"); return type; }

  bool is_type() const { return kind == Kind::Type; }
  bool is_func() const { return kind == Kind::Func; }
  bool is_var() const { return kind == Kind::Var; }

  static auto create(ast::types::Type* type) { 
    return TypeCheckItem(type); 
  }
};

class TypeChecker : public ast::AstVisitor, public Reporter {
  Universe<TypeCheckItem> universe;
  std::vector<Module>& modules;
public:
  TypeChecker(const Ctx& ctx, std::vector<Module>& modules);
  ~TypeChecker() = default;

  void check();
#define SN_REGISTER_ACCEPT(n) virtual void visit(ast::n* node) override;
#include "compiler/frontend/ast/nodes.def"
#undef SN_REGISTER_ACCEPT
private:
  void register_builtins();

  void err(const LocationHolder* holder, const std::string& message, 
    const Error::Info& info = Error::Info(), Error::Type type = Error::Type::Err, 
    bool fatal = true);
};

}
}
}

#endif // __SNOWBALL_FRONTEND_SEMA_CHECK_H_
