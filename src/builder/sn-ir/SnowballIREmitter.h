#include "../../ValueVisitor/Visitor.h"
#include "../../ir/values/Value.h"
#include "../../sourceInfo/DBGSourceInfo.h"

#include <assert.h>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

#ifndef __SNOWBALL_IR_EMITTER_H_
#define __SNOWBALL_IR_EMITTER_H_

namespace snowball {
namespace codegen {

/**
 * @brief SnowballIREmitter class
 *
 * The SnowballIREmitter class is responsible for generating an Intermediate Representation (IR)
 * code in the form of a string representation. This IR code represents a program's logic and structure
 * and can serve as input for various subsequent stages of code generation and optimization.
 *
 * This class extends the ValueVisitor hierarchy, allowing it to traverse and visit different types
 * of IR values to emit their corresponding string representations. It operates on a module, which
 * encapsulates the entire program to be emitted.
 *
 * The SnowballIREmitter supports the following functionalities:
 * - Generating IR code for different types of IR values by visiting them and converting them to strings.
 * - Emitting the generated IR code to a specified output destination, such as a file or console.
 * - Ensuring consistency and correctness by relying on the underlying IR value structure.
 *
 * The emitted IR code can then be utilized for various purposes, including debugging, optimization,
 * and generating machine code or other target-specific representations.
 */
class SnowballIREmitter : public AcceptorExtend<SnowballIREmitter, codegen::ValueVisitor> {
  // Program represented by a module.
  std::shared_ptr<ir::Module> module;
  // String representation of the emitted IR code.
  std::stringstream output;

 public:
  /**
   * @brief Construct a SnowballIREmitter instance.
   * @param mod The IR module to be emitted.
   */
  SnowballIREmitter(std::shared_ptr<ir::Module> mod);

  /**
   * @brief Destructor for the SnowballIREmitter.
   */
  ~SnowballIREmitter() noexcept = default;

  /**
   * @brief Generate and emit the IR code to the specified output destination.
   * @param output The output destination for the emitted IR code.
   */
  void codegen(std::string output);

  // Deleting the default codegen() function to prevent accidental usage.
  void codegen() override { assert(false); }

 private:
  /**
   * @brief Visit and emit IR code for a given IR value.
   * @param v The IR value to be visited and emitted.
   */
  void visit(ir::Value* v) { v->visit(this); }

  /**
   * @brief Emit a new module.
   * @param p_node The module to be emitted.
   */
  void visit(std::shared_ptr<ir::Module> p_node);

  /**
   * @brief Add string content to the emitted IR code.
   * @param p_node The string content to be added.
   */
  void addContent(std::string str);

  // Define visit functions for various IR value types using the visits.def file.
#define VISIT(n) void visit(ir::n*) override;
#include "../../defs/visits.def"
#undef VISIT
};

} // namespace codegen
} // namespace snowball

#undef VISIT
#endif // __SNOWBALL_IR_EMITTER_H_
