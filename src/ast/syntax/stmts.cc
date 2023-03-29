
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

Privacy::Privacy(Status status) : status(status) {}

void Privacy::setPrivacy(Status s) { status = s; }
Status Privacy::getPrivacy() const { return status; }

Status Privacy::fromInt(int p_status) { return static_cast<Status>(!p_status); }
} // namespace Statement

namespace Statement {

FunctionDef::FunctionDef(std::string name, Privacy::Status prvc)
    : AcceptorExtend<FunctionDef, Privacy>(prvc), name(name) {}

std::vector<ptr<Expression::Param>> FunctionDef::getArgs() const {
    return args;
}
void FunctionDef::setArgs(std::vector<ptr<Expression::Param>> p_args) {
    args = p_args;
}

ptr<Expression::TypeRef> FunctionDef::getRetType() const { return retType; };
void FunctionDef::setRetType(ptr<Expression::TypeRef> p_type) {
    retType = p_type;
}
bool FunctionDef::isVirtual() { return _virtual; }
void FunctionDef::setVirtual(bool v) { _virtual = v; }
std::string FunctionDef::getName() { return name; }
void FunctionDef::setName(const std::string name) { this->name = name; }
bool FunctionDef::isVariadic() { return variadic; }
void FunctionDef::setVariadic(bool v) { variadic = v; }
bool FunctionDef::isStatic() { return _static; }
void FunctionDef::setStatic(bool s) { _static = s; }
ImportStmt::ImportStmt(const std::vector<std::string> path,
                       const std::string package, ImportType ty)
    : path(path), package(package), type(ty){};
std::vector<ptr<Expression::Param>> GenericContainer::getGenerics() const {
    return generics;
}
void GenericContainer::setGenerics(GenericList list) {
    generics = std::move(list);
}

VariableDecl::VariableDecl(const std::string& name, ptr<Expression::Base> value,
                           bool isMutable)
    : name(name), value(value), _mutable(isMutable){};

std::string VariableDecl::getName() const { return name; }
ptr<Expression::Base> VariableDecl::getValue() { return value; }
bool VariableDecl::isMutable() { return _mutable; }
ptr<Expression::TypeRef> VariableDecl::getDefinedType() { return definedType; }
void VariableDecl::setDefinedType(ptr<Expression::TypeRef> t) {
    definedType = t;
}

Return::Return(ptr<Expression::Base> value) : value(value){};
ptr<Expression::Base> Return::getValue() const { return value; }

ClassDef::ClassDef(std::string name, ptr<Expression::TypeRef> extends,
                   Privacy::Status prvc)
    : name(name), extends(extends), AcceptorExtend<ClassDef, Privacy>(prvc) {}
void ClassDef::addFunction(ptr<FunctionDef> fnDef) {
    functions.push_back(fnDef);
}
void ClassDef::addVariable(ptr<VariableDecl> var) { variables.push_back(var); }
ptr<Expression::TypeRef> ClassDef::getParent() const { return extends; }
std::string ClassDef::getName() const { return name; }
std::vector<ptr<FunctionDef>>& ClassDef::getFunctions() { return functions; }
std::vector<ptr<VariableDecl>>& ClassDef::getVariables() { return variables; }
ClassDef::FunctionIterator ClassDef::funcStart() { return functions.begin(); }
ClassDef::FunctionIterator ClassDef::funcEnd() { return functions.end(); }
ClassDef::VariableIterator ClassDef::varStart() { return variables.begin(); }
ClassDef::VariableIterator ClassDef::varEnd() { return variables.end(); }
std::string ImportStmt::getPackage() const { return package; }
std::vector<std::string> ImportStmt::getPath() const { return path; }
std::string ImportStmt::getExportSymbol() const { return exportSymbol; }

} // namespace Statement
} // namespace Syntax
} // namespace snowball
