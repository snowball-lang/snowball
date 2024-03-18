
#ifndef __SNOWBALL_COMPILER_SIL_INSTS_H__
#define __SNOWBALL_COMPILER_SIL_INSTS_H__

#include "compiler/frontend/ast/types.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/utils/id.h"

namespace snowball {
namespace sil {

using namespace frontend;
class SilVisitor;

class Inst : public LocationHolder {
  ast::types::Type* type;
public:
  Inst(LocationHolder& loc, ast::types::Type* type) 
    : LocationHolder(loc), type(type) {}
  virtual ~Inst() = default;
  
  auto get_type() const { return type; }
  virtual void emit(SilVisitor*) = 0;

  template <typename T>
  [[nodiscard]] auto as() { return dynamic_cast<T*>(this); }
  template <typename T>
  bool is() { return as<T>() != nullptr; }
};

#define EMITABLE() void emit(SilVisitor* visitor) override;

class Block final : public Inst {
  std::vector<Inst*> insts;
public:
  Block(LocationHolder& loc, ast::types::Type* type, const std::vector<Inst*>& insts) 
    : Inst(loc, type), insts(insts) {}
  ~Block() = default;

  auto get_insts() const { return insts; }
  EMITABLE()

  static auto create(LocationHolder loc, ast::types::Type* type, const std::vector<Inst*>& insts) {
    return new Block(loc, type, insts);
  }
};

class FuncDecl final : public Inst, public ast::AttributedNode, public Identified {
  using ParamType = std::pair<uint64_t, std::string>;
  std::string name;
  std::vector<ParamType> params;
  std::optional<Block*> body;
public:
  FuncDecl(LocationHolder& loc, ast::types::Type* type, const std::string& name, const std::vector<ParamType>& params,
    const ast::AttributedNode& attrs, std::optional<Block*> body = std::nullopt, uint64_t id = 0)
    : Identified(id), Inst(loc, type), AttributedNode(attrs), name(name), params(params), body(body) {}
  ~FuncDecl() = default;

  auto get_name() const { return name; }
  auto get_params() const { return params; }
  auto get_body() const { return body; }
  void set_body(Block* b) { body = b; }
  EMITABLE()

  static auto create(LocationHolder loc, ast::types::Type* type, const std::string& name, const std::vector<ParamType>& params,
    const ast::AttributedNode& attrs, std::optional<Block*> body = std::nullopt, uint64_t id = 0) {
    assert(id > 0);
    return new FuncDecl(loc, type, name, params, attrs, body, id);
  }
};

class VarDecl final : public Inst, public ast::AttributedNode, public Identified {
  std::string name;
  std::optional<Inst*> value;
public:
  VarDecl(LocationHolder& loc, ast::types::Type* type, const std::string& name, const ast::AttributedNode& attrs, 
    std::optional<Inst*> value = std::nullopt, uint64_t id = 0)
    : Identified(id), Inst(loc, type), AttributedNode(attrs), name(name), value(value) {}
  ~VarDecl() = default;

  auto get_name() const { return name; }
  auto get_value() const { return value; }
  EMITABLE()

  static auto create(LocationHolder loc, ast::types::Type* type, const std::string& name, const ast::AttributedNode& attrs, 
    std::optional<Inst*> value = std::nullopt, uint64_t id = 0) {
    assert(id > 0);
    return new VarDecl(loc, type, name, attrs, value, id);
  }
};

class ValueUse final : public Inst {
  Inst* value;
public:
  ValueUse(LocationHolder& loc, ast::types::Type* type, Inst* value) : Inst(loc, type), value(value) {}
  ~ValueUse() = default;

  auto get_value() const { return value; }
  EMITABLE()

  static auto create(LocationHolder loc, Inst* value) {
    return new ValueUse(loc, value->get_type(), value);
  }
};

class Call final : public Inst {
  Inst* callee;
  std::vector<Inst*> args;
public:
  Call(LocationHolder& loc, ast::types::Type* type, Inst* callee, const std::vector<Inst*>& args)
    : Inst(loc, type), callee(callee), args(args) {}
  ~Call() = default;

  auto get_callee() const { return callee; }
  auto get_args() const { return args; }
  EMITABLE()

  static auto create(LocationHolder loc, ast::types::Type* type, Inst* callee, const std::vector<Inst*>& args) {
    return new Call(loc, type, callee, args);
  }
};

class ConstInt final : public Inst {
  int64_t value;
public:
  ConstInt(LocationHolder& loc, ast::types::Type* type, int64_t value) : Inst(loc, type), value(value) {}
  ~ConstInt() = default;

  auto get_value() const { return value; }
  EMITABLE()

  static auto create(LocationHolder loc, ast::types::Type* type, int64_t value) {
    return new ConstInt(loc, type, value);
  }
};

}
}

#endif // __SNOWBALL_COMPILER_SIL_INSTS_H__
