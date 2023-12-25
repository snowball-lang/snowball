

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

    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/styles/atom-one-light.min.css">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/highlight.min.js"></script>

    <script src="https://cdnjs.cloudflare.com/ajax/libs/showdown/2.1.0/showdown.min.js" integrity="sha512-LhccdVNGe2QMEfI3x4DVV3ckMRe36TfydKss6mJpdHjNFiV07dFpS2xzeZedptKZrwxfICJpez09iNioiSZ3hA==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
    <script src="https://snowball-lang.github.io/autodoc-styles/md2html.js"></script>

    <script src="https://snowball-lang.github.io/autodoc-styles/highlight.min.js"></script>

    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Poppins:wght@400;500;600;700&display=swap" rel="stylesheet">

    <base href="%s">
</head>
<body>
    <sidenav>
        <h1 style="display: flex; align-items: center;">
            %s <span class="tag">version %s</span>
        </h1>
        <hr />
        %s
    </sidenav>
    <main>
        %s
    </main>
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
/**
 * @brief Creates a documentation page for a module.
 * 
 * @param nodes The nodes in the module.
 * @param context The documentation generator context.
 * @return DocumentationPage The documentation page.
 * @ingroup docgen
 */
void createModulePage(std::vector<Syntax::Node*> nodes, DocGenContext context, DocumentationPage& page);
/**
 * @brief Creates a documentation page for a macro.
 * 
 * @param node The macro node.
 * @param context The documentation generator context.
 * @return DocumentationPage The documentation page.
 * @ingroup docgen
 */
void createMacroPage(Macro* node, DocGenContext context, DocumentationPage& page);
/**
 * @brief Creates a documentation page for a namespace.
 * 
 * @param node The namespace node.
 * @param context The documentation generator context.
 * @param page The documentation page.
 * @return DocumentationPage The documentation page.
 * @ingroup docgen
 */
void createNamespacePage(Statement::Namespace* node, DocGenContext context, DocumentationPage& page);
/**
 * @brief Creates a documentation page for a variable.
 * 
 * @param node The variable node.
 * @param context The documentation generator context.
 * @param page The documentation page.
 * @return DocumentationPage The documentation page.
 * @ingroup docgen
 */
void createVariablePage(Statement::VariableDecl* node, DocGenContext context, DocumentationPage& page);
/**
 * @brief Creates a documentation page for the module index.
 * 
 * @param modules The modules in the program.
 * @param context The documentation generator context.
 * @param page The documentation page.
 * @return DocumentationPage The documentation page.
*/
void createRootPage(std::vector<std::string> modules, DocGenContext context, DocumentationPage& page);
/**
 * @brief Creates a documentation page for a type alias.
 * 
 * @param node The type alias node.
 * @param context The documentation generator context.
 * @param page The documentation page.
*/
void createTypeAliasPage(Statement::TypeAlias* node, DocGenContext context, DocumentationPage& page);

} // namespace docgen
} // namespace Syntax
} // namespace snowball

#endif // __SNOWBALL_DOCUMENTATION_GENERATOR_TEMPLATES_H_

