

#include "../../ast/syntax/nodes.h"
#include "../../ast/types/DefinedType.h"
#include "../../ast/types/FunctionType.h"
#include "../../ast/visitor/Visitor.h"
#include "../../utils/utils.h"

#include <assert.h>
#include <memory>
#include <string>
#include <vector>

#include "DocGen.h"

#ifndef __SNOWBALL_DOCUMENTATION_GENERATOR_TEMPLATES_H_
#define __SNOWBALL_DOCUMENTATION_GENERATOR_TEMPLATES_H_

namespace snowball {
namespace Syntax {

static const std::string pageTemplate = "\
\
";

/**
 * @brief Creates a documentation page for a function.
 * 
 * This function creates a documentation page for a function.
 * 
 * @param node The function definition node.
 * @param context The documentation generator context.
 * @return std::string The documentation page.
 * @ingroup docgen
*/
std::string createFunctionPage(Statement::FunctionDef node, DocGenContext context);

} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_DOCUMENTATION_GENERATOR_TEMPLATES_H_

