
#include "snowball/types.h"
#include "snowball/nodes.h"
#include "snowball/token.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

#include <optional>

namespace snowball {
    llvm::Value* Generator::generate(Node p_node) {
        switch (p_node.type)
        {
            case Node::Type::CONST_VALUE: {
                return generate_const_value(p_node);
            }

            case Node::Type::VAR: {
                return generate_variable_decl(p_node);
            }

            case Node::Type::FUNCTION: {
                return generate_function(p_node);
            }

            default:
                DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node.pos, p_node.width);
                throw Warning(Logger::format("Node with type %s%i%s%s is not yet supported", BCYN, p_node.type, RESET, BOLD), dbg_info);
        }
    }

    llvm::Value* Generator::generate_function(Node p_node) {
        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);

        _enviroment->create_scope(p_node.name);

        auto retType = _builder.getVoidTy();
        auto prototype = llvm::FunctionType::get(retType, false);
        llvm::Function *function = llvm::Function::Create(prototype, llvm::Function::ExternalLinkage, p_node.name, _module);

        llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder.getContext(), "body", function);
        _builder.SetInsertPoint(body);

        for (auto expr : p_node.exprs.at(0).exprs) {
            generate(expr);
        }

        if (body->size() == 0 || !body->back().isTerminator()) {
            _builder.CreateRet(nullptr);
        }

        llvm::verifyFunction(*function, &message_stream);
        if (!llvm_error.empty())
            throw SNError(Error::LLVM_INTERNAL, llvm_error);

        _enviroment->delete_scope();
        return function;
    }

    llvm::Value* Generator::generate_variable_decl(Node p_node) {
        // TODO: check if variable is global
        // TODO: add it to the enviroment

        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node.pos, p_node.width);
        Scope* scope = _enviroment->current_scope();

        bool _value = scope->item_exists(p_node.name);
        DUMP(_value)
        if (_value) {
            throw CompilerError(Error::VARIABLE_ERROR, Logger::format("'%s' has already been declared", p_node.name.c_str()), dbg_info);
        }

        // We asume that the variable only has 1 expression
        llvm::Value* value = generate(p_node.exprs.at(0));
        auto* alloca = _builder.CreateAlloca (value->getType(), nullptr, p_node.name );

        ScopeValue scope_value;
        scope_value.type = ScopeType::LLVM;
        scope_value.llvm_value = value;

        scope->set(p_node.name, scope_value);
        return _builder.CreateStore (value, alloca, /*isVolatile=*/false);
    }

    llvm::Value* Generator::generate_const_value(Node p_node) {
        switch (p_node.const_type)
        {
            case TokenType::VALUE_NUMBER: {
                llvm::Type * i64 = get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder);

                llvm::Constant * num = llvm::ConstantInt::get(i64, (uint64_t)std::stoi(p_node.value));
                return _builder.CreateCall(_buildin_types.sn_number_class, num);
            }

            default:
                throw SNError(Error::TODO, Logger::format("Const Value with type %s%i%s%s is not yet supported", BCYN, p_node.const_type, RESET, BOLD));
        }
    }
}
