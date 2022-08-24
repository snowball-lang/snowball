
#include "snowball/libs.h"

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
#include <fstream>

#include <dlfcn.h>


#define SET_TO_SCOPE_OR_CLASS(_name, value) \
    if (_context._current_class != nullptr) { \
        _enviroment->get(_context._current_class->name, nullptr)->scope_value->set(_name, std::move(value)); \
    } else if (_context._current_module != nullptr) { \
        _context._current_module->scope_value->set(_name, std::move(value)); \
    } else { \
        _enviroment->current_scope()->set(_name, std::move(value)); \
    }

#define SET_TO_GLOBAL_OR_CLASS(_name, value) \
    if (_context._current_class != nullptr) { \
        _enviroment->get(_context._current_class->name, nullptr)->scope_value->set(_name, std::move(value)); \
    } else if (_context._current_module != nullptr) { \
        _context._current_module->scope_value->set(_name, std::move(value)); \
    } else { \
        _enviroment->global_scope()->set(_name, std::move(value)); \
    }

#define COMPILER_ERROR(error, message) \
    DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width); \
    throw CompilerError(Error::error, message, dbg_info);


#define GET_BOOL_VALUE(ret, __v) \
    llvm::Type* __ty = TypeChecker::type2llvm(_builder, __v->getType());\
    std::string  __tys = TypeChecker::get_type_name(__ty); \
    if (TypeChecker::is_number(__ty)) { \
        __v =  _builder.CreateICmpEQ(__v, llvm::ConstantInt::get(__v->getType(), 1)); \
    } else if (__tys != BOOL_TYPE->mangle()) { \
        llvm::Value* __c = *_enviroment->get(GET_FUNCTION_FROM_CLASS(__tys.c_str(), "__bool", {TypeChecker::to_type(__tys).first}, true), p_node, Logger::format("%s.__bool(self)", __tys.c_str()))->llvm_function; \
        __v = _builder.CreateCall(__c, {__v}); \
    } \
    llvm::Value* ret = __v;

#define CALL_OPERATOR(method) \
    function = *_enviroment->get( \
    GET_FUNCTION_FROM_CLASS( \
        TypeChecker::get_type_name(left_type).c_str(), \
        method, \
        { \
            TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first, \
            TypeChecker::to_type(TypeChecker::get_type_name(right_type)).first \
        }, \
        true \
    ), p_node, Logger::format( \
        "%s." method "(%s, %s)", \
            TypeChecker::get_type_name(left_type).c_str(), \
            TypeChecker::get_type_name(left_type).c_str(), \
            TypeChecker::get_type_name(right_type).c_str() \
        ) \
    )->llvm_function;

#define MODULE_NAME_IF_EXISTS(_sufix) (_context._current_module != nullptr ? (_context._current_module->module_name + _sufix) : "")
#define ADD_MODULE_NAME_IF_EXISTS() MODULE_NAME_IF_EXISTS(".") +

#define CALL_UNARY_OPERATOR(method) \
    function = *_enviroment->get( \
    GET_FUNCTION_FROM_CLASS( \
        TypeChecker::get_type_name(left_type).c_str(), \
        method, \
        { \
            TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first \
        }, \
        true \
    ), p_node, Logger::format( \
        "%s." method "(self)", \
            TypeChecker::get_type_name(left_type).c_str() \
        ) \
    )->llvm_function;

#define FUNCTION_CALL_NOT_FOUND() \
    if (private_method_exists) { \
        COMPILER_ERROR(\
            VARIABLE_ERROR,\
            Logger::format("Function named '%s' is a private method that can't be accessed outside it's class or module",\
                p_node->base != nullptr ?\
                    Logger::format("%s.%s", base_struct.c_str(), method_name.c_str()).c_str()\
                    : method_name.c_str()\
            )\
        )\
    } else {\
        COMPILER_ERROR(\
            VARIABLE_ERROR,\
            Logger::format("No function found with name: %s",\
                p_node->base != nullptr ?\
                    Logger::format("%s.%s", base_struct.c_str(), method_name.c_str()).c_str()\
                    : method_name.c_str()\
            )\
        )\
    }

namespace snowball {

    llvm::Value* Generator::generate(Node* p_node) {
        switch (p_node->type)
        {
            case Node::Ty::CONST_VALUE: {
                return generate_const_value(static_cast<ConstantValue *>(p_node));
            }

            case Node::Ty::VAR: {
                return generate_variable_decl(static_cast<VarNode *>(p_node));
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

            case Node::Ty::TEST: {
                return generate_test(static_cast<TestingNode *>(p_node));
            }

            case Node::Ty::ASSERT: {
                return generate_assert(static_cast<AssertNode *>(p_node));
            }

            case Node::Ty::IF_STMT: {
                return generate_if_stmt(static_cast<IfStatementNode *>(p_node));
            }

            case Node::Ty::BLOCK: {
                return generate_block(static_cast<BlockNode *>(p_node));
            }

            default:
                DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
                throw Warning(Logger::format("Node with type %s%i%s%s is not yet supported", BCYN, p_node->type, RESET, BOLD), dbg_info);
        }
    }

    llvm::Value* Generator::generate_block(BlockNode * p_node) {
        for (Node* node : p_node->exprs) {
            generate(node);
        }

        return llvm::ConstantInt::get(_builder.getInt1Ty(), 0);
    }


    llvm::Value* Generator::generate_if_stmt(IfStatementNode *p_node) {
        #define ELSE_STMT_EXISTS() p_node->else_stmt != NULL

        llvm::Value* inital_value = generate(p_node->stmt);
        GET_BOOL_VALUE(condition, inital_value)

        llvm::Value* cond = _builder.CreateICmpEQ(
            condition,
            llvm::ConstantInt::get(
                get_llvm_type_from_sn_type(BuildinTypes::BOOL, _builder),
                1
            )
        );

        llvm::Function *TheFunction = _builder.GetInsertBlock()->getParent();
        llvm::BasicBlock* IfBB = llvm::BasicBlock::Create(_builder.getContext(), "btrue", TheFunction);
        llvm::BasicBlock* ElseBB;

        if (ELSE_STMT_EXISTS()) {
            ElseBB = llvm::BasicBlock::Create(_builder.getContext(), "bfalse", TheFunction);
        }

        llvm::BasicBlock* ContinueBB = llvm::BasicBlock::Create(_builder.getContext(), "end", TheFunction);

        _builder.CreateCondBr(cond, IfBB, ELSE_STMT_EXISTS() ? ElseBB : ContinueBB);

        // Generate if statement
        _builder.SetInsertPoint(IfBB);
        _enviroment->create_scope("if$true");

        for (Node* node : p_node->body->exprs) {
            generate(node);
        }

        if ((IfBB->size() == 0 || !IfBB->back().isTerminator()) || _context.is_test) {
            _builder.CreateBr(ContinueBB);
        }

        _enviroment->delete_scope();

        // Generate else statement (if it exist)
        if (ELSE_STMT_EXISTS()) {
            _builder.SetInsertPoint(ElseBB);
            _enviroment->create_scope("if$false");

            for (Node* node : p_node->else_stmt->exprs) {
                generate(node);
            }

            if ((ElseBB->size() == 0 || !ElseBB->back().isTerminator()) || _context.is_test) {
                _builder.CreateBr(ContinueBB);
            }

            _enviroment->delete_scope();
        }

        // Continue with rest of body
        _builder.SetInsertPoint(ContinueBB);
        return ContinueBB;

        #undef ELSE_STMT_EXISTS
    }

    llvm::Value* Generator::generate_assert(AssertNode* p_node) {
        llvm::Value* inital_value = generate(p_node->expr);
        GET_BOOL_VALUE(assertion, inital_value)

        llvm::Value* current_test = *_enviroment->get("?test-result", nullptr)->llvm_value;

        _builder.CreateStore(_builder.CreateIntCast(assertion, _builder.getInt8Ty(), false), current_test);

        // DUMP_S(TypeChecker::get_type_name(current_test->getType()).c_str())
        llvm::Value* cond = _builder.CreateICmpEQ(
            convert_to_right_value(_builder, current_test),
            llvm::ConstantInt::get(
                _builder.getInt8Ty(),
                1
            )
        );

        llvm::Function *TheFunction = _builder.GetInsertBlock()->getParent();
        llvm::BasicBlock* FailBB = llvm::BasicBlock::Create(_builder.getContext(), "assert_fail", TheFunction);
        llvm::BasicBlock* ContinueBB = llvm::BasicBlock::Create(_builder.getContext(), "assert_continue", TheFunction);

        _builder.CreateCondBr(cond, ContinueBB, FailBB);

        _builder.SetInsertPoint(FailBB);
        _builder.CreateRet(convert_to_right_value(_builder, current_test));

        _builder.SetInsertPoint(ContinueBB);

        return ContinueBB;
    }

    llvm::Value* Generator::generate_import(ImportNode* p_node) {

        std::string module_name;
        std::string module_path;

        if (snowball_utils::endsWith(p_node->path, ".so")) {
            // TODO
        } else if (is_snowball_lib(p_node->path)) {
            if (_enviroment->item_exists(p_node->path)) {
                COMPILER_ERROR(VARIABLE_ERROR, Logger::format("module '%s' is already defined", p_node->path.c_str()))
            }

            if (snlib_is_object(p_node->path)) {
                auto [fn, path] = get_sn_export_lib(p_node->path);
                ScopeValue* mod = fn(_api);

                _linked_libraries.push_back(path);
                _enviroment->current_scope()->set(mangle(p_node->path, {}, true, true), std::make_unique<ScopeValue*>(mod));
                return llvm::ConstantInt::get(_builder.getInt8Ty(), 0);
            } else {
                module_name = p_node->path;
                module_path = get_sn_lib_src(p_node->path);
            }
        } else {
            // TODO
        }

        ScopeValue* module_scope = new ScopeValue(new Scope());
        auto class_struct = llvm::StructType::create(_builder.getContext(), module_name);
        module_scope->llvm_struct = std::make_shared<llvm::StructType *>(class_struct);
        module_scope->module_name = module_name;
        module_scope->type = ScopeType::MODULE;

        _context._current_module = module_scope;
        _enviroment->global_scope()->set(module_name, std::make_unique<ScopeValue*>(module_scope));

        // CREATE MODULE
        // TODO: new loading bar for modules as status
        SourceInfo* source_bk = _source_info;

        std::ifstream ifs(module_path);
        if (ifs.fail()){
            COMPILER_ERROR(IO_ERROR, Logger::format("path '%s' not found.", p_node->path.c_str()))
        }

        std::string content( (std::istreambuf_iterator<char>(ifs) ),
            (std::istreambuf_iterator<char>()    ) );

        _source_info = new SourceInfo(content, module_path);

        Lexer* lexer = new Lexer(_source_info);
        lexer->tokenize();

        if (lexer->tokens.size() != 0) {

            Parser* parser = new Parser(lexer, _source_info);
            parser->parse();

            for (auto* node : parser->nodes()) {
                generate(node);
            }

        }

        _context._current_module = nullptr;
        _source_info = source_bk;

        // Just return anything
        return llvm::ConstantInt::get(_builder.getInt8Ty(), 0);
    }

    llvm::Value* Generator::generate_new(NewNode* p_node) {
        std::string method_name = "__init(";
        std::vector<Type*> arg_types;
        std::vector<llvm::Value*> args;

        int arg_index = 0;
        for (Node* arg : p_node->arguments) {
            llvm::Value* result = generate(arg);
            arg_types.push_back(TypeChecker::to_type(TypeChecker::get_type_name(result->getType())).first);

            args.push_back(result);
            method_name += TypeChecker::get_type_name(result->getType());

            if ((p_node->arguments.size() > 1) && (arg_index < (p_node->arguments.size() - 1)))
                method_name += ", ";

            arg_index++;
        }

        method_name += ")";

        // TODO: check if there are generics
        std::string fname = GET_FUNCTION_FROM_CLASS(TypeChecker::to_mangle(p_node->method, {}).c_str(), "__init", arg_types, true);
        ScopeValue* function = _enviroment->get(
            fname,
            p_node,
            Logger::format("%s", fname.c_str())
        );

        if (function->type != ScopeType::FUNC) {
            DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
            throw CompilerError(Error::SYNTAX_ERROR, Logger::format("'%s' is not a function", p_node->method.c_str()), dbg_info);
        }

        return _builder.CreateCall(*function->llvm_function, args, "calltmp");
    }

    llvm::Value* Generator::generate_class(ClassNode* p_node) {
        _context._current_class = p_node;
        Type* class_type = new Type(p_node->name);

        _context._current_class->name = class_type->mangle();

        std::vector<llvm::Type*> var_types;
        for (VarNode* var : p_node->vars) {
            ScopeValue* type = TypeChecker::get_type(_enviroment, var->vtype, p_node);
            if (!TypeChecker::is_class(type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("'%s' does not reference a class", var->vtype->name.c_str()))
            }

            var_types.push_back((llvm::Type*)(*type->llvm_struct));
        }

        // TODO: check for generics
        // TODO: class name mangled if module exists
        auto class_struct = llvm::StructType::create(_builder.getContext(), class_type->mangle());
        class_struct->setBody(var_types);

        Scope* class_scope = new Scope(p_node->name, _source_info);

        ScopeValue* class_scope_val = new ScopeValue(class_scope, std::make_shared<llvm::StructType*>(class_struct));
        std::unique_ptr<ScopeValue*> class_value = std::make_unique<ScopeValue*>(class_scope_val);
        _enviroment->global_scope()->set(class_type->mangle(), std::move(class_value));

        for (FunctionNode* func : p_node->functions) {
            generate(func);
        }

        _context._current_class = nullptr;
        return (llvm::Value*)class_struct;
    }

    llvm::Value* Generator::generate_test(TestingNode* p_node) {

        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);
        std::string test_name = _context._testing_context->get_name(_context._testing_context->addTest(p_node->description));

        auto prototype = llvm::FunctionType::get(_builder.getInt8Ty(), {}, false);
        llvm::Function *function = llvm::Function::Create(prototype, llvm::Function::ExternalLinkage, test_name, _module);

        llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder.getContext(), "body", function);
        _builder.SetInsertPoint(body);

        if (p_node->skip) {
            _enviroment->delete_scope();
            _builder.CreateRet(llvm::ConstantInt::get(_builder.getInt64Ty(), 2));

            return function;

        } else {
            Scope* current_scope = _enviroment->create_scope(test_name);
            llvm::Value* value = llvm::ConstantInt::get(_builder.getInt8Ty(), 3);

            auto* llvm_alloca = _builder.CreateAlloca (value->getType(), nullptr, "?test-result" );

            std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(llvm_alloca)));
            current_scope->set("?test-result", std::move(scope_value));
            _builder.CreateStore (value, llvm_alloca, /*isVolatile=*/false);

            _context.is_test = true;
            for (Node* node : p_node->block->exprs) {
                generate(node);
            }

            _context.is_test = false;
            llvm::verifyFunction(*function, &message_stream);
            if (!llvm_error.empty())
                throw SNError(Error::LLVM_INTERNAL, llvm_error);

            _enviroment->delete_scope();
            _builder.CreateRet(convert_to_right_value(_builder, llvm_alloca));

            return function;
        }
    }

    llvm::Value* Generator::generate_call(CallNode* p_node) {
        std::string method_name = p_node->method + "(";
        std::vector<Type*> arg_types;
        std::vector<std::string> arg_types_str;
        std::vector<llvm::Value*> args;

        std::string base_struct = MODULE_NAME_IF_EXISTS("");
        llvm::Value* base_value;
        ScopeValue* class_value;
        if (p_node->base != nullptr && !p_node->is_static_call) {
            base_value = generate(p_node->base);

            if (dynamic_cast<IdentifierNode*>(p_node->base) != nullptr) {

                std::string base_name = dynamic_cast<IdentifierNode*>(p_node->base)->name;
                std::string mangled_base_name = (new Type(base_name))->mangle();

                if (_enviroment->item_exists(mangled_base_name)) {
                    class_value = _enviroment->get(mangled_base_name, p_node);
                } else if (_enviroment->item_exists(base_name)) {
                    class_value = _enviroment->get(base_name, p_node);
                } else {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Identifier %s does not exist (in function call base)!"))
                }

                if (class_value->type == ScopeType::LLVM) {
                    class_value = _enviroment->get(TypeChecker::get_type_name((*class_value->llvm_value)->getType()), p_node->base);
                }
            } else {
                class_value = _enviroment->get(TypeChecker::get_type_name(base_value->getType()), p_node->base);
            }

            if (!base_struct.empty()) base_struct += ".";
            base_struct += TypeChecker::get_type_name(*class_value->llvm_struct);
            if (class_value->type == ScopeType::MODULE) {
                p_node->is_static_call = true;
            } else {
                args.push_back(base_value);
                arg_types.push_back(TypeChecker::to_type(base_struct).first); // demangle types
                arg_types_str.push_back(base_struct);

                method_name += "self";
                if ((p_node->arguments.size() > 0))
                    method_name += ", ";
            }
        } else if (p_node->base != nullptr && p_node->is_static_call) {
            base_value = generate(p_node->base);

            if (dynamic_cast<IdentifierNode*>(p_node->base) != nullptr) {
                class_value = _enviroment->get((new Type(dynamic_cast<IdentifierNode*>(p_node->base)->name))->mangle(), p_node->base);
                if (class_value->type == ScopeType::LLVM) {
                    class_value = _enviroment->get(TypeChecker::get_type_name((*class_value->llvm_value)->getType()), p_node);
                }
            } else {
                class_value = _enviroment->get(TypeChecker::get_type_name(base_value->getType()), p_node);
            }

            if (!base_struct.empty()) base_struct += ".";
            base_struct += TypeChecker::get_type_name(*class_value->llvm_struct);
        }

        int arg_index = 0;
        for (Node* arg : p_node->arguments) {
            llvm::Value* result = generate(arg);
            arg_types.push_back(TypeChecker::to_type(TypeChecker::get_type_name(result->getType())).first);

            args.push_back(result);
            method_name += TypeChecker::get_type_name(result->getType());

            if ((p_node->arguments.size() > 1) && (arg_index < (p_node->arguments.size() - 1)))
                method_name += ", ";

            arg_index++;
        }

        method_name += ")";

        // Todo: check if method is private / public
        std::string method_call =
            ADD_MODULE_NAME_IF_EXISTS()
            (p_node->base == nullptr ?
            mangle(p_node->method, arg_types) :
            GET_FUNCTION_FROM_CLASS(base_struct.c_str(), p_node->method, arg_types));

        ScopeValue* function;

        // First, look for private methods
        bool private_method_used = false;
        bool private_method_exists = false;
        if (_enviroment->item_exists(method_call)) {
            ScopeValue* private_function = _enviroment->get(method_call, p_node); // it will exist... right?
            if ((_context._current_module != nullptr && _context._current_module->module_name == base_struct) || (_context._current_class != nullptr && _context._current_class->name == base_struct) || (private_function->parent_scope->name() == SN_GLOBAL_SCOPE)) {
                function = private_function;
                private_method_used = true;
            } else {
                private_method_exists = true;
            }
        } else if (p_node->generics.size() > 0) {
            auto [generic_function, succ] = _generics->get_generic(method_call, arg_types, p_node->generics, p_node);
            if (succ && ((_context._current_module != nullptr && _context._current_module->module_name == base_struct) || (_context._current_class != nullptr && _context._current_class->name == base_struct) || generic_function.node->is_lop_level)) {
                auto backup = _builder.GetInsertBlock();

                generate(generic_function.node);
                function = _enviroment->get(
                    p_node->base == nullptr ?
                    mangle(p_node->method, generic_function.args, false) :
                    GET_FUNCTION_FROM_CLASS(base_struct.c_str(), p_node->method, generic_function.args, false), p_node);

                _builder.SetInsertPoint(backup);
                private_method_used = true;
            } else if (succ) {
                private_method_exists = true;
            }
        }

        if (!private_method_used) {
            method_call =
                ADD_MODULE_NAME_IF_EXISTS()
                (p_node->base == nullptr ?
                mangle(p_node->method, arg_types, true) :
                GET_FUNCTION_FROM_CLASS(base_struct.c_str(), p_node->method, arg_types, true));

            if (p_node->generics.size() > 0) {
                auto [generic_function, succ] = _generics->get_generic(method_call, arg_types, p_node->generics, p_node);
                if (succ) {
                    auto backup = _builder.GetInsertBlock();

                    generate(generic_function.node);
                    function = _enviroment->get(
                        p_node->base == nullptr ?
                        mangle(p_node->method, generic_function.args, true) :
                        GET_FUNCTION_FROM_CLASS(base_struct.c_str(), p_node->method, generic_function.args, true), p_node);

                    _builder.SetInsertPoint(backup);
                } else {
                    FUNCTION_CALL_NOT_FOUND()
                }
            } else {

                // Look for public
                if (_enviroment->item_exists(method_call)) {
                    function = _enviroment->get(method_call, p_node);
                } else {
                    FUNCTION_CALL_NOT_FOUND()
                }
            }
        }

        if (function->type != ScopeType::FUNC) {
            COMPILER_ERROR(SYNTAX_ERROR, Logger::format("'%s' is not a function", p_node->method.c_str()))
        }

        ASSERT(args.size() == arg_types.size())
        return _builder.CreateCall(*function->llvm_function, args);
    }

    llvm::Value* Generator::generate_return(ReturnNode* p_node) {
        llvm::Value* value = generate(p_node->value);
        llvm::Type* type = value->getType();
        ScopeValue* ret_value = TypeChecker::get_type(_enviroment, p_node->parent->return_type, p_node);

        std::string ret_type;
        if (TypeChecker::is_class(ret_value)) {
            ret_type = TypeChecker::get_type_name(TypeChecker::type2llvm(_builder, *ret_value->llvm_struct));
        } else if (ret_value->type == ScopeType::LLVM) {
            ret_type = TypeChecker::get_type_name(TypeChecker::type2llvm(_builder, (*ret_value->llvm_value)
                ->getType()));
        }

        if (TypeChecker::get_type_name(type) == ret_type) {
            return _builder.CreateRet(value);
        } else {
            COMPILER_ERROR(
                TYPE_ERROR,
                Logger::format(
                    "Mismatched types between '%s' and '%s'",
                    TypeChecker::get_type_name(value->getType()).c_str(),
                    ret_type.c_str()
                )
            )
        }
    }

    llvm::Value* Generator::generate_identifier(IdentifierNode* p_node) {

        ScopeValue* value;
        std::string name = (new Type(p_node->name))->mangle();

        if (_enviroment->item_exists(p_node->name)) {
            value = _enviroment->get(p_node->name, p_node);
        } else if (_enviroment->item_exists(name)) {
            value = _enviroment->get(name, p_node);
        } else {
            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Identifier %s does not exist!", p_node->name.c_str()))
        }

        switch (value->type)
        {
            case ScopeType::CLASS: {
                llvm::StructType* type = *value->llvm_struct;
                int size = _module->getDataLayout().getTypeStoreSize(type);
                llvm::ConstantInt* size_constant = llvm::ConstantInt::get(_builder.getInt32Ty(), size);

                llvm::Value* alloca_value = _builder.CreateCall(get_alloca(_module, _builder), size_constant);
                return _builder.CreatePointerCast(alloca_value, type->getPointerTo());
            }

            case ScopeType::MODULE: {
                return (llvm::Value*)(*value->llvm_struct);
            }

            case ScopeType::FUNC:
                return (llvm::Value*)(*value->llvm_function);

            case ScopeType::LLVM:
                return (llvm::Value*)(*value->llvm_value);

            default: {
                COMPILER_ERROR(BUG, Logger::format("Scope with type ::SCOPE has been fetched in Generator::generate_identifier (idnt: %s).", p_node->name.c_str()))
            }
        }
    }

    llvm::Value* Generator::generate_operator(BinaryOp* p_node) {
        llvm::Value* left = generate(p_node->left);

        if (p_node->unary) {
            llvm::Type* left_type = left->getType()->isPointerTy() ? left->getType()->getPointerElementType() : left->getType();

            llvm::Function* function;
            switch (p_node->op_type)
            {
                case OP_NOT: {
                    if ((TypeChecker::get_type_name(left_type) == BOOL_TYPE->mangle()) || TypeChecker::is_number(left_type)) {
                        return _builder.CreateNot(left);
                    }

                    CALL_UNARY_OPERATOR("__not")
                    break;
                }

                default: {
                    COMPILER_ERROR(BUG, Logger::format("The operator with type '%i' has not been handled.", p_node->op_type))
                }
            }

            return _builder.CreateCall(function,
                {left});
        } else {
            llvm::Value* right = generate(p_node->right);

            // get names with type checker
            llvm::Type* left_type = left->getType()->isPointerTy() ? left->getType()->getPointerElementType() : left->getType();
            llvm::Type* right_type = right->getType()->isPointerTy() ? right->getType()->getPointerElementType() : right->getType();

            llvm::Function* function;
            switch (p_node->op_type)
            {
                case OP_PLUS: {
                    TypeChecker::implicit_cast(_builder, left_type, right);
                    bool types_equal = TypeChecker::get_type_name(left_type) == TypeChecker::get_type_name(right_type);

                    if (types_equal && TypeChecker::is_number(left_type)) {
                        return _builder.CreateAdd(left, right);
                    }
                    // TODO: bool + bool
                    // TODO: create int cast if they dont match or throw an error

                    CALL_OPERATOR("__sum")
                    break;
                }

                case OP_EQ: {
                    CALL_OPERATOR("__eq")
                    break;
                }

                case OP_EQEQ: {
                    TypeChecker::implicit_cast(_builder, left_type, right);
                    bool types_equal = TypeChecker::get_type_name(left_type) == TypeChecker::get_type_name(right_type);

                    if (types_equal && TypeChecker::is_number(left_type)) {
                        return _builder.CreateICmpEQ(left, right);
                    }

                    CALL_OPERATOR("__eqeq")
                    break;
                }

                case OP_LTEQ: {
                    TypeChecker::implicit_cast(_builder, left_type, right);
                    bool types_equal = TypeChecker::get_type_name(left_type) == TypeChecker::get_type_name(right_type);

                    if (types_equal && TypeChecker::is_number(left_type)) {
                        return _builder.CreateICmpSLE(left, right);
                    }

                    CALL_OPERATOR("__lteq")
                    break;
                }

                case OP_MINUS: {
                    TypeChecker::implicit_cast(_builder, left_type, right);
                    bool types_equal = TypeChecker::get_type_name(left_type) == TypeChecker::get_type_name(right_type);

                    if (types_equal && TypeChecker::is_number(left_type)) {
                        return _builder.CreateSub(left, right);
                    }


                    CALL_OPERATOR("__sub")
                    break;
                }

                default: {
                    COMPILER_ERROR(BUG, Logger::format("The operator with type '%i' has not been handled.", p_node->op_type))
                }
            }

            return _builder.CreateCall(function,
                {left, right});
        }
    }

    llvm::Value* Generator::generate_function(FunctionNode* p_node) {

        #define IS_ENTRY_POINT() (p_node->name == _SNOWBALL_FUNCTION_ENTRY && p_node->is_lop_level)

        // Skip if the function contains a template
        if (p_node->generics.size() > 0) {

            std::vector<Type*> args;
            for (ArgumentNode* argument : p_node->arguments) {
                args.push_back(argument->arg_type);
            }

            // TODO: check if return type and arg types exist
            _generics->add_generic(mangle(ADD_MODULE_NAME_IF_EXISTS()
                (_context._current_class == nullptr ? p_node->name : Logger::format(
                    "%s.%s", _context._current_class->name.c_str(),
                    p_node->name.c_str()
                )), args, p_node->is_public), args, p_node->return_type, p_node->generics, p_node);
            return _builder.getInt1(0);
        };

        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);

        ScopeValue* returnType = TypeChecker::get_type(_enviroment, p_node->return_type, p_node);
        auto retType =
            IS_ENTRY_POINT()
                ? get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder)
                : TypeChecker::type2llvm(_builder, *returnType->llvm_struct);

        std::vector<Type*> arg_tnames;
        std::vector<llvm::Type*> arg_types;
        for (ArgumentNode* argument : p_node->arguments) {

            // check if type exists
            ScopeValue* value = TypeChecker::get_type(_enviroment, argument->arg_type, argument);
            if (!TypeChecker::is_class(value)) {
                COMPILER_ERROR(ARGUMENT_ERROR, Logger::format("'%s' must be a referece to a class", p_node->name.c_str()))
            }

            llvm::StructType* type = *value->llvm_struct;

            arg_types.push_back(TypeChecker::type2llvm(_builder, type));
            arg_tnames.push_back(TypeChecker::to_type(type->getName().str()).first);
        }

        if (_context._current_class != nullptr && p_node->name != "__init" && !p_node->is_static) {
            // We asume that the class has already been assigned
            arg_types.insert(
                arg_types.begin(),
                ((llvm::Type*)*_enviroment->get(_context._current_class->name, p_node)->llvm_struct)->getPointerTo()
            );
            arg_tnames.insert(arg_tnames.begin(), TypeChecker::to_type(_context._current_class->name).first);
        }

        std::string fname = p_node->is_extern ? p_node->name : mangle(
                ADD_MODULE_NAME_IF_EXISTS()
                (_context._current_class == nullptr ? p_node->name : Logger::format(
                    "%s.%s", _context._current_class->name.c_str(),
                    p_node->name.c_str()
                )), arg_tnames, p_node->is_public);

        auto prototype = llvm::FunctionType::get(retType, arg_types, p_node->has_vargs);
        llvm::Function *function = llvm::Function::Create(
            prototype,
            llvm::Function::ExternalLinkage,
            IS_ENTRY_POINT() ? _SNOWBALL_FUNCTION_ENTRY : fname,
            _module);

        std::unique_ptr<ScopeValue*> func_scopev = std::make_unique<ScopeValue*>(new ScopeValue(std::make_shared<llvm::Function*>(function)));
        (*func_scopev)->isStaticFunction = p_node->is_static;
        (*func_scopev)->hasVArg = p_node->has_vargs;
        (*func_scopev)->arguments = arg_tnames;
        SET_TO_GLOBAL_OR_CLASS(mangle(
                // ADD_MODULE_NAME_IF_EXISTS()
                p_node->name, arg_tnames, p_node->is_public), func_scopev);

        Scope* current_scope = _enviroment->create_scope(p_node->name);

        int parameter_index = _context._current_class != nullptr ? 0 : 1;
        for (auto& arg : function->args()) {
            std::string name;
            if (_context._current_class != nullptr && p_node->name != "__init" && parameter_index == 0 && !p_node->is_static) /* self argument */ {
                name = "self";
            } else {
                name = p_node->arguments.at(parameter_index == 0 ? 0 : parameter_index-1)->name;
            }

            if (_context._current_class != nullptr && parameter_index>0 && name == "self") {
                COMPILER_ERROR(SYNTAX_ERROR, "Class method can't contain self as a parameter")
            }

            arg.setName(name);

            std::unique_ptr<ScopeValue*> param_scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(&arg)));
            current_scope->set(name, std::move(param_scope_value));

            parameter_index++;
        }

        // BODY GENERATION

        if (!p_node->is_foward) {
            llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder.getContext(), "body", function);
            _builder.SetInsertPoint(body);

            if (_context._current_class != nullptr && p_node->name == "__init" && !p_node->is_static) {
                generate_contructor_meta();
            }

            for (const auto& generic : p_node->generic_map) {
                ScopeValue* scope_val = TypeChecker::get_type(_enviroment, generic.second, p_node);
                if (!TypeChecker::is_class(scope_val)) {
                    COMPILER_ERROR(SYNTAX_ERROR, Logger::format("%s does not point a class", generic.second->to_string().c_str()))
                }

                std::string name = generic.second->mangle();

                if (_enviroment->item_exists(name)) {
                    auto ty = *_enviroment->get(name, p_node)->llvm_struct;

                    int size = _module->getDataLayout().getTypeStoreSize(ty);
                    llvm::ConstantInt* size_constant = llvm::ConstantInt::get(_builder.getInt32Ty(), size);

                    llvm::Value* alloca_value = _builder.CreateCall(get_alloca(_module, _builder), size_constant);
                    llvm::Value* cast = _builder.CreatePointerCast(alloca_value, TypeChecker::type2llvm(_builder, ty), generic.first);

                    std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(cast)));

                    SET_TO_SCOPE_OR_CLASS(generic.first, std::move(scope_value))
                    continue;
                }

                COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Type '%s' not found in generics", p_node->name))
            }

            for (auto expr : p_node->body->exprs) {
                generate(expr);
            }

            if (body->size() == 0 || !body->back().isTerminator()) {
                if (p_node->name == _SNOWBALL_FUNCTION_ENTRY && p_node->is_lop_level) {
                    llvm::Type * i64 = get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder);
                    _builder.CreateRet(llvm::ConstantInt::get(i64, 0));
                } else if (_context._current_class != nullptr && p_node->name == "__init") {
                    _builder.CreateRet(*current_scope->get("self", nullptr)->llvm_value);
                } else if (retType->isVoidTy()) {
                    _builder.CreateRet(nullptr);
                } else {
                    COMPILER_ERROR(FUNCTION_RET_ERR, Logger::format("Function '%s' does not have a return statement for all paths!", p_node->name.c_str()))
                }
            }
        }

        llvm::verifyFunction(*function, &message_stream);
        if (!llvm_error.empty()) {
            COMPILER_ERROR(LLVM_INTERNAL, llvm_error)
        }

        _enviroment->delete_scope();

        return function;

        #undef IS_ENTRY_POINT
    }

    llvm::Value* Generator::generate_variable_decl(VarNode* p_node) {
        // TODO: check if variable is global

        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
        Scope* scope = _enviroment->current_scope();

        if (scope->item_exists(p_node->name) || p_node->name == _enviroment->current_scope()->name()) {
            throw CompilerError(Error::VARIABLE_ERROR, Logger::format("'%s' has already been declared", p_node->name.c_str()), dbg_info);
        }

        if (p_node->isGlobal) {
            throw SNError(Error::TODO, "Global variables");
        } else {
            llvm::Value* value = generate(p_node->value);
            auto* alloca = _builder.CreateAlloca (value->getType(), nullptr, p_node->name );

            std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(value)));
            _enviroment->current_scope()->set(p_node->name, std::move(scope_value));

            return _builder.CreateStore (value, alloca, /*isVolatile=*/false);
        }

    }

    llvm::Value* Generator::generate_const_value(ConstantValue* p_node) {
        switch (p_node->const_type)
        {
            case TokenType::VALUE_NUMBER: {
                llvm::Type * i64 = get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder);
                snowball_int_t number_value;

                if ((p_node->value.rfind("0x", 0) == 0) || (p_node->value.rfind("0X", 0) == 0)) {
                    number_value = std::stoul(p_node->value, nullptr, 16);
                } else if ((p_node->value.rfind("0b", 0) == 0) || (p_node->value.rfind("0B", 0) == 0)) {
                    number_value = std::stoul(p_node->value.substr(2, (size_t)(p_node->value.size() - 2)), nullptr, 2);
                } else {
                    number_value = std::stoul(p_node->value);
                }

                llvm::Constant * num = llvm::ConstantInt::get(i64, (snowball_int_t)number_value);
                return num;
            }

            case TokenType::VALUE_STRING: {
                std::string str = p_node->value;
                str = str.substr(1, str.size() - 2);
                llvm::Constant* value = _builder.CreateGlobalStringPtr(str.c_str(), ".str");
                return value;
            }

            case TokenType::VALUE_BOOL: {
                llvm::Type * i1 = get_llvm_type_from_sn_type(BuildinTypes::BOOL, _builder);
                return llvm::ConstantInt::get(i1, p_node->value == "true");
            }

            default:
                throw SNError(Error::TODO, Logger::format("Const Value with type %s%i%s%s is not yet supported", BCYN, p_node->const_type, RESET, BOLD));
        }
    }

    // utils

    void Generator::generate_contructor_meta() {
        ASSERT(_context._current_class != nullptr)

        llvm::StructType* type = *_enviroment->get(_context._current_class->name, _context._current_class)->llvm_struct;
        int size = _module->getDataLayout().getTypeStoreSize(type);
        llvm::ConstantInt* size_constant = llvm::ConstantInt::get(_builder.getInt32Ty(), size);

        llvm::Value* alloca_value = _builder.CreateCall(get_alloca(_module, _builder), size_constant);
        llvm::Value* pointerCast = _builder.CreatePointerCast(alloca_value, type->getPointerTo(), "self");

        std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value *>(pointerCast)));
        _enviroment->current_scope()->set("self", std::move(scope_value));


        int var_index = 0;
        for (VarNode* var : _context._current_class->vars) {
            llvm::Value* value = generate(var->value);
            llvm::Value* pointer = _builder.CreateStructGEP(pointerCast, var_index);
            llvm::Value* load = convert_to_right_value(_builder, pointer);

            _builder.CreateStore(load, value);

            var_index++;
        }
    }

    llvm::Value* Generator::convert_to_right_value(llvm::IRBuilder<> p_builder, llvm::Value* value) {

        if (value->getName().str().empty()) return p_builder.CreateLoad(value);
        std::ostringstream ss_name;

        ss_name << value->getName().str();
        ss_name << ".load";

        return p_builder.CreateLoad(value, ss_name.str());
    }
}
