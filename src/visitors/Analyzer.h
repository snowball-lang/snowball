
#include "../ast/syntax/nodes.h"
#include "../ast/types/DefinedType.h"
#include "../ast/types/FunctionType.h"
#include "../ast/visitor/Visitor.h"
#include "../ir/module/Module.h"
#include "../ir/values/Argument.h"
#include "../ir/values/Call.h"
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

#define ACCEPT(Node)               virtual void visit(ptr<Node> p_node) override = 0;
#define SN_ANALYZER_VISIT(Node)    void Analyzer::visit(ptr<Node> p_node)

namespace snowball {
namespace Syntax {

/**
 * @class Analyzer
 * @brief Analyzes an Abstract Syntax Tree (AST) and produces analysis results.
 *
 * This class provides functionality to analyze an AST and extract relevant
 * information from it. The class takes an AST as input and produces analysis
 * results, which can be used for various purposes such as optimizing code,
 * generating reports, or improving program understanding. The analysis is
 * performed by traversing the AST and examining the nodes and their properties.
 *
 * @note This class assumes that the AST is valid and conforms to the expected
 * syntax and structure. Any errors or inconsistencies in the AST may result in
 * incorrect or incomplete analysis results.
 */
class Analyzer : public AcceptorExtend<Analyzer, Visitor> {

#include "../defs/accepts.def"
public:
    // Default destructor
    ~Analyzer() noexcept = default;
};

} // namespace Syntax
} // namespace snowball

#undef ACCEPT
#endif // __SNOWBALL_ANALYZER_H_
