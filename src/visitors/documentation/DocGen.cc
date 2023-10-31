
#include "DocGen.h"
#include "DocTemplates.h"
#include "../../services/OperatorService.h"
#include <optional>

namespace snowball {
namespace Syntax {

using Operator = services::OperatorService;

SN_DOCGEN_VISIT(Block) {}
SN_DOCGEN_VISIT(Macro) {}

SN_DOCGEN_VISIT(Expression::ConstantValue) {}
SN_DOCGEN_VISIT(Expression::FunctionCall) {}
SN_DOCGEN_VISIT(Expression::Identifier) {}
SN_DOCGEN_VISIT(Expression::GenericIdentifier) {}
SN_DOCGEN_VISIT(Expression::Index) {}
SN_DOCGEN_VISIT(Expression::TypeRef) {}
SN_DOCGEN_VISIT(Expression::Cast) {}
SN_DOCGEN_VISIT(Expression::NewInstance) {}
SN_DOCGEN_VISIT(Expression::BinaryOp) {}
SN_DOCGEN_VISIT(Expression::LambdaFunction) {}
SN_DOCGEN_VISIT(Expression::PseudoVariable) {}

SN_DOCGEN_VISIT(Statement::TypeAlias) {}
SN_DOCGEN_VISIT(Statement::Raise) {}
SN_DOCGEN_VISIT(Statement::WhileLoop) {}
SN_DOCGEN_VISIT(Statement::TryCatch) {}
SN_DOCGEN_VISIT(Statement::Return) {}
SN_DOCGEN_VISIT(Statement::ImportStmt) {}
SN_DOCGEN_VISIT(Statement::ForLoop) {}
SN_DOCGEN_VISIT(Statement::Conditional) {}
SN_DOCGEN_VISIT(Statement::LoopFlow) {}  

SN_DOCGEN_VISIT(Statement::VariableDecl) {} // TODO:

SN_DOCGEN_VISIT(Statement::Namespace) {
    auto [name, path] = getFullName(p_node->getName());
    auto backup = context.currentNamespace;
    context.currentNamespace = p_node->getName();
    for (auto& stmt : p_node->getBody()) { stmt->accept(this); }

    auto newPage = DocumentationPage {
        .name = name,
        .path = path,
        .type = DocumentationPage::Type::Namespace,
    };

    // TODO:
    newPage.html = "";

    result.pages.push_back(newPage);
    context.currentNamespace = backup;
}

SN_DOCGEN_VISIT(Statement::DefinedTypeDef) {
    auto [name, path] = getFullName(p_node->getName());    
    
    auto backup = context.currentType;
    if (context.currentType.empty())
        context.currentType = name;
    else context.currentType += "::" + name;
    for (auto& func : p_node->getFunctions()) { func->accept(this); }

    context.currentType = backup;
    auto newPage = DocumentationPage {
        .name = name,
        .path = path,
        .type = DocumentationPage::Type::Type,
    };

    // TODO:
    newPage.html = "";

    result.pages.push_back(newPage);
}

SN_DOCGEN_VISIT(Statement::FunctionDef) {
    auto rawName = p_node->getName();
    if (Operator::isOperator(rawName)) 
        rawName = "-" + Operator::operatorName(Operator::operatorID(rawName));
    auto [name, path] = getFullName(rawName);

    auto newPage = DocumentationPage {
        .name = name,
        .path = path,
        .type = DocumentationPage::Type::Function,
    };

    // TODO: add html here!
    newPage.html = "";

    result.pages.push_back(newPage);
}

} // namespace Syntax
} // namespace snowball
