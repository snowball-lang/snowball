
#include "../common.h"

#ifndef __SNOWBALL_VALUE_VISITOR_H_
#define __SNOWBALL_VALUE_VISITOR_H_

namespace snowball {
namespace ir {
class Value;

#define VISIT(n) class n;
#include "../defs/visits.def"
#undef VISIT

} // namespace ir

namespace codegen {

/**
 * @brief Value visitor
 *
 * This class is just a tree visitor that we
 * can use for different scenarios. e.g. for
 * type checking and for generating llvm ir.
 */
class ValueVisitor {
 public:
  /**
   * @brief Start the codegen process
   *
   * Transform the value tree into an output the
   * can use for another process.
   */
  virtual void codegen() = 0;

#define VISIT(n) virtual void visit(ir::n*) = 0;
#include "../defs/visits.def"
#undef VISIT
};

} // namespace codegen
} // namespace snowball

#endif // __SNOWBALL_VALUE_VISITOR_H_
