
#include "snowball/libs.h"

#include "snowball/types.h"
#include "snowball/nodes.h"
#include "snowball/token.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"
#include "snowball/operators.h"

#include <cstdio>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

#include <memory>
#include <pthread.h>
#include <sstream>
#include <optional>
#include <fstream>

#include <dlfcn.h>

namespace snowball {

    llvm::Value* Generator::generate(Node* p_node) {
        switch (p_node->type)
        {
            case Node::Ty::CONST_VALUE: {
                return generate_const_value(static_cast<ConstantValue *>(p_node));
            }

            case Node::Ty::MODULE: {
                return generate_module(static_cast<ModuleNode *>(p_node));
            }

            case Node::Ty::ATTRIBUTE: {
                return generate_attribute(static_cast<AttributeNode *>(p_node));
            }

            case Node::Ty::CAST: {
                return generate_cast(static_cast<CastNode *>(p_node));
            }

            case Node::Ty::VAR: {
                return generate_variable_decl(static_cast<VarNode *>(p_node));
            }

            case Node::Ty::INDEX: {
                return generate_index(static_cast<IndexNode *>(p_node));
            }

            case Node::Ty::FUNCTION: {
                return generate_function(static_cast<FunctionNode *>(p_node));
            }

            case Node::Ty::OPERATOR: {
                return generate_operator(static_cast<BinaryOp *>(p_node));
            }

            case Node::Ty::IDENTIFIER: {
                return generate_identifier(static_cast<IdentifierNode *>(p_node));
            }

            case Node::Ty::RETURN: {
                return generate_return(static_cast<ReturnNode *>(p_node));
            }

            case Node::Ty::CALL: {
                return generate_call(static_cast<CallNode *>(p_node));
            }

            case Node::Ty::CLASS: {
                return generate_class(static_cast<ClassNode *>(p_node));
            }

            case Node::Ty::IMPORT: {
                return generate_import(static_cast<ImportNode *>(p_node));
            }

            case Node::Ty::NEW_CALL: {
                return generate_new(static_cast<NewNode *>(p_node));
            }

            case Node::Ty::IF_STMT: {
                return generate_if_stmt(static_cast<IfStatementNode *>(p_node));
            }

            case Node::Ty::BLOCK: {
                return generate_block(static_cast<BlockNode *>(p_node));
            }

            case Node::Ty::OPERATOR_OVERRIDE: {
                return generate_operator(static_cast<OperatorNode *>(p_node));
            }

            case Node::Ty::TERNARY: {
                return generate_ternary(static_cast<TernaryOperator *>(p_node));
            }

            default:
                COMPILER_ERROR(BUG, Logger::format("Node with type %s%i%s%s is not yet supported", BCYN, p_node->type, RESET, BOLD));
        }
    }
}