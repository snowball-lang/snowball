
#include "../../ast/syntax/nodes.h"
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/FunctionType.h"
#include "../../ast/visitor/Visitor.h"
#include "../../utils/utils.h"
#include "../../services/OperatorService.h"

#include <assert.h>
#include <memory>
#include <string>
#include <vector>

#ifndef __SNOWBALL_DOCUMENTATION_GENERATOR_H_
#define __SNOWBALL_DOCUMENTATION_GENERATOR_H_

#define ACCEPT(Node)          virtual void visit(Node* p_node) override;
#define SN_DOCGEN_VISIT(Node) void DocGen::visit(Node* p_node)

namespace snowball {
namespace Syntax {

using Operator = services::OperatorService;

/**
 * @struct DocumentationPage
 * @brief A struct that represents a documentation page.
 * 
 * This struct represents a documentation page. It contains the name
 * of the page and the path to the file that contains the page.
 */
struct DocumentationPage {
  std::string name;
  std::filesystem::path path;

  std::string html;
  enum Type {
    Type,
    Function,
    Namespace,
    Module,
  } type;
};

/**
 * @struct DocumentationResult
 * @brief A struct that represents the result of a documentation analysis.
 * 
 * This struct represents the result of a documentation analysis. It
 * contains a vector of documentation pages, which can be used to
 * generate documentation for the program.
 */
struct DocumentationResult {
  std::vector<DocumentationPage> pages;
};

/**
 * @struct DocGenContext
 * @brief A struct that represents the context of the documentation generator.
 * 
 * This struct represents the context of the documentation generator. It
 * contains the current namespace, module and type that the generator is
 * analyzing.
*/
struct DocGenContext {
  std::string currentNamespace = "";
  std::string currentModule;
  std::string currentType = "";

  std::string currentNamespacePath;
  std::string currentModulePath = "";
  std::string currentTypePath = "";

  std::string baseURL;
};

/**
 * @class DocGen
 * @brief Analyzes an Abstract Syntax Tree (AST) and produces documentation
 * results.
 * 
 * This class provides functionality to analyze an AST and extract
 * relevant information from it. The class takes an AST as input and
 * produces documentation results, which can be used for various purposes
 * such as generating documentation for the program. The analysis is performed
 * by traversing the AST and examining the nodes and their properties.
 * 
 * @note This class assumes that the AST is valid and conforms to the
 * expected syntax and structure. Any errors or inconsistencies in the
 * AST may result in incorrect or incomplete analysis results.
 * 
 * @note This class require the parser to include Comments in the AST.
 */
class DocGen : public AcceptorExtend<DocGen, Visitor> {
  /// @brief The result of the documentation analysis.
  DocumentationResult result;
  /// @brief The current context of the documentation generator.
  DocGenContext context;
  
#include "../../defs/accepts.def"
public:
  DocGen(DocGenContext ctx) : AcceptorExtend(nullptr), 
    context(ctx) {}

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
   */
  void run(std::vector<Syntax::Node*> nodes) {
    for (auto n : nodes) { 
      n->accept(this); 
    }
  }

  /// @brief Returns the result of the documentation analysis.
  /// @return The result of the documentation analysis.
  auto getResult() { return result; }
  /// @brief Returns the path and name preppended to `name`
  /// @param name The name of the page.
  /// @return The path and name preppended to `name`
  std::pair<std::string, std::string> getFullName(std::string name) {
    std::string fullName = "";
    std::string path = "";
    if (!context.currentType.empty()) {
      fullName += context.currentType + "::";
      path += context.currentTypePath + "/";
    } else if (!context.currentNamespace.empty()) {
      fullName += context.currentNamespace + "::";
      path += context.currentNamespacePath + "/";
    } else if (!context.currentModule.empty()) {
      fullName += context.currentModule + "::";
      path += context.currentModulePath + "/";
    } 
    fullName += name;
    path += name;
    return {fullName, path};
  }

  // Default destructor
  ~DocGen() noexcept = default;
};

} // namespace Syntax
} // namespace snowball

#undef ACCEPT

#endif // __SNOWBALL_DOCUMENTATION_GENERATOR_H_
