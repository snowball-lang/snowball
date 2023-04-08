
#include "../DefiniteAssigment.h"

namespace snowball {
namespace Syntax {


SN_DEFINITE_ASSIGMENT_VISIT(Expression::ConstantValue) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::FunctionCall) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::Identifier) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::GenericIdentifier) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::Index) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::TypeRef) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::Cast) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::NewInstance) {}
SN_DEFINITE_ASSIGMENT_VISIT(Expression::BinaryOp) {}

SN_DEFINITE_ASSIGMENT_VISIT(Statement::Return) {}
SN_DEFINITE_ASSIGMENT_VISIT(Statement::VariableDecl) {}
SN_DEFINITE_ASSIGMENT_VISIT(Statement::ClassDef) {}
SN_DEFINITE_ASSIGMENT_VISIT(Statement::ImportStmt) {}
SN_DEFINITE_ASSIGMENT_VISIT(Statement::FunctionDef) {}

}
}
