
#include "../../ValueVisitor/Visitor.h"
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/Type.h"
#include "../../common.h"
#include "Value.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_TRY_CATCH_VALUE_H_
#define __SNOWBALL_TRY_CATCH_VALUE_H_

namespace snowball {
namespace ir {

/**
 * @brief Representation of a try-catch block in the IR.
 * @note This is not the same as the try-catch block in C++.
 * This is more like the try-catch block in Java.
 * @see https://docs.oracle.com/javase/tutorial/essential/exceptions/try.html
 */
class TryCatch : public AcceptorExtend<TryCatch, Value> {
  // The block to execute
  std::shared_ptr<Block> block;
  // The catch block
  std::vector<std::shared_ptr<Block>> catchBlocks;
  // Catch types
  std::vector<std::shared_ptr<VariableDeclaration>> catchVars;

 public:
  explicit TryCatch(std::shared_ptr<Block> block,
          std::vector<std::shared_ptr<Block>>
                  catchBlocks,
          std::vector<std::shared_ptr<VariableDeclaration>>
                  catchVars)
      : block(block), catchBlocks(catchBlocks), catchVars(catchVars){};

  /// @return body block instructions to execute
  auto getBlock() { return block; }

  /// @return the catch blocks
  auto getCatchBlocks() { return catchBlocks; }

  /// @return the catch types
  auto getCatchVars() { return catchVars; }

  // Set a visit handler for the generators
  SN_GENERATOR_VISITS
};

} // namespace ir
} // namespace snowball

#endif // __SNOWBALL_TRY_CATCH_VALUE_H_
