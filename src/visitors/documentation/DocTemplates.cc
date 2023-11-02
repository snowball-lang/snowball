
#include "DocGen.h"
#include "DocTemplates.h"
#include "../../services/OperatorService.h"
#include <optional>

namespace snowball {
namespace Syntax {
namespace docgen {

std::string getPageTemplate(DocGenContext context, std::string title, std::string body, std::vector<std::pair<std::string, std::string>> links) {
    std::string parent;
    std::string parentPath;
    if (!context.currentType.empty()) {
        parent = context.currentType;
        parentPath = context.currentTypePath;
    } else if (!context.currentNamespace.empty()) {
        parent = context.currentNamespace;
        parentPath = context.currentNamespacePath;
    } else {
        parent = context.currentModule; 
        parentPath = context.currentModulePath;
    }

    links.insert(links.begin(), {"< Go Back", parentPath});
    std::string linksHTML = "";
    for (auto& [name, link] : links) {
        linksHTML += "<a href=\"" + link + ".html\">" + name + "</a>";
    }

    return FMT(pageTemplate.c_str(), title.c_str(), context.baseURL.c_str(), parent.c_str(), linksHTML.c_str(), body.c_str());
}

namespace {
std::string generateFromBase(Expression::Base* ast) {
    if (auto x = utils::cast<Expression::Identifier>(ast)) {
        auto n = x->getIdentifier();
        if (auto generics = utils::cast<Expression::GenericIdentifier>(x)) {
            n += "<";
            for (auto& g : generics->getGenerics()) {
                n += typeToHtml(g) + ", ";
            }
            if (generics->getGenerics().size() > 0)
                n = n.substr(0, n.size() - 2);
            n += ">";
        }
        return n;
    } else if (auto x = utils::cast<Expression::Index>(ast)) {
        auto base = x->getBase();
        auto identifier = x->getIdentifier();
        return generateFromBase(base) + "::" + generateFromBase(identifier);
    }
    assert(false);    
}

std::string sanitize(std::string s) {
    auto str = s;
    utils::replaceAll(str, "<", "&lt;");
    utils::replaceAll(str, ">", "&gt;");
    utils::replaceAll(str, "\n", "<br/>");
    auto trimed = s;
    utils::replaceAll(trimed, " ", "");
    if (str == "<br/>") return "";
    return "<br/>" + str;
}

std::string getFunctionCode(Statement::FunctionDef* node) {
    std::string body;
    if (node->isExtern()) body += "external ";
    if (node->isMutable()) body += "mut ";
    if (node->isPublic()) body += "public ";
    if (node->isPrivate()) body += "private ";
    if (node->isVirtual()) body += "virtual ";
    if (node->isStatic()) body += "static ";
    if (node->hasAttribute(Attributes::UNSAFE)) body += "unsafe ";
    bool isOperator = Operator::isOperator(node->getName());
    if (isOperator) {
        body += "operator func ";
        body += Operator::operatorName(Operator::operatorID(node->getName()));
    } else {
        body += "func " + node->getName();
    }

    if (node->isGeneric()) {
        body += "<";
        for (auto& generic : node->getGenerics()) {
            body += generic->getName();
            if (generic->getType()) {
                body += " = " + typeToHtml(generic->getType());
            }
            body += ", ";
        }
        // remove the last ", "
        if (node->getGenerics().size() > 0)
            body = body.substr(0, body.size() - 2);
        body += ">";
    }
    body += "(\n";
    for (auto& param : node->getArgs()) {
        body += "    " + param->getName() + ": " + typeToHtml(param->getType()) + ",\n";
    }

    if (node->isVariadic()) {
        body += "    ...,\n";
    }

    // remove the last ",<br>"
    if (utils::endsWith(body, ",\n"))
        body = body.substr(0, body.size() - 2);
    if (node->isVariadic() || node->getArgs().size() > 0)
        body += "\n";
    else body = body.substr(0, body.size() - 1);
    body += ") " + typeToHtml(node->getRetType()) + " { ... }";
    return body;
}

void createSmallPictureFn(Statement::FunctionDef* node, DocGenContext context, std::string& body) {
    body += "<pre><code style=\"background: transparent !important; padding: 5px 0 !important;\" class=\"language-snowball\">";
    body += getFunctionCode(node);
    body += "</code></pre>";
    if (auto comment = node->getComment()) {
        auto values = comment->getValues();
        if (values.count("brief")) {
            body += "<p style=\"margin-left: 15px; transform: translateY(-50%);\">" + sanitize(values["brief"]) + "</p>";
        }
    }
}
}

std::string typeToHtml(Expression::TypeRef* type) {
    if (type->isReferenceType()) {
        return (type->isMutable() ? "&mut " : "&") + typeToHtml(utils::cast<Expression::ReferenceType>(type)->getBaseType());
    } else if (type->isPointerType()) {
        return (type->isMutable() ? "*mut " : "*const ") + typeToHtml(utils::cast<Expression::PointerType>(type)->getBaseType());
    } else if (type->isFunctionType()) {
        auto funcType = utils::cast<Expression::FuncType>(type);
        std::string result = "func (";
        for (auto& param : funcType->getArgs()) {
            result += typeToHtml(param) + ", ";
        }
        // remove the last ", "
        result = result.substr(0, result.size() - 2);
        result += ") -> " + typeToHtml(funcType->getReturnValue());
        return result;
    } else if (type->isTypeDecl()) {
        return "decltype(...)";
    }

    auto ast = type->_getInternalAST();
    return ast ? generateFromBase(ast) : type->getName();
}

void createFunctionPage(Statement::FunctionDef* node, DocGenContext context, DocumentationPage& page) {

    std::string body = "";
    body += "<h1>";

    auto pathParts = page.path;
    auto nameParts = utils::list2vec(utils::split(page.name, "::"));
    int i = 0;
    for (auto _:pathParts) {
        std::string url = "";
        int j = 0;
        for (auto& part : pathParts) {
            if (j == i) {
                url += part.string();
                if (utils::endsWith(part.string(), ".html"))
                    url = url.substr(0, url.size() - 5);
                break;
            } else {
                url += part.string() + "/";
            }
            j++;
        }
        body += "<a style=\"color:#78d3fc;\" href=\"" + url + ".html\">" + nameParts[i] + "</a>::";
        i++;
    }
    body = body.substr(0, body.size() - 2) + ";"; // remove the last "::"
    body += "</h1><hr/><div><pre><code class=\"language-snowball\">";

    body += getFunctionCode(node);

    body += "</code></pre></div><br><div class=\"doc\">";

    if (auto docString = node->getComment()) {
        auto values = docString->getValues();
        if (values.count("brief")) {
            body += "<h1 style=\"color:#78d3fc;\">Brief Description for <quote>" + node->getName() + "</quote></h1>";
            body += "<p>" + sanitize(values["brief"]) + "</p>";
        }
        auto fnBody = sanitize(docString->getBody());
        if (!fnBody.empty())
            body += "<p>" + fnBody + "</p>";

        std::vector<std::pair<std::string, std::string>> params;
        for (auto& [tag, value] : values) {
            if (utils::startsWith(tag, "param$")) {
                params.push_back({tag, value});
            }
        }

        if (params.size() > 0) {
            body += "<hr/><h1 style=\"color:#78d3fc;\">Parameters</h1><br/>";
            for (auto& [tag, value] : params) {
                auto idx = tag.find_first_of("$");
                auto paramIdx = std::stoi(tag.substr(idx + 1));
                std::string paramName = "";

                if (utils::startsWith(value, "[in]")) {
                    value = value.substr(4);
                } else if (utils::startsWith(value, "[out]")) {
                    value = value.substr(5);
                } else if (utils::startsWith(value, "[in,out]")) {
                    value = value.substr(8);
                }

                auto words = utils::list2vec(utils::split(value, " "));
                if (words.size() > 0) {
                    for (auto& word : words) {
                        if (word.empty()) continue;
                        paramName = word;
                        break;
                    }
                    value = value.substr(paramName.size() + 1);
                }

                body += "<h1>" + paramName + "</h1>";
                body += "<p>" + value + "</p>";
            }
        }

        for (auto& [tag, value] : values) {
            if (tag == "brief") continue;
            if (utils::startsWith(tag, "param$")) continue;
            body += "<hr/><h1 style=\"color:#78d3fc;\">@" + tag + "</h1>";
            body += "<p>" + value + "</p>";
        }
    }

    body += "<br/><br/></div>";

    page.html = getPageTemplate(context, page.name, body);
}

void createTypePage(Statement::DefinedTypeDef* node, DocGenContext context, DocumentationPage& page) {
    std::string body = "";
    body += "<h1>";

    auto pathParts = page.path;
    auto nameParts = utils::list2vec(utils::split(page.name, "::"));
    int i = 0;
    for (auto _:pathParts) {
        std::string url = "";
        int j = 0;
        for (auto& part : pathParts) {
            if (j == i) {
                url += part.string();
                if (utils::endsWith(part.string(), ".html"))
                    url = url.substr(0, url.size() - 5);
                break;
            } else {
                url += part.string() + "/";
            }
            j++;
        }
        body += "<a style=\"color:#78d3fc;\" href=\"" + url + ".html\">" + nameParts[i] + "</a>::";
        i++;
    }
    body = body.substr(0, body.size() - 2) + ";"; // remove the last "::"
    body += "</h1><hr/><div><pre><code class=\"language-snowball\">";

    if (node->isPrivate()) body += "private ";
    if (node->isPublic()) body += "public ";

    if (node->isInterface()) body += "interface ";
    else if (node->isStruct()) body += "struct ";
    else body += "class ";
    
    body += node->getName();

    if (node->isGeneric()) {
        body += "<";
        for (auto& generic : node->getGenerics()) {
            body += generic->getName();
            if (generic->getType()) {
                body += " = " + typeToHtml(generic->getType());
            }
            body += ", ";
        }
        // remove the last ", "
        if (node->getGenerics().size() > 0)
            body = body.substr(0, body.size() - 2);
        body += ">";
    }

    std::vector<Statement::VariableDecl*> publicMembers;
    for (auto& field : node->getVariables()) {
        if (field->isPublic())
            publicMembers.push_back(field);
    }

    if (node->getParent()) {
        body += "\n    extends " + typeToHtml(node->getParent());
    }

    if (node->getImpls().size() > 0) {
        body += "\n    implements ";
        for (auto& impl : node->getImpls()) {
            body += typeToHtml(impl) + ", ";
        }
        // remove the last ", "
        body = body.substr(0, body.size() - 2);
    }

    if (publicMembers.size() > 0) 
        body += " { \npublic:";
    else body += " { \n";
    for (auto& field : publicMembers) {
        if (field->getComment()) {
            auto values = field->getComment()->getValues();
            for (auto& [tag, value] : values) {
                body += "\n    // @" + tag + " " + value;
            }

            auto fnBody = sanitize(field->getComment()->getBody());
            if (!fnBody.empty())
                for (auto& line : utils::list2vec(utils::split(fnBody, "<br/>")))
                    body += "\n    // " + line;
        }
        body += "\n    " + (std::string)(field->isContantDecl() ? "const " : "let ") + field->getName() + ": " + typeToHtml(field->getDefinedType()) + ";\n";
    }
    if (utils::endsWith(body, ",\n"))
        body = body.substr(0, body.size() - 2);
    if (publicMembers.size() < node->getVariables().size())
        body += "private:\n    // ... private fields\n";
    body += "};</code></pre></div><br><div class=\"doc\">";

    if (auto docString = node->getComment()) {
        auto values = docString->getValues();
        if (values.count("brief")) {
            body += "<h1 style=\"color:#78d3fc;\">Brief Description for <quote>" + node->getName() + "</quote></h1>";
            body += "<p>" + sanitize(values["brief"]) + "</p>";
        }
        body += "<p>" + sanitize(docString->getBody()) + "</p>";

        for (auto& [tag, value] : values) {
            if (tag == "brief") continue;
        }
    }

    if (node->getFunctions().size() > 0) {
        std::vector<Statement::FunctionDef*> publicFunctions;
        std::vector<Statement::FunctionDef*> publicStaticFunctions;
        std::vector<Statement::FunctionDef*> privateFunctions;
        std::vector<Statement::FunctionDef*> privateStaticFunctions;

        for (auto& func : node->getFunctions()) {
            if (func->isPublic()) {
                if (func->isStatic()) publicStaticFunctions.push_back(func);
                else publicFunctions.push_back(func);
            } else {
                if (func->isStatic()) privateStaticFunctions.push_back(func);
                else privateFunctions.push_back(func);
            }
        }

        if (publicFunctions.size() > 0) {
            body += "<hr/><h1 style=\"color:#78d3fc;\">Public Functions</h1>";
            for (auto& func : publicFunctions) {
                createSmallPictureFn(func, context, body);
            }
        }
        
        if (publicStaticFunctions.size() > 0) {
            body += "<hr/><h1 style=\"color:#78d3fc;\">Public Static Functions</h1>";
            for (auto& func : publicStaticFunctions) {
                createSmallPictureFn(func, context, body);
            }
        }

        if (privateFunctions.size() > 0) {
            body += "<hr/><h1 style=\"color:#78d3fc;\">Private Functions</h1>";
            for (auto& func : privateFunctions) {
                createSmallPictureFn(func, context, body);
            }
        }

        if (privateStaticFunctions.size() > 0) {
            body += "<hr/><h1 style=\"color:#78d3fc;\">Private Static Functions</h1>";
            for (auto& func : privateStaticFunctions) {
                createSmallPictureFn(func, context, body);
            }
        }
    }

    body += "</div>";

    std::vector<std::pair<std::string, std::string>> links;

    for (auto& func : node->getFunctions()) {
        auto name = func->getName();
        bool isOperator = false;
        if (Operator::isOperator(name)) {
            isOperator = true;
            name = "-" + Operator::operatorName(Operator::operatorID(name));
        }

        std::string link = page.path.string();
        link = link.substr(0, link.size() - 5); // remove ".html"
        link += "/" + name;
        links.push_back({isOperator ? name.substr(1) : name, link});
    }

    page.html = getPageTemplate(context, page.name, body, links);
}

} // namespace docgen
} // namespace Syntax
} // namespace snowball
