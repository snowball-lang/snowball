

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
namespace docgen {

static const std::string pageTemplate = R"(
<!DOCTYPE html>
<html>
<head>
    <title>%s</title>
    <link rel="stylesheet" href="https://snowball-lang.github.io/autodoc-styles/styles.css">

    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/styles/atom-one-dark.min.css">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/highlight.min.js"></script>

    <!-- and it's easy to individually load additional languages -->
    <script src="https://snowball-lang.github.io/autodoc-styles/highlight.min.js"></script>
</head>
<body>
    <sidenav>
        <h1>
            %s 
        </h1>
        <hr />
        %s
    </sidenav>
    <main>
        %s
    </main>

    <script>hljs.highlightAll();</script>
</body>
</html>
)";

std::string getPageTemplate(DocGenContext context, std::string title, std::string body, std::vector<std::pair<std::string, std::string>> links = {});

std::string typeToHtml(Expression::TypeRef* type);

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
void createFunctionPage(Statement::FunctionDef* node, DocGenContext context, DocumentationPage& page);
/**
 * @brief Creates a documentation page for a type.
 * 
 * @param node The type definition node.
 * @param context The documentation generator context.
 * @return DocumentationPage The documentation page.
*/
void createTypePage(Statement::DefinedTypeDef* node, DocGenContext context, DocumentationPage& page);

} // namespace docgen
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_DOCUMENTATION_GENERATOR_TEMPLATES_H_

