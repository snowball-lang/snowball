
#ifndef __SNOWBALL_COMPILER_SIL_INSTS_H__
#define __SNOWBALL_COMPILER_SIL_INSTS_H__

#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/utils/id.h"

namespace snowball {
namespace sil {

using namespace frontend;
class SilVisitor;

class Inst {
  ast::types::Type* type;
public:
  Inst(ast::types::Type* type) : type(type) {}
  virtual ~Inst() = default;
  
  auto get_type() const { return type; }
  virtual void emit(SilVisitor*) = 0;

  template <typename T>
  [[nodiscard]] auto as() { return dynamic_cast<T*>(this); }
  template <typename T>
  bool is() { return as<T>() != nullptr; }
};

#define EMITABLE() void emit(SilVisitor* visitor) override;

class Block : public Inst {
  std::vector<Inst*> insts;
public:
  Block(ast::types::Type* type, const std::vector<Inst*>& insts) 
    : Inst(type), insts(insts) {}
  ~Block() = default;

  auto get_insts() const { return insts; }
  EMITABLE()

  static auto create(ast::types::Type* type, const std::vector<Inst*>& insts) {
    return new Block(type, insts);
  }
};

class FuncDecl : public Inst, public ast::AttributedNode, public Identified {
  std::string name;
  std::vector<std::string> params;
  std::optional<Block*> body;
public:
  FuncDecl(ast::types::Type* type, const std::string& name, const std::vector<std::string>& params,
    const ast::AttributedNode& attrs, std::optional<Block*> body = std::nullopt)
    : Inst(type), AttributedNode(attrs), name(name), params(params), body(body) {}
  ~FuncDecl() = default;

  auto get_name() const { return name; }
  auto get_params() const { return params; }
  EMITABLE()

  static auto create(ast::types::Type* type, const std::string& name, const std::vector<std::string>& params,
    const ast::AttributedNode& attrs, std::optional<Block*> body = std::nullopt) {
    return new FuncDecl(type, name, params, attrs, body);
  }
};

class VarDecl : public Inst, public ast::AttributedNode, public Identified {
  std::string name;
  std::optional<Inst*> value;
public:
  VarDecl(ast::types::Type* type, const std::string& name, const ast::AttributedNode& attrs, std::optional<Inst*> value = std::nullopt)
    : Inst(type), AttributedNode(attrs), name(name), value(value) {}
  ~VarDecl() = default;

  auto get_name() const { return name; }
  auto get_value() const { return value; }
  EMITABLE()

  static auto create(ast::types::Type* type, const std::string& name, const ast::AttributedNode& attrs, std::optional<Inst*> value = std::nullopt) {
    return new VarDecl(type, name, attrs, value);
  }
};

}
}

#endif // __SNOWBALL_COMPILER_SIL_INSTS_H__
