
#include "snowball/types.h"
#include "snowball/nodes.h"
#include "snowball/token.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"

#include <cstdio>
#include <llvm-10/llvm/IR/Intrinsics.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>

#include <memory>
#include <pthread.h>
#include <sstream>
#include <optional>

namespace snowball {

    llvm::Value* Generator::generate(Node* p_node) {
        switch (p_node->type)
        {
            case Node::Type::CONST_VALUE: {
                return generate_const_value(static_cast<ConstantValue *>(p_node));
            }

            case Node::Type::VAR: {
                return generate_variable_decl(static_cast<VarNode *>(p_node));
            }

            case Node::Type::FUNCTION: {
                return generate_function(static_cast<FunctionNode *>(p_node));
            }

            case Node::Type::OPERATOR: {
                return generate_operator(static_cast<BinaryOp *>(p_node));
            }

            case Node::Type::IDENTIFIER: {
                return generate_identifier(static_cast<IdentifierNode *>(p_node));
            }

            case Node::Type::RETURN: {
                return generate_return(static_cast<ReturnNode *>(p_node));
            }

            case Node::Type::CALL: {
                return generate_call(static_cast<CallNode *>(p_node));
            }

            case Node::Type::TEST: {
                return generate_test(static_cast<TestingNode *>(p_node));
            }

            default:
                DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
                throw Warning(Logger::format("Node with type %s%i%s%s is not yet supported", BCYN, p_node->type, RESET, BOLD), dbg_info);
        }
    }

    llvm::Value* Generator::generate_test(TestingNode* p_node) {
        throw SNError(Error::TODO, "Unit tests are not yet supported");
        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);
        std::string test_name = _testing_context->get_name(_testing_context->addTest(p_node->description));

        auto prototype = llvm::FunctionType::get(_builder.getInt64Ty(), {}, false);
        llvm::Function *function = llvm::Function::Create(prototype, llvm::Function::ExternalLinkage, test_name, _module);

        llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder.getContext(), "body", function);
        _builder.SetInsertPoint(body);

        _enviroment->create_scope(test_name);
        Scope* current_scope = _enviroment->current_scope();

        llvm::Value* value = llvm::ConstantInt::get(_builder.getInt64Ty(), 1);
        std::string test_var_name = Logger::format("_SN__TestCaseN%i_Result", _testing_context->getTestLength());
        auto* alloca = _builder.CreateAlloca (value->getType(), nullptr, test_var_name );

        std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(value)));
        current_scope->set(test_var_name, std::move(scope_value));
        _builder.CreateStore (value, alloca, /*isVolatile=*/false);

        for (Node* node : p_node->block->exprs) {
            generate(node);
        }

        llvm::verifyFunction(*function, &message_stream);
        if (!llvm_error.empty())
            throw SNError(Error::LLVM_INTERNAL, llvm_error);

        _enviroment->delete_scope();
        _builder.CreateRet(value);

        return function;
    }

    llvm::Value* Generator::generate_call(CallNode* p_node) {
        std::string method_name = p_node->method + "(";
        std::vector<std::string> arg_types;
        std::vector<llvm::Value*> args;

        int arg_index = 0;
        for (Node* arg : p_node->arguments) {
            llvm::Value* result = generate(arg);
            arg_types.push_back(result->getType()->getStructName());

            args.push_back(result);
            method_name += result->getType()->getStructName().str();

            if ((p_node->arguments.size() > 1) && (arg_index < (p_node->arguments.size() - 1)))
                method_name += ", ";

            arg_index++;
        }

        method_name += ")";

        std::string base_struct;
        llvm::Value* base_value;
        ScopeValue* class_value;
        if (p_node->base != nullptr) {
            if (dynamic_cast<IdentifierNode*>(p_node->base) != nullptr) {
                class_value = _enviroment->get(dynamic_cast<IdentifierNode*>(p_node->base)->name, p_node->base);

                if (class_value->type != ScopeType::CLASS) {
                    base_value = generate(p_node->base);
                    base_struct = base_value->getType()->getStructName().str();

                    args.insert(args.begin(), base_value);
                    arg_types.insert(arg_types.begin(), base_struct);
                } else {
                    base_struct = dynamic_cast<IdentifierNode*>(p_node->base)->name;
                }
            } else {
                base_value = generate(p_node->base);
                class_value = _enviroment->get(base_value->getType()->getStructName().str(), p_node->base);

                base_struct = base_value->getType()->getStructName().str();

                args.insert(args.begin(), base_value);
                arg_types.insert(arg_types.begin(), base_struct);
            }
        }


        std::string method_call = p_node->base == nullptr ? mangle(p_node->method, arg_types) : GET_FUNCTION_FROM_CLASS(base_struct.c_str(), p_node->method, arg_types);
        ScopeValue* function = _enviroment->get(method_call, p_node, p_node->base != nullptr ? Logger::format("%s.%s", base_struct.c_str(), method_name.c_str()) : method_name);

        if (function->type != ScopeType::FUNC) {
            DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
            throw CompilerError(Error::SYNTAX_ERROR, Logger::format("'%s' is not a function", p_node->method.c_str()), dbg_info);
        }

        ASSERT(args.size() == arg_types.size())
        return _builder.CreateCall(*function->llvm_function, args);
    }

    llvm::Value* Generator::generate_return(ReturnNode* p_node) {
        llvm::Value* value = generate(p_node->value);

        if (value->getType()->getStructName() == p_node->parent->return_type) {
            return _builder.CreateRet(value);
        } else {
            DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
            throw CompilerError(Error::TYPE_ERROR, Logger::format("Mismatched types between '%s' and '%s'", value->getType()->getStructName().str().c_str(), p_node->parent->return_type.c_str()), dbg_info);
        }
    }

    llvm::Value* Generator::generate_identifier(IdentifierNode* p_node) {

        ScopeValue* value = _enviroment->get(p_node->name, p_node);
        switch (value->type)
        {
            case ScopeType::CLASS:
                return (llvm::Value*)(*value->llvm_struct);

            case ScopeType::FUNC:
                return (llvm::Value*)(*value->llvm_function);

            case ScopeType::LLVM:
                return (llvm::Value*)(*value->llvm_value);

            default: {
                DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
                throw CompilerError(Error::BUG, Logger::format("Scope with type ::SCOPE has been fetched in Generator::generate_identifier (idnt: %s).", p_node->name.c_str()), dbg_info);
            }
        }
    }

    llvm::Value* Generator::generate_operator(BinaryOp* p_node) {
        llvm::Value* left = generate(p_node->left);
        llvm::Value* right = generate(p_node->right);

        llvm::Function* function;
        switch (p_node->op_type)
        {
            case OP_POSITIVE:
            case OP_PLUS: {
                function = *_enviroment->get(
                    GET_FUNCTION_FROM_CLASS(
                        left->getType()->getStructName().str().c_str(),
                        "__sum",
                        {
                            left->getType()->getStructName().str(),
                            right->getType()->getStructName().str()
                        }
                    ), p_node, Logger::format(
                        "%s.__sum(%s, %s)",
                            left->getType()->getStructName().str().c_str(),
                            left->getType()->getStructName().str().c_str(),
                            right->getType()->getStructName().str().c_str()
                        )
                    )->llvm_function;
                break;
            }

            default: {
                DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
                throw CompilerError(Error::BUG, Logger::format("The operator with type '%i' has not been handled.", p_node->op_type), dbg_info);
            }
        }

        return _builder.CreateCall(function,
            {left, right});
    }

    llvm::Value* Generator::generate_function(FunctionNode* p_node) {
        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);

        _enviroment->create_scope(p_node->name);
        Scope* current_scope = _enviroment->current_scope();

        ScopeValue* returnType = _enviroment->get(p_node->return_type, p_node);
        auto retType = (p_node->name == _SNOWBALL_FUNCTION_ENTRY && p_node->is_lop_level) ? _builder.getVoidTy() : *returnType->llvm_struct;

        std::vector<std::string> arg_tnames;
        std::vector<llvm::Type*> arg_types;
        for (ArgumentNode* argument : p_node->arguments) {

            // check if type exists
            ScopeValue* value = _enviroment->get(argument->type_name, argument);
            if (value->type != ScopeType::CLASS) {
                DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
                throw CompilerError(Error::ARGUMENT_ERROR, Logger::format("'%s' must be a referece to a class", p_node->name.c_str()), dbg_info);
            }

            llvm::StructType* type = *value->llvm_struct;

            arg_types.push_back(type);
            arg_tnames.push_back(type->getName().str());
        }

        auto prototype = llvm::FunctionType::get(retType, arg_types, false);
        llvm::Function *function = llvm::Function::Create(prototype, llvm::Function::ExternalLinkage, mangle(p_node->name, arg_tnames), _module);

        int parameter_index = 0;
        for (auto& arg : function->args()) {
            std::string name = p_node->arguments.at(parameter_index)->name;
            arg.setName(name);

            std::unique_ptr<ScopeValue*> param_scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(&arg)));
            current_scope->set(name, std::move(param_scope_value));

            parameter_index++;
        }

        llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder.getContext(), "body", function);
        _builder.SetInsertPoint(body);

        for (auto expr : p_node->body->exprs) {
            generate(expr);
        }

        if (body->size() == 0 || !body->back().isTerminator()) {
            if (p_node->name == _SNOWBALL_FUNCTION_ENTRY && p_node->is_lop_level) {
                _builder.CreateRet(nullptr);
            } /* TODO: check if function has type Void */ else {
                DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
                throw CompilerError(Error::FUNCTION_RET_ERR, Logger::format("Function '%s' does not have a return statement ", p_node->name.c_str()), dbg_info);
            }
        }

        llvm::verifyFunction(*function, &message_stream);
        if (!llvm_error.empty())
            throw SNError(Error::LLVM_INTERNAL, llvm_error);

        _enviroment->delete_scope();

        std::unique_ptr<ScopeValue*> func_scopev = std::make_unique<ScopeValue*>(new ScopeValue(std::make_shared<llvm::Function*>(function)));
        _enviroment->current_scope()->set(mangle(p_node->name, arg_tnames), std::move(func_scopev));
        return function;
    }

    llvm::Value* Generator::generate_variable_decl(VarNode* p_node) {
        // TODO: check if variable is global

        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
        Scope* scope = _enviroment->current_scope();

        if (scope->item_exists(p_node->name)) {
            throw CompilerError(Error::VARIABLE_ERROR, Logger::format("'%s' has already been declared", p_node->name.c_str()), dbg_info);
        }

        if (p_node->isGlobal) {
            throw SNError(Error::TODO, "Global variables");
        } else {
            // We asume that the variable only has 1 expression
            llvm::Value* value = generate(p_node->value);
            auto* alloca = _builder.CreateAlloca (value->getType(), nullptr, p_node->name );

            std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(value)));
            scope->set(p_node->name, std::move(scope_value));
            return _builder.CreateStore (value, alloca, /*isVolatile=*/false);
        }

    }

    llvm::Value* Generator::generate_const_value(ConstantValue* p_node) {
        switch (p_node->const_type)
        {
            case TokenType::VALUE_NUMBER: {
                llvm::Type * i64 = get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder);


                ScopeValue* scope_value = _enviroment->get(GET_FUNCTION_FROM_CLASS("Number", "__new", { "i" }), p_node);
                llvm::Function* constructor = const_cast<llvm::Function*>(*scope_value->llvm_function);

                llvm::Constant * num = llvm::ConstantInt::get(i64, (uint64_t)std::stoi(p_node->value));
                return _builder.CreateCall(constructor, { num });
            }

            case TokenType::VALUE_STRING: {
                ScopeValue* scope_value = _enviroment->get(GET_FUNCTION_FROM_CLASS("String", "__new", { "s" }), p_node);
                llvm::Function* constructor = const_cast<llvm::Function*>(*scope_value->llvm_function);

                auto str = p_node->value.c_str();
                auto value = _builder.CreateGlobalStringPtr("str");
                return _builder.CreateCall(constructor, { value });
            }

            default:
                throw SNError(Error::TODO, Logger::format("Const Value with type %s%i%s%s is not yet supported", BCYN, p_node->const_type, RESET, BOLD));
        }
    }

    // utils
    llvm::Value* Generator::convert_to_right_value(llvm::Value* value) {

        std::ostringstream ss_name;

        ss_name << value->getName().str();
        ss_name << ".load";

        return _builder.CreateLoad(value, ss_name.str());
    }
}
