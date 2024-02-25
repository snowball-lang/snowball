
#ifndef __SNOWBALL_COMPILER_SIL_INSTS_H__
#define __SNOWBALL_COMPILER_SIL_INSTS_H__

#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/ast/nodes.h"

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
  virtual void emit(SilVisitor&) = 0;

  template <typename T>
  [[nodiscard]] auto as() { return dynamic_cast<T*>(this); }
  template <typename T>
  bool is() { return as<T>() != nullptr; }
};

#define EMITABLE() void emit(SilVisitor& visitor) override;

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

class FuncDecl : public Inst, ast::AttributedNode {
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

}
}

#endif // __SNOWBALL_COMPILER_SIL_INSTS_H__
