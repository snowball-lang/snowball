
#include "nodes.h"

#include <assert.h>
#include <string>
#include <vector>

namespace snowball {
namespace Syntax {
namespace Statement {
// Separated namespace in order to use
// Privacy::Status without name conflicts
using Status = Privacy::Status;
Privacy::Privacy(Status status) : status(status) { }
void Privacy::setPrivacy(Status s) { status = s; }
Status Privacy::getPrivacy() const { return status; }
Status Privacy::fromInt(bool p_status) { return static_cast<Status>(!p_status); }
} // namespace Statement
namespace Statement {
FunctionDef::FunctionDef(std::string name, Privacy::Status prvc)
    : AcceptorExtend<FunctionDef, Privacy>(prvc), name(name) { }
std::vector<Expression::Param*> FunctionDef::getArgs() const { return args; }
void FunctionDef::setArgs(std::vector<Expression::Param*> p_args) { args = p_args; }
Expression::TypeRef* FunctionDef::getRetType() const { return retType; };
void FunctionDef::setRetType(Expression::TypeRef* p_type) { retType = p_type; }
bool FunctionDef::isVirtual() { return _virtual; }
void FunctionDef::setVirtual(bool v) { _virtual = v; }
std::string FunctionDef::getName() { return name; }
void FunctionDef::setName(const std::string name) { this->name = name; }
bool FunctionDef::isVariadic() { return variadic; }
void FunctionDef::setVariadic(bool v) { variadic = v; }
bool FunctionDef::isStatic() { return _static; }
void FunctionDef::setStatic(bool s) { _static = s; }
bool FunctionDef::isMutable() { return _mutable; }
void FunctionDef::isMutable(bool m) { _mutable = m; }
void ConstructorDef::setSuperArgs(std::vector<Expression::Base*> args) { superArgs = args; }
void ConstructorDef::setInitArgs(std::map<Expression::Identifier*, Expression::Base*> list) {
    initArgs = list;
}
std::map<Expression::Identifier*, Expression::Base*> ConstructorDef::getInitArgs() const {
    return initArgs;
}
std::vector<Expression::Base*> ConstructorDef::getSuperArgs() const { return superArgs; }
std::vector<Expression::Base*>::iterator ConstructorDef::superArgsBegin() {
    return superArgs.begin();
}
std::vector<Expression::Base*>::iterator ConstructorDef::superArgsEnd() { return superArgs.end(); }
std::map<Expression::Identifier*, Expression::Base*>::iterator ConstructorDef::initArgsBegin() {
    return initArgs.begin();
}
std::map<Expression::Identifier*, Expression::Base*>::iterator ConstructorDef::initArgsEnd() {
    return initArgs.end();
}
Namespace::Namespace(std::string name, std::vector<Node*> body) : body(body), name(name) { }
std::string Namespace::getName() const { return name; }
std::vector<Node*> Namespace::getBody() const { return body; }
ImportStmt::ImportStmt(const std::vector<std::string> path,
                       const std::string package,
                       ImportType ty)
    : path(path), package(package), type(ty){};
VariableDecl::VariableDecl(const std::string& name, Expression::Base* value, bool isMutable)
    : name(name), value(value), _mutable(isMutable){};
bool VariableDecl::isInitialized() { return value != nullptr; }
std::string VariableDecl::getName() const { return name; }
Expression::Base* VariableDecl::getValue() { return value; }
bool VariableDecl::isMutable() { return _mutable; }
Expression::TypeRef* VariableDecl::getDefinedType() { return definedType; }
void VariableDecl::setDefinedType(Expression::TypeRef* t) { definedType = t; }
Return::Return(Expression::Base* value) : value(value){};
Expression::Base* Return::getValue() const { return value; }
DefinedTypeDef::DefinedTypeDef(std::string name, Expression::TypeRef* extends, Privacy::Status prvc, bool _struct)
    : name(name), extends(extends), AcceptorExtend<DefinedTypeDef, Privacy>(prvc), _struct(_struct) { }
void DefinedTypeDef::addFunction(FunctionDef* fnDef) { functions.push_back(fnDef); }
void DefinedTypeDef::addVariable(VariableDecl* var) { variables.push_back(var); }
bool DefinedTypeDef::isStruct() { return _struct; }
Expression::TypeRef* DefinedTypeDef::getParent() const { return extends; }
std::string DefinedTypeDef::getName() const { return name; }
std::vector<FunctionDef*>& DefinedTypeDef::getFunctions() { return functions; }
std::vector<VariableDecl*>& DefinedTypeDef::getVariables() { return variables; }
DefinedTypeDef::FunctionIterator DefinedTypeDef::funcStart() { return functions.begin(); }
DefinedTypeDef::FunctionIterator DefinedTypeDef::funcEnd() { return functions.end(); }
DefinedTypeDef::VariableIterator DefinedTypeDef::varStart() { return variables.begin(); }
DefinedTypeDef::VariableIterator DefinedTypeDef::varEnd() { return variables.end(); }
std::string ImportStmt::getPackage() const { return package; }
std::vector<std::string> ImportStmt::getPath() const { return path; }
std::string ImportStmt::getExportSymbol() const { return exportSymbol; }

} // namespace Statement
} // namespace Syntax
} // namespace snowball
