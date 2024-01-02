
#include "../ast/syntax/nodes.h"
#include "../ast/types/DefinedType.h"
#include "../ast/types/FunctionType.h"
#include "../ast/visitor/Visitor.h"
#include "../ir/module/Module.h"
#include "../ir/values/Argument.h"
#include "../ir/values/Call.h"
#include "../ir/values/EnumInit.h"
#include "../ir/values/Constants.h"
#include "../ir/values/Func.h"
#include "../ir/values/Return.h"
#include "../ir/values/ValueExtract.h"
#include "../utils/utils.h"

#include <assert.h>
#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_ANALYZER_H_
#define __SNOWBALL_ANALYZER_H_

#define ACCEPT(Node)            virtual void visit(Node* p_node) override{};
#define SN_ANALYZER_VISIT(Node) void Analyzer::visit(Node* p_node)

namespace snowball {
namespace Syntax {

/**
 * @class Analyzer
 * @brief Analyzes an Abstract Syntax Tree (AST) and produces analysis
 * results.
 *
 * This class provides functionality to analyze an AST and extract
 * relevant information from it. The class takes an AST as input and
 * produces analysis results, which can be used for various purposes
 * such as optimizing code, generating reports, or improving program
 * understanding. The analysis is performed by traversing the AST and
 * examining the nodes and their properties.
 *
 * @note This class assumes that the AST is valid and conforms to the
 * expected syntax and structure. Any errors or inconsistencies in the
 * AST may result in incorrect or incomplete analysis results.
 */
class Analyzer : public AcceptorExtend<Analyzer, Visitor> {
#include "../defs/accepts.def"
public:
  Analyzer(const SourceInfo* srci) : AcceptorExtend(srci){};

  /**
   * A function that executes a pass manager on a vector of syntax
   * nodes.
   *
   * The run function takes a vector of syntax nodes as its argument
   * and iterates through them, calling the accept function on each
   * node and passing this object as the argument. The accept function
   * then invokes the appropriate method for the specific node type.
   * This allows the pass manager to traverse the syntax tree and
   * perform analysis or transformation on each node as needed.
   *
   * @param nodes The vector of syntax nodes to be processed by the
   * pass manager.
   */
  void run(std::vector<Syntax::Node*> nodes) {
    for (auto n : nodes) { n->accept(this); }
  }

  // Default destructor
  ~Analyzer() noexcept = default;
};

} // namespace Syntax
} // namespace snowball

#undef ACCEPT
#endif // __SNOWBALL_ANALYZER_H_
