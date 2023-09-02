
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_BLOCK_VALUE_H_
#define __SNOWBALL_BLOCK_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of block in the IR. This contains
 * instructions that are executed inside of it.
 */
class Block : public AcceptorExtend<Block, Value>, public AcceptorExtend<Func, Syntax::AttributeHolder> {
  // Instructions stored inside a block
  std::vector<std::shared_ptr<Value>> insts;

 public:
  explicit Block(std::vector<std::shared_ptr<Value>> insts) : insts(insts){};

  /// @return body block instructions
  auto getBlock() { return insts; }
  /// @brief It prepends a new instruction to the block
  void prepend(std::shared_ptr<Value> inst) { insts.insert(insts.begin(), inst); }
  /// @brief It prepends a new set of instructions to the block
  void prepend(std::vector<std::shared_ptr<Value>> inst) {
    for (auto i = inst.rbegin(); i != inst.rend(); ++i) { prepend(*i); }
  }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_BLOCK_VALUE_H_
