
#include "snowball/libs.h"

#include "snowball/types.h"
#include "snowball/nodes.h"
#include "snowball/token.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"

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

#define MODULE_NAME_IF_EXISTS(_sufix) (_context._current_module != nullptr ? (_context._current_module->module_name + _sufix) : "")
#define ADD_MODULE_NAME_IF_EXISTS(_sufix) MODULE_NAME_IF_EXISTS(_sufix) +

#define NAMESPACE_NAME_IF_EXISTS(_sufix) (_context._current_namespace != nullptr ? (_context._current_namespace->module_name + _sufix) : "")
#define ADD_NAMESPACE_NAME_IF_EXISTS(_sufix) NAMESPACE_NAME_IF_EXISTS(_sufix) +

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
        _enviroment->get(ADD_MODULE_NAME_IF_EXISTS(".") _context._current_class->name, nullptr)->scope_value->set(_name, std::move(value)); \
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
        __v =  _builder->CreateICmpEQ(__v, llvm::ConstantInt::get(__ty, 1)); \
    } else if (__ty->isDoubleTy() || __ty->isFloatTy()) { \
        __v = _builder->CreateFCmpOEQ(__v, llvm::ConstantFP::get(__ty, 1.0)); \
    } else if (!TypeChecker::is_bool(__ty)) { \
        auto __c = *_enviroment->get(GET_FUNCTION_FROM_CLASS(__tys.c_str(), "__bool", {TypeChecker::to_type(__tys).first}, true), p_node, Logger::format("%s.__bool(self)", __tys.c_str()))->llvm_function; \
        __v = _builder->CreateCall(__c, {__v}); \
    } \
    llvm::Value* ret = __v;

#define CALL_OPERATOR(opty) \
    std::string method = Logger::format("%s.#%s", TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first->mangle().c_str(), op2str(opty).c_str()); \
    auto __u = unmangle(mangle(method, { \
        TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first, \
        TypeChecker::to_type(TypeChecker::get_type_name(right_type)).first \
    })); \
    __u.isPublic = true; \
    auto __f = _enviroment->find_function_if(FNAME_NO_MANGLE(opty), [=](auto store) -> bool { \
        auto node_args = store.node->arguments; \
        ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first); \
        node_args.insert(node_args.begin(), arg); \
        if ((node_args.size() <= __u.arguments.size()) && store.node->has_vargs) {} \
        else if (node_args.size() != __u.arguments.size()) return false; \
        return TypeChecker::functions_equal( \
            store.node->name, \
            store.node->name, \
            TypeChecker::args2types(node_args), \
            __u.arguments, \
            __u.isPublic, \
            store.node->is_public, \
            store.node->has_vargs); \
    }); \
    if (__f == nullptr) { \
        function = *_enviroment->get( \
        GET_FUNCTION_FROM_CLASS( \
            TypeChecker::get_type_name(left_type).c_str(), \
            method, \
            __u.arguments, \
            __u.isPublic \
        ), p_node, Logger::format( \
            "%s %s %s", \
                TypeChecker::get_type_name(left_type).c_str(), \
                op2str(opty).c_str(), /* TODO: convert to actual symbol */ \
                TypeChecker::get_type_name(right_type).c_str() \
            ) \
        )->llvm_function; \
    } else { \
        function = (llvm::Function*)paste_function(__f); \
    }

#define CALL_UNARY_OPERATOR(opty) \
    std::string method = Logger::format("%s.#%s", TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first->mangle().c_str(), op2str(opty).c_str()); \
    auto __u = unmangle(mangle(method, { \
        TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first, \
    })); \
    __u.isPublic = true; \
    auto __f = _enviroment->find_function_if(FNAME_NO_MANGLE(opty), [=](auto store) -> bool { \
        auto node_args = store.node->arguments; \
        ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first); \
        node_args.insert(node_args.begin(), arg); \
        if ((node_args.size() <= __u.arguments.size()) && store.node->has_vargs) {} \
        else if (node_args.size() != __u.arguments.size()) return false; \
        return TypeChecker::functions_equal( \
            store.node->name, \
            store.node->name, \
            TypeChecker::args2types(node_args), \
            __u.arguments, \
            __u.isPublic, \
            store.node->is_public, \
            store.node->has_vargs); \
    }); \
    if (__f == nullptr) { \
        function = *_enviroment->get( \
        GET_FUNCTION_FROM_CLASS( \
            TypeChecker::get_type_name(left_type).c_str(), \
            method, \
            __u.arguments, \
            __u.isPublic \
        ), p_node, Logger::format( \
            "%s%s", \
                op2str(opty).c_str(), /* TODO: convert to actual symbol */ \
                TypeChecker::get_type_name(left_type).c_str() \
            ) \
        )->llvm_function; \
    } else { \
        function = (llvm::Function*)paste_function(__f); \
    }

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

            default:
                DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
                throw Warning(Logger::format("Node with type %s%i%s%s is not yet supported", BCYN, p_node->type, RESET, BOLD), dbg_info);
        }
    }

    llvm::Value* Generator::generate_operator(OperatorNode * p_node) {

        ASSERT(_context._current_class != nullptr)

        std::vector<Type*> arg_tnames;
        std::vector<llvm::Type*> arg_types;

        for (ArgumentNode* argument : p_node->arguments) {

            // check if argument is actualy a generic
            auto it = std::find_if(p_node->generics.begin(), p_node->generics.end(), [&](Type* arg) {
                return arg->equals(argument->arg_type);
            });

            if (it == p_node->generics.end()) {

                // check if type exists
                ScopeValue* value = TypeChecker::get_type(_enviroment, argument->arg_type, argument);
                if (!TypeChecker::is_class(value)) {
                    COMPILER_ERROR(ARGUMENT_ERROR, Logger::format("'%s' must be a referece to a class", p_node->name.c_str()))
                }

                llvm::StructType* type = *value->llvm_struct;
                arg_types.push_back(TypeChecker::type2llvm(_builder, type));
                arg_tnames.push_back(argument->arg_type);
            } else {
                arg_tnames.push_back(*it);
            }
        }

        // We asume that the class has already been assigned
        arg_types.insert(
            arg_types.begin(),
            ((llvm::Type*)*_enviroment->get(_context._current_class->name, p_node)->llvm_struct)->getPointerTo()
        );

        arg_tnames.insert(arg_tnames.begin(), TypeChecker::to_type(_context._current_class->name).first);

        Enviroment::FunctionStore* store = new Enviroment::FunctionStore();
        store->current_class = _context._current_class;
        store->current_module = _context._current_module;

        store->node = p_node;

        std::string fname = ADD_MODULE_NAME_IF_EXISTS(".")
            (
                mangle((ADD_MODULE_NAME_IF_EXISTS(".")

                Logger::format(
                    "%s.#%s", store->current_class->name.c_str(),
                    store->node->name.c_str()
                )), arg_tnames, store->node->is_public)
            );

        _enviroment->set_function(fname, store);

        // Function prototype for return statement

        ScopeValue* returnType = TypeChecker::get_type(_enviroment, store->node->return_type, store->node);
        auto retType = TypeChecker::type2llvm(_builder, *returnType->llvm_struct);

        auto prototype = llvm::FunctionType::get(retType, arg_types, store->node->has_vargs);
        llvm::Function *function = llvm::Function::Create(
            prototype,
            llvm::Function::ExternalLinkage,
            (
                store->node->is_extern ? store->node->name : mangle((ADD_MODULE_NAME_IF_EXISTS(".")

                (store->current_class == nullptr ? store->node->name : Logger::format(
                    "%s.#%s", store->current_class->name.c_str(),
                    store->node->name.c_str()
                ))), arg_tnames, store->node->is_public)
            ),
            _module);

        return function;
    }

    llvm::Value* Generator::generate_attribute(AttributeNode* p_node) {
        auto attrs = _api->get_attributes();

        for (auto node_attrs : p_node->attributes) {
            bool attr_exists = false;
            for (auto attr : attrs) {
                if (attr->get_name() == node_attrs.name) {
                    attr_exists = true;

                    if (attr->start(_api->context)) {
                        auto generated = generate(p_node->node);

                        if (generated->getType()->isPointerTy() ?
                            generated->getType()->getPointerElementType()->isFunctionTy() :
                            generated->getType()->isFunctionTy()) {
                            Attribute::ResponseValue response;
                            response.type = Attribute::ResponseValue::ResponseType::LLVM_FUNCTION;
                            response.function.llvm_value = generated;

                            auto result = unmangle(generated->getName().str());
                            Enviroment::FunctionStore* function_store;


                            if ((function_store = _enviroment->find_function_if(result.name, [=](auto store) -> bool {
                                if (store.node->is_public) return false;
                                if ((store.node->arguments.size() <= result.arguments.size()) && store.node->has_vargs) {}
                                else if (store.node->arguments.size() != result.arguments.size()) return false;
                                return TypeChecker::functions_equal(
                                    store.node->name,
                                    store.node->name,
                                    TypeChecker::args2types(store.node->arguments),
                                    result.arguments,
                                    result.isPublic,
                                    store.node->is_public,
                                    store.node->has_vargs);
                            }))) {
                                response.function.store = function_store;
                            } else {
                                COMPILER_ERROR(BUG, "Coudn't find function in attribute")
                            }

                            attr->end(response, _api);
                        } else {
                            COMPILER_ERROR(BUG, "Unsuported type from attribute")
                        }
                    }

                    break;
                }
            }

            if (!attr_exists) {
                COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Attribute name not found: %s", node_attrs.name.c_str()))
            }
        }
    }

    llvm::Value* Generator::generate_cast(CastNode* p_node) {
        auto original_value = generate(p_node->expr);
        auto cast_type = TypeChecker::get_type(_enviroment, p_node->cast_type, p_node);

        if (!TypeChecker::is_class(cast_type)) {
            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Type '%s' does not point to a class!", p_node->cast_type->to_string().c_str()))
        }

        auto [cast, succ] = TypeChecker::implicit_cast(_builder, TypeChecker::type2llvm(_builder, *cast_type->llvm_struct), original_value);
        if (!succ) {
            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Can't cast type '%s' to '%s'!", TypeChecker::to_type(TypeChecker::get_type_name(original_value->getType())).first->to_string().c_str(), p_node->cast_type->to_string().c_str()))
        }

        return cast;
    }

    llvm::Value* Generator::generate_index(IndexNode* p_node) {
        llvm::Value* gen_result = generate(p_node->base); // TODO: check if base points to a type
        llvm::Type* type = gen_result->getType();

        ScopeValue* value = _enviroment->get(TypeChecker::get_type_name(type), p_node);
        switch (value->type)
        {
            case ScopeType::CLASS: {
                std::vector<ScopeValue::ClassPropertie> properties = value->properties;

                ptrdiff_t pos = std::find_if(properties.begin(), properties.end(), [&](ScopeValue::ClassPropertie p_prop) {
                    return p_prop.name == p_node->member->name;
                }) - properties.begin();

                if (pos >= (properties.size())) {

                    // TODO: index error
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format(
                        "Class %s%s%s does not have a member called %s%s%s!",
                        BBLU, TypeChecker::to_type(TypeChecker::get_type_name(type)).first->to_string().c_str(), RESET,
                        BBLU, p_node->member->name.c_str(), RESET))
                }

                if ((!properties.at(pos).is_public) && _context._current_class == nullptr) {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format(
                        "Trying to access member private %s%s%s from class %s%s%s!",
                        BBLU, p_node->member->name.c_str(), RESET,
                        BBLU, TypeChecker::to_type(TypeChecker::get_type_name(type)).first->to_string().c_str(), RESET))
                }

                // We asume it's a pointer since raw types does not have any attriute
                auto GEP = _builder->CreateInBoundsGEP(gen_result->getType()->getPointerElementType(), gen_result, {llvm::ConstantInt::get(_builder->getInt32Ty(), 0), llvm::ConstantInt::get(_builder->getInt32Ty(), pos+value->parents.size())});
                return convert_to_right_value(_builder, GEP);
            }

            case ScopeType::MODULE: {
                // TODO: custom error if no member exists
                // TODO: module variables?
                return generate(new IdentifierNode((value->module_name + ".") + p_node->member->name));
            }

            case ScopeType::NAMESPACE: {
                // TODO: custom error if no member exists
                std::string name = (value->module_name + ".") + TypeChecker::string_mangle(p_node->member->name);

                ScopeValue* result = nullptr;
                if (_enviroment->item_exists((value->module_name + ".") + p_node->member->name)) {
                    result = _enviroment->get((value->module_name + ".") + p_node->member->name, p_node);
                } else if (_enviroment->item_exists(name)) {
                    result = _enviroment->get(name, p_node);
                } else {
                    COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Namespace '%s' does not contain member '%s'", TypeChecker::to_type(value->module_name).first->to_string().c_str(), p_node->member->name.c_str()))
                }

                switch (result->type) {
                    case ScopeType::MODULE:
                    case ScopeType::CLASS:
                    case ScopeType::NAMESPACE: {
                        llvm::StructType* type = *result->llvm_struct;
                        auto alloca = _builder->CreateAlloca(type);
                        alloca->eraseFromParent();
                        return alloca;
                    }

                    case ScopeType::FUNC:
                        return (llvm::Value*)(*result->llvm_function);

                    case ScopeType::LLVM: {
                        llvm::Value* llvalue = *result->llvm_value;
                        if (llvm::GlobalValue* G = llvm::dyn_cast<llvm::GlobalValue>(llvalue)) {

                            if (p_node->member->name.find(".") != std::string::npos) {
                                std::string split = snowball_utils::split(p_node->member->name, ".").at(0);
                                if ((_context._current_module == nullptr ? true : _context._current_module->module_name != split)) {
                                    if (!value->isPublic) {
                                        COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Trying to access a private variable from '%s'", split.c_str()))
                                    }
                                }
                            }

                            return convert_to_right_value(_builder, G);
                        }

                        return llvalue;
                    }

                    default: {
                        COMPILER_ERROR(BUG, Logger::format("Invalid Scope Value (idnt: %s, ty: %i).", p_node->member->name.c_str(), value->type))
                    }
                }

                return nullptr;
            }

            case ScopeType::FUNC: {
                COMPILER_ERROR(TODO, "Function index!")
            }

            case ScopeType::LLVM: {
                COMPILER_ERROR(TODO, "LLVM Index!")
            }

            default: {
                COMPILER_ERROR(BUG, Logger::format("Scope with type ::SCOPE has been fetched in Generator::generate_index (idnt: %s).", p_node->member->name.c_str()))
            }
        }
    }

    llvm::Value* Generator::generate_module(ModuleNode* p_node) {

        // TODO: check if module already exists
        auto module_name = TypeChecker::string_mangle(p_node->name);

        ScopeValue* module_scope = new ScopeValue(new Scope(module_name, _source_info));
        auto class_struct = llvm::StructType::create(_builder->getContext(),  ADD_NAMESPACE_NAME_IF_EXISTS(".") module_name);
        class_struct->setBody({}, true);
        module_scope->llvm_struct = std::make_shared<llvm::StructType *>(class_struct);
        module_scope->module_name = ADD_NAMESPACE_NAME_IF_EXISTS(".") module_name;
        module_scope->type = ScopeType::MODULE;
        module_scope->type = ScopeType::NAMESPACE;


        if (_context._current_namespace != nullptr) {
            _enviroment->get((ADD_MODULE_NAME_IF_EXISTS(".") _context._current_namespace->module_name), nullptr)->scope_value->set(module_name, std::make_unique<ScopeValue*>(module_scope));
            _enviroment->current_scope()->set(module_name, std::make_unique<ScopeValue*>(module_scope));
        } else if (_context._current_module != nullptr) {
            _enviroment->get(MODULE_NAME_IF_EXISTS("."), nullptr)->scope_value->set(module_name, std::make_unique<ScopeValue*>(module_scope));
            _enviroment->current_scope()->set(module_name, std::make_unique<ScopeValue*>(module_scope));
        } else {
            _enviroment->global_scope()->set(module_name, std::make_unique<ScopeValue*>(module_scope));
        }

        auto namespace_bk = _context._current_namespace;
        _context._current_namespace = module_scope;

        _enviroment->create_scope(module_name);

        for (Node* node : p_node->nodes) {
            generate(node);
        }
        _enviroment->delete_scope();

        _context._current_namespace = namespace_bk;

        // Just return anything
        return llvm::ConstantInt::get(_builder->getInt8Ty(), 0);
    }

    llvm::Value* Generator::generate_block(BlockNode* p_node) {
        for (Node* node : p_node->exprs) {
            generate(node);
        }

        return llvm::ConstantInt::get(_builder->getInt1Ty(), 0);
    }


    llvm::Value* Generator::generate_if_stmt(IfStatementNode *p_node) {
        #define ELSE_STMT_EXISTS() p_node->else_stmt != NULL

        llvm::Value* inital_value = generate(p_node->stmt);
        GET_BOOL_VALUE(condition, inital_value)

        llvm::Function *TheFunction = _builder->GetInsertBlock()->getParent();
        llvm::BasicBlock* IfBB = llvm::BasicBlock::Create(_builder->getContext(), "btrue", TheFunction);
        llvm::BasicBlock* ElseBB;

        if (ELSE_STMT_EXISTS()) {
            ElseBB = llvm::BasicBlock::Create(_builder->getContext(), "bfalse", TheFunction);
        }

        llvm::BasicBlock* ContinueBB = llvm::BasicBlock::Create(_builder->getContext(), "end", TheFunction);

        _builder->CreateCondBr(condition, IfBB, ELSE_STMT_EXISTS() ? ElseBB : ContinueBB);

        // Generate if statement
        _builder->SetInsertPoint(IfBB);
        _enviroment->create_scope("if$true");

        for (Node* node : p_node->body->exprs) {
            generate(node);
        }

        if (IfBB->size() == 0 || !IfBB->back().isTerminator()) {
            _builder->CreateBr(ContinueBB);
        }

        _enviroment->delete_scope();

        // Generate else statement (if it exist)
        if (ELSE_STMT_EXISTS()) {
            _builder->SetInsertPoint(ElseBB);
            _enviroment->create_scope("if$false");

            for (Node* node : p_node->else_stmt->exprs) {
                generate(node);
            }

            if (ElseBB->size() == 0 || !ElseBB->back().isTerminator()) {
                _builder->CreateBr(ContinueBB);
            }

            _enviroment->delete_scope();
        }

        // Continue with rest of body
        _builder->SetInsertPoint(ContinueBB);
        return ContinueBB;

        #undef ELSE_STMT_EXISTS
    }


    llvm::Value* Generator::generate_import(ImportNode* p_node) {

        std::string module_name;
        std::string module_path;

        if (snowball_utils::endsWith(p_node->path, ".so")) {
            // TODO
        } else if (Library::is_snowball_lib(p_node->path)) {
            if (_enviroment->item_exists(p_node->path)) {
                COMPILER_ERROR(VARIABLE_ERROR, Logger::format("module '%s' is already defined", p_node->path.c_str()))
            }

            if (Library::snlib_is_object(p_node->path)) {
                auto [fn, path] = Library::get_sn_export_lib(p_node->path);
                ScopeValue* mod = fn(_api);

                _linked_libraries.push_back(path);
                _enviroment->current_scope()->set(mangle(p_node->path, {}, true, true), std::make_unique<ScopeValue*>(mod));
                return llvm::ConstantInt::get(_builder->getInt8Ty(), 0);
            } else {
                module_name = p_node->path;
                module_path = Library::get_sn_lib_src(p_node->path);
            }

            _api->context.is_crate = false;
        } else {
            module_path = Library::find_lib_by_path(p_node->path);
            module_name = Library::get_module_name(p_node->path);
            if (module_path.empty()) {
                COMPILER_ERROR(IO_ERROR, Logger::format("Module '%s' not found.", p_node->path.c_str()))
            }
        }

        ScopeValue* module_scope = new ScopeValue(new Scope(module_name, _source_info));
        auto class_struct = llvm::StructType::create(_builder->getContext(), module_name);
        class_struct->setBody({}, true);
        module_scope->llvm_struct = std::make_shared<llvm::StructType *>(class_struct);
        module_scope->module_name = module_name;
        module_scope->type = ScopeType::MODULE;

        auto module_bk = _context._current_module;
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

        _context._current_module = module_bk;
        _source_info = source_bk;
        _api->context.is_crate = true;

        // Just return anything
        return llvm::ConstantInt::get(_builder->getInt8Ty(), 0);
    }

    llvm::Value* Generator::generate_new(NewNode* p_node) {
        std::vector<Type*> arg_types;
        std::vector<llvm::Value*> args;

        int arg_index = 0;
        for (Node* arg : p_node->arguments) {
            llvm::Value* result = generate(arg);
            arg_types.push_back(TypeChecker::to_type(TypeChecker::get_type_name(result->getType())).first);
            args.push_back(result);

            arg_index++;
        }

        Type* class_type = new Type(p_node->method);

        // TODO: check if there are generics
        // TODO: check if class exist and throw custom error
        #define FNAME() GET_FUNCTION_FROM_CLASS(\
            (ADD_MODULE_NAME_IF_EXISTS(".") class_type->mangle()).c_str(), \
                (((std::string)"#") + op2str(OperatorNode::OpType::CONSTRUCTOR)).c_str(), arg_types, true)
        #define FNAME_NO_MANGLE() GET_FUNCTION_FROM_CLASS_NO_MANGLE( \
            (ADD_MODULE_NAME_IF_EXISTS(".") class_type->mangle()), \
                (((std::string)"#") + op2str(OperatorNode::OpType::CONSTRUCTOR)))

        Enviroment::FunctionStore* function_store;
        llvm::Function* function;

        auto unmangled = unmangle(mangle(FNAME()));
        unmangled.isPublic = true;

        auto fn = _enviroment->find_function_if(FNAME_NO_MANGLE(), [=](auto store) -> bool {
            if ((store.node->arguments.size() <= unmangled.arguments.size()) && store.node->has_vargs) {}
            else if (store.node->arguments.size() != unmangled.arguments.size()) return false;
            return TypeChecker::functions_equal(
                store.node->name,
                store.node->name,
                TypeChecker::args2types(store.node->arguments),
                unmangled.arguments,
                unmangled.isPublic,
                store.node->is_public,
                store.node->has_vargs);
        });

        if (fn == nullptr) {
            function = *_enviroment->get(
            FNAME(), p_node, Logger::format(
                "constructor for %s (%s)",
                    class_type->to_string().c_str(),
                    TypeChecker::args_to_string(arg_types).c_str()
                )
            )->llvm_function;
        } else {
            function = (llvm::Function*)paste_function(fn);
        }

        return _builder->CreateCall(function, args);

        #undef FNAME
        #undef FNAME_NO_MANGLE
    }

    llvm::Value* Generator::generate_class(ClassNode* p_node) {
        Type* class_type = new Type(p_node->name);

        // TODO: check for generics
        // TODO: class name mangled if module exists
        Scope* class_scope = new Scope(p_node->name, _source_info);

        auto class_struct = llvm::StructType::create(_builder->getContext(), ADD_MODULE_NAME_IF_EXISTS(".") class_type->mangle());
        ScopeValue* class_scope_val = new ScopeValue(class_scope, std::make_shared<llvm::StructType*>(class_struct));

        std::vector<llvm::Type*> var_types;
        for (VarNode* var : p_node->vars) {
            ScopeValue* type = TypeChecker::get_type(_enviroment, var->vtype, p_node);
            if (!TypeChecker::is_class(type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("'%s' does not reference a class", var->vtype->name.c_str()))
            }

            class_scope_val->properties.push_back({ .name = var->name, .is_public = var->isPublic });
            var_types.push_back(TypeChecker::type2llvm(_builder, (llvm::Type*)(*type->llvm_struct)));
        }

        for (Type* parent : p_node->parents) {
            // COMPILER_ERROR(TODO, "Parents not yet supported!")
            ScopeValue* type = TypeChecker::get_type(_enviroment, parent, p_node);
            if (!TypeChecker::is_class(type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("'%s' does not reference a class", parent->name.c_str()))
            }

            class_scope_val->parents.push_back(parent);
            var_types.insert(var_types.begin(), TypeChecker::type2llvm(_builder, (llvm::Type*)(*type->llvm_struct)));
        }

        std::unique_ptr<ScopeValue*> class_value = std::make_unique<ScopeValue*>(class_scope_val);
        SET_TO_GLOBAL_OR_CLASS(class_type->mangle(), class_value)

        class_struct->setBody(var_types);

        _context._current_class = p_node;
        _context._current_class->name = class_type->mangle();

        for (FunctionNode* func : p_node->functions) {
            generate(func);
        }

        for (OperatorNode* func : p_node->operators) {
            generate(func);
        }

        _context._current_class = nullptr;
        return (llvm::Value*)class_struct;
    }

    llvm::Value* Generator::generate_call(CallNode* p_node) {
        #define FUNCTION_NAME() ( \
            ADD_MODULE_NAME_IF_EXISTS(".") ( \
                (!((!base_struct.empty()) && (class_value->type == ScopeType::CLASS || class_value->type == ScopeType::MODULE))) ? \
                    p_node->method : \
                    Logger::format("%s.%s", base_struct.c_str(), p_node->method.c_str()) \
            ) \
        )

        std::string method_name = p_node->method + "("; // TODO: move "stringified" function to a typechecker function
        std::vector<Type*> arg_types;
        std::vector<std::string> arg_types_str;
        std::vector<llvm::Value*> args;

        std::string base_struct = MODULE_NAME_IF_EXISTS("");
        llvm::Value* base_value;
        ScopeValue* class_value = new ScopeValue();

        // TODO: generics
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
            method_name += TypeChecker::to_type(TypeChecker::get_type_name(result->getType())).first->to_string();

            if ((p_node->arguments.size() > 1) && (arg_index < (p_node->arguments.size() - 1)))
                method_name += ", ";

            arg_index++;
        }

        method_name += ")";

        // Todo: check if method is private / public
        std::string method_call =
            ADD_MODULE_NAME_IF_EXISTS(".") (p_node->base == nullptr ?
            mangle( p_node->method, arg_types) :
            GET_FUNCTION_FROM_CLASS( base_struct.c_str(), p_node->method, arg_types));

        ScopeValue* function;
        Enviroment::FunctionStore* function_store;

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
        } else if ((function_store = _enviroment->find_function_if(FUNCTION_NAME(), [=](auto store) -> bool {
            auto node_args = store.node->arguments;

            if ((!base_struct.empty()) && class_value->type == ScopeType::CLASS) {
                ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(base_struct).first);
                node_args.insert(node_args.begin(), arg);
            }

            if (store.node->is_public) return false;
            if ((node_args.size() <= arg_types.size()) && store.node->has_vargs) {}
            else if (node_args.size() != arg_types.size()) return false;
            if (!store.node->generics.empty()) return true;// If it's generic, return it because it is the only function with the specified name and argument amount in the list (this might be a canditate)
            return TypeChecker::functions_equal(
                store.node->name,
                store.node->name,
                TypeChecker::args2types(node_args),
                arg_types,
                false,
                store.node->is_public,
                store.node->has_vargs);
        }))) {

            auto [args, succ] = TypeChecker::deduce_template_args(function_store->node, arg_types, p_node->generics);
            if (succ) {
                for (int i = 0; i < function_store->node->arguments.size(); i++) {
                    function_store->node->arguments[i]->arg_type = args[i];
                }
            } else {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("Coudn't deduce arguments for '%s'", p_node->method.c_str()))
            }

            paste_function(function_store);
            ScopeValue* private_function = _enviroment->get(method_call, nullptr); // it will exist... right?

            if ((_context._current_module != nullptr && _context._current_module->module_name == base_struct) || (_context._current_class != nullptr && _context._current_class->name == base_struct) || (private_function->parent_scope->name() == SN_GLOBAL_SCOPE)) {
                function = private_function;
                private_method_used = true;
            } else {
                private_method_exists = true;
            }
        }

        if (!private_method_used) {
            method_call =
                (p_node->base == nullptr ?
                mangle(ADD_MODULE_NAME_IF_EXISTS(".") p_node->method, arg_types, true) :
                GET_FUNCTION_FROM_CLASS((ADD_MODULE_NAME_IF_EXISTS(".") base_struct).c_str(), p_node->method, arg_types, true));


            // Look for public
            if (_enviroment->item_exists(method_call)) {
                function = _enviroment->get(method_call, p_node);
            } else if ((function_store = _enviroment->find_function_if(FUNCTION_NAME(), [=](auto store) -> bool {
                // TODO: check if generic is private
                auto node_args = store.node->arguments;

                if ((!base_struct.empty()) && class_value->type == ScopeType::CLASS) {
                    ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(base_struct).first);

                    // TODO: arguments are added after each iteration \_(0_0)_/
                    node_args.insert(node_args.begin(), arg);
                }

                if ((node_args.size() <= arg_types.size()) && store.node->has_vargs) {}
                else if (node_args.size() != arg_types.size()) return false;
                if (!store.node->generics.empty()) return true;// If it's generic, return it because it is the only function with the specified name and argument amount in the list (this might be a canditate)
                return TypeChecker::functions_equal(
                    store.node->name,
                    store.node->name,
                    TypeChecker::args2types(node_args),
                    arg_types,
                    true,
                    store.node->is_public,
                    store.node->has_vargs);
            }))) {

                auto [args, succ] = TypeChecker::deduce_template_args(function_store->node, arg_types, p_node->generics);
                if (succ) {
                    for (int i = 0; i < function_store->node->arguments.size(); i++) {
                        function_store->node->arguments[i]->arg_type = args[i];
                    }
                } else {
                    COMPILER_ERROR(TYPE_ERROR, Logger::format("Coudn't deduce arguments for '%s'", p_node->method.c_str()))
                }

                paste_function(function_store);

                // TODO: error, function not found if it is extern
                function = _enviroment->get(method_call, p_node); // it will exist... right?
            } else {
                FUNCTION_CALL_NOT_FOUND()
            }
        }

        if (function->type != ScopeType::FUNC) {
            COMPILER_ERROR(SYNTAX_ERROR, Logger::format("'%s' is not a function", p_node->method.c_str()))
        }

        ASSERT(args.size() == arg_types.size())
        return _builder->CreateCall(*function->llvm_function, args);

        #undef FUNCTION_NAME
    }

    llvm::Value* Generator::generate_return(ReturnNode* p_node) {
        llvm::Value* value = generate(p_node->value);
        ScopeValue* ret_value = TypeChecker::get_type(_enviroment, p_node->parent->return_type, p_node);
        llvm::Type* left_type; // Function's return type

        std::string ret_type;
        if (TypeChecker::is_class(ret_value)) {
            left_type = TypeChecker::type2llvm(_builder, *ret_value->llvm_struct);
            ret_type = TypeChecker::get_type_name(left_type);
        } else if (ret_value->type == ScopeType::LLVM) {
            left_type = TypeChecker::type2llvm(_builder, (*ret_value->llvm_value)
                ->getType());
            ret_type = TypeChecker::get_type_name(left_type);
        }

        llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, value).first;
        llvm::Type* new_right_type = new_right->getType();

        if ((TypeChecker::get_type_name(new_right_type) == ret_type) ||
            (TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
            (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
            return _builder->CreateRet(new_right);
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
        std::string name = ADD_MODULE_NAME_IF_EXISTS(".") (new Type(p_node->name))->mangle();

        bool found_value = false;
        if (_enviroment->item_exists(p_node->name)) {
            value = _enviroment->get(p_node->name, p_node);

            if (!(_context._current_module != nullptr && value->parent_scope->name() == SN_GLOBAL_SCOPE)) {
                found_value = true;
            }
        } else if (_enviroment->item_exists(name)) {
            value = _enviroment->get(name, p_node);

            if (!(_context._current_module != nullptr && value->parent_scope->name() == SN_GLOBAL_SCOPE)) {
                found_value = true;
            }
        }

        if ((!found_value) && _enviroment->item_exists(ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") p_node->name)) {
            value = _enviroment->get(ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") p_node->name, p_node);
        } else if ((!found_value) && _enviroment->item_exists(ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") name)) {
            value = _enviroment->get(ADD_MODULE_NAME_IF_EXISTS(".") ADD_NAMESPACE_NAME_IF_EXISTS(".") name, p_node);
        } else {
            if (!found_value) {
                COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Identifier %s does not exist!", p_node->name.c_str()))
            }
        }

        switch (value->type)
        {
            case ScopeType::MODULE:
            case ScopeType::NAMESPACE:
            case ScopeType::CLASS: {
                llvm::StructType* type = *value->llvm_struct;
                auto alloca = _builder->CreateAlloca(type);
                alloca->eraseFromParent();
                return alloca;
            }

            case ScopeType::FUNC:
                return (llvm::Value*)(*value->llvm_function);

            case ScopeType::LLVM: {
                llvm::Value* llvalue = *value->llvm_value;
                if (llvm::GlobalValue* G = llvm::dyn_cast<llvm::GlobalValue>(llvalue)) {

                    if (p_node->name.find(".") != std::string::npos) {
                        std::string split = snowball_utils::split(p_node->name, ".").at(0);
                        if ((_context._current_module == nullptr ? true : _context._current_module->module_name != split)) {
                            if (!value->isPublic) {
                                COMPILER_ERROR(VARIABLE_ERROR, Logger::format("Trying to access a private variable from '%s'", split.c_str()))
                            }
                        }
                    }

                    return convert_to_right_value(_builder, G);
                }

                return llvalue;
            }

            default: {
                COMPILER_ERROR(BUG, Logger::format("Invalid Scope Value (idnt: %s, ty: %i).", p_node->name.c_str(), value->type))
            }
        }
    }

    llvm::Value* Generator::generate_operator(BinaryOp* p_node) {
        #define FNAME(opty) GET_FUNCTION_FROM_CLASS(\
            (ADD_MODULE_NAME_IF_EXISTS(".") TypeChecker::get_type_name(left_type)).c_str(), \
                (((std::string)"#") + op2str(opty)).c_str(), { \
                    TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first, \
                    TypeChecker::to_type(TypeChecker::get_type_name(right_type)).first \
                }, true)
        #define FNAME_NO_MANGLE(opty) GET_FUNCTION_FROM_CLASS_NO_MANGLE( \
            (ADD_MODULE_NAME_IF_EXISTS(".") TypeChecker::get_type_name(left_type)), \
                (((std::string)"#") + op2str(opty)))

        llvm::Value* left = generate(p_node->left);

        if (p_node->unary) {
            llvm::Type* left_type = left->getType()->isPointerTy() ? left->getType()->getPointerElementType() : left->getType();

            llvm::Function* function;
            switch (p_node->op_type)
            {
                case OP_NOT: {
                    if (TypeChecker::is_bool(left_type) || TypeChecker::is_number(left_type)) {
                        return _builder->CreateNot(left);
                    }

                    CALL_UNARY_OPERATOR(OperatorNode::OpType::NOT)
                    break;
                }

                default: {
                    COMPILER_ERROR(BUG, Logger::format("The unary operator with type '%i' has not been handled.", p_node->op_type))
                }
            }

            return _builder->CreateCall(function,
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
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFAdd(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateAdd(left, new_right);
                    }

                    CALL_OPERATOR(OperatorNode::OpType::PLUS)
                    break;
                }

                case OP_EQ: {
                    // TODO: if same types (and __eq does not exist) just do _builder->CreateStore()
                    CALL_OPERATOR(OperatorNode::OpType::EQ)
                    break;
                }

                case OP_EQEQ: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFCmpOEQ(left, new_right);
                    } else if (TypeChecker::both_number(left_type, new_right_type, true)) {
                        return _builder->CreateICmpEQ(left, new_right);
                    }

                    CALL_OPERATOR(OperatorNode::OpType::EQEQ)
                    break;
                }

                case OP_NOTEQ: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFCmpONE(left, new_right);
                    } else if (TypeChecker::both_number(left_type, new_right_type, true)) {
                        return _builder->CreateICmpNE(left, new_right);
                    }

                    CALL_OPERATOR(OperatorNode::OpType::NOTEQ)
                    break;
                }

                case OP_LTEQ: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFCmpOLE(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateICmpULE(left, new_right);
                    }

                    CALL_OPERATOR(OperatorNode::OpType::LTEQ)
                    break;
                }

                case OP_MINUS: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFSub(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateSub(left, new_right);
                    }


                    CALL_OPERATOR(OperatorNode::OpType::MINUS)
                    break;
                }

                case OP_MUL: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFMul(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateMul(left, new_right);
                    }

                    CALL_OPERATOR(OperatorNode::OpType::MUL)
                    break;
                }

                case OP_DIV: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFDiv(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateSDiv(left, new_right);
                    }


                    CALL_OPERATOR(OperatorNode::OpType::DIV)
                    break;
                }

                case OP_GT: {
                    llvm::Value* new_right = TypeChecker::implicit_cast(_builder, left_type, right).first;
                    llvm::Type* new_right_type = new_right->getType();

                    if (TypeChecker::is_float(new_right_type) && TypeChecker::is_float(left_type)) {
                        return _builder->CreateFCmpOGT(left, new_right);
                    } else if ((TypeChecker::is_number(left_type) || TypeChecker::is_float(left_type) || TypeChecker::is_bool(left_type)) &&
                    (TypeChecker::is_number(new_right_type) || TypeChecker::is_float(new_right_type) || TypeChecker::is_bool(new_right_type))) {
                        return _builder->CreateICmpSGT(left, new_right);
                    }


                    CALL_OPERATOR(OperatorNode::OpType::GT)
                    break;
                }

                default: {
                    COMPILER_ERROR(BUG, Logger::format("The operator with type '%i' has not been handled.", p_node->op_type))
                }
            }

            return _builder->CreateCall(function,
                {left, right});

            #undef FNAME
            #undef FNAME_NO_MANGLE

        }
    }

    llvm::Value* Generator::generate_function(FunctionNode* p_node) {
        #define IS_ENTRY_POINT() (p_node->name == _SNOWBALL_FUNCTION_ENTRY && p_node->is_lop_level)

        // Skip if the function contains a template

        // TODO: check if generics name already exist as a class or smth

        std::vector<Type*> arg_tnames;
        std::vector<llvm::Type*> arg_types;

        for (ArgumentNode* argument : p_node->arguments) {

            // check if argument is actualy a generic
            auto it = std::find_if(p_node->generics.begin(), p_node->generics.end(), [&](Type* arg) {
                return arg->equals(argument->arg_type);
            });

            if (it == p_node->generics.end()) {

                // check if type exists
                ScopeValue* value = TypeChecker::get_type(_enviroment, argument->arg_type, argument);
                if (!TypeChecker::is_class(value)) {
                    COMPILER_ERROR(ARGUMENT_ERROR, Logger::format("'%s' must be a referece to a class", p_node->name.c_str()))
                }

                llvm::StructType* type = *value->llvm_struct;
                arg_types.push_back(TypeChecker::type2llvm(_builder, type));
                arg_tnames.push_back(argument->arg_type);
            } else {
                arg_tnames.push_back(*it);
            }
        }

        if (_context._current_class != nullptr && !p_node->is_static) {
            // We asume that the class has already been assigned
            arg_types.insert(
                arg_types.begin(),
                ((llvm::Type*)*_enviroment->get(_context._current_class->name, p_node)->llvm_struct)->getPointerTo()
            );

            arg_tnames.insert(arg_tnames.begin(), TypeChecker::to_type(_context._current_class->name).first);
        }

        Enviroment::FunctionStore* store = new Enviroment::FunctionStore();
        store->current_class = _context._current_class;
        store->current_module = _context._current_module;
        store->current_namespace = _context._current_namespace;

        store->node = p_node;

        std::string fname = ADD_MODULE_NAME_IF_EXISTS(".") (_context._current_class == nullptr? p_node->name :
            (
                mangle((ADD_MODULE_NAME_IF_EXISTS(".") (ADD_NAMESPACE_NAME_IF_EXISTS(".")

                (store->current_class == nullptr ? store->node->name : Logger::format(
                    "%s.%s", store->current_class->name.c_str(),
                    store->node->name.c_str()
                )))), arg_tnames, store->node->is_public)
            ));

        if (IS_ENTRY_POINT()) {
            return paste_function(store);
        }

        _enviroment->set_function(fname, store);

        // Function prototype for return statement

        ScopeValue* returnType = TypeChecker::get_type(_enviroment, store->node->return_type, store->node);
        auto retType =
            IS_ENTRY_POINT()
                ? get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder)
                : TypeChecker::type2llvm(_builder, *returnType->llvm_struct);

        auto prototype = llvm::FunctionType::get(retType, arg_types, store->node->has_vargs);
        llvm::Function *function = llvm::Function::Create(
            prototype,
            llvm::Function::ExternalLinkage,
            IS_ENTRY_POINT() ? _SNOWBALL_FUNCTION_ENTRY : (
                store->node->is_extern ? store->node->name : mangle((ADD_MODULE_NAME_IF_EXISTS(".")
                (ADD_NAMESPACE_NAME_IF_EXISTS(".")

                (store->current_class == nullptr ? store->node->name : Logger::format(
                    "%s.%s", store->current_class->name.c_str(),
                    store->node->name.c_str()
                )))), arg_tnames, store->node->is_public)
            ),
            _module);

        return function;

        #undef IS_ENTRY_POINT
    }

    llvm::Value* Generator::generate_variable_decl(VarNode* p_node) {
        // TODO: check if variable is global

        Scope* scope = _enviroment->current_scope();

        if (scope->item_exists( p_node->name) || p_node->name == _enviroment->current_scope()->name()) {
            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("'%s' has already been declared", p_node->name.c_str()))
        }

        if (p_node->isGlobal) {
            if (!(p_node->value->type == Node::Ty::CONST_VALUE)) {
                auto mangled_name = ((std::string)"_GLOBAL__I") + mangle("$SN.$GlobalInit$");
                auto fn = _module->getFunction(mangled_name);

                if (!fn) {
                    auto prototype = llvm::FunctionType::get(_builder->getVoidTy(), {});
                    fn = llvm::Function::Create(
                            prototype,
                            llvm::Function::ExternalLinkage,
                            mangled_name,
                            _module);

                    // Create CTors
                    auto ctors_ty = llvm::StructType::get(_builder->getInt32Ty(), prototype->getPointerTo(), _builder->getInt8PtrTy());
                    llvm::GlobalVariable* ctors_gvar = new llvm::GlobalVariable(/*Module=*/*_module,
                        /*Type=*/llvm::ArrayType::get(ctors_ty, 1),
                        /*isConstant=*/true,
                        /*Linkage=*/llvm::GlobalValue::AppendingLinkage,
                        /*Initializer=*/llvm::ConstantArray::get(llvm::ArrayType::get(ctors_ty, 1),
                            llvm::ConstantStruct::get(ctors_ty, {
                                llvm::ConstantInt::get(_builder->getInt32Ty(), 65535),
                                fn,
                                llvm::ConstantPointerNull::get(_builder->getInt8PtrTy())
                            })
                        ), // has initializer, specified below
                        /*Name=*/"llvm.global_ctors");

                    ctors_gvar->setSection(".ctor");

                    // Create function
                    llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder->getContext(), "body", fn);
                    _builder->SetInsertPoint(body);

                    _builder->CreateRetVoid();

                }

                llvm::BasicBlock& block = fn->getEntryBlock();
                block.back().eraseFromParent();

                _builder->SetInsertPoint(&block);

                auto g_value = generate(p_node->value);
                auto g_type = g_value->getType();
                llvm::GlobalVariable* gvar_ptr = new llvm::GlobalVariable(/*Module=*/*_module,
                    /*Type=*/g_type,
                    /*isConstant=*/false,
                    /*Linkage=*/llvm::GlobalValue::CommonLinkage,
                    /*Initializer=*/0, // has initializer, specified below
                    /*Name=*/(ADD_MODULE_NAME_IF_EXISTS("::") p_node->name));

                gvar_ptr->setInitializer(llvm::Constant::getNullValue(g_type));

                std::unique_ptr<ScopeValue*> scope_val = std::make_unique<ScopeValue*>(
                    new ScopeValue(
                        std::make_shared<llvm::Value*>(
                            gvar_ptr
                        )
                    )
                );

                (*scope_val)->isPublic = p_node->isPublic;
                SET_TO_GLOBAL_OR_CLASS(p_node->name, scope_val);

                _builder->CreateStore(g_value, gvar_ptr);
                _builder->CreateRetVoid();

                return gvar_ptr;
            }

            auto g_value = generate(p_node->value);
            llvm::GlobalVariable* gvar_ptr = new llvm::GlobalVariable(/*Module=*/*_module,
                /*Type=*/TypeChecker::type2llvm(_builder, g_value->getType()),
                /*isConstant=*/false,
                /*Linkage=*/llvm::GlobalValue::ExternalLinkage,
                /*Initializer=*/static_cast<llvm::Constant *>(g_value), // has initializer, specified below
                /*Name=*/(ADD_MODULE_NAME_IF_EXISTS("::") p_node->name));

            std::unique_ptr<ScopeValue*> scope_val = std::make_unique<ScopeValue*>(new ScopeValue(std::make_shared<llvm::Value*>(gvar_ptr)));
            (*scope_val)->isPublic = p_node->isPublic;
            SET_TO_GLOBAL_OR_CLASS(p_node->name, scope_val);

            return gvar_ptr;
        } else {
            llvm::Value* value = generate(p_node->value);
            auto* alloca = _builder->CreateAlloca (value->getType(), nullptr, p_node->name );

            std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(value)));
            _enviroment->current_scope()->set(p_node->name, std::move(scope_value));

            return _builder->CreateStore (value, alloca, /*isVolatile=*/false);
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
                llvm::Constant* value = _builder->CreateGlobalStringPtr(str.c_str(), ".str");
                return value;
            }

            case TokenType::VALUE_BOOL: {
                llvm::Type * i1 = get_llvm_type_from_sn_type(BuildinTypes::BOOL, _builder);
                return llvm::ConstantInt::get(i1, p_node->value == "true");
            }

            case TokenType::VALUE_FLOAT: {
                llvm::Type * f = get_llvm_type_from_sn_type(BuildinTypes::FLOAT, _builder);
                return llvm::ConstantFP::get(f, std::stof(p_node->value));
            }

            default:
                throw SNError(Error::BUG, Logger::format("Const Value with type %s%i%s%s is not yet supported", BCYN, p_node->const_type, RESET, BOLD));
        }
    }

    // utils

    void Generator::generate_contructor_meta(ClassNode* current_class) {
        ASSERT(current_class != nullptr)

        llvm::StructType* type = *_enviroment->get(current_class->name, current_class)->llvm_struct;
        int size = _module->getDataLayout().getTypeStoreSize(type);
        llvm::ConstantInt* size_constant = llvm::ConstantInt::get(_builder->getInt32Ty(), size);

        llvm::Value* alloca_value = _builder->CreateCall(get_alloca(_module, _builder), {size_constant});
        llvm::Value* pointerCast = _builder->CreatePointerCast(alloca_value, type->getPointerTo(), "self");

        std::unique_ptr<ScopeValue*> scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value *>(pointerCast)));
        _enviroment->current_scope()->set("self", std::move(scope_value));

        int var_index = current_class->parents.size();
        for (VarNode* var : current_class->vars) {
            auto p_node = var; // for compiler errors

            auto var_type = TypeChecker::get_type(_enviroment, var->vtype, var);
            if (!TypeChecker::is_class(var_type)) {
                COMPILER_ERROR(TYPE_ERROR, Logger::format("Type %s does not point to a valid type.", var->vtype->to_string().c_str()))
            }

            llvm::Value* value = generate(var->value);

            if (TypeChecker::to_type(TypeChecker::get_type_name(value->getType())).first != var->vtype) {
                auto [cast, succ] = TypeChecker::implicit_cast(_builder, TypeChecker::type2llvm(_builder, *var_type->llvm_struct), value);
                if (!succ) {
                    COMPILER_ERROR(TYPE_ERROR, Logger::format("Can't cast type '%s' to '%s'!", TypeChecker::to_type(TypeChecker::get_type_name(value->getType())).first->to_string().c_str(), var->vtype->to_string().c_str()))
                }

                value = cast;
            }

            llvm::Value* pointer = _builder->CreateInBoundsGEP(pointerCast->getType()->getPointerElementType(), pointerCast, {llvm::ConstantInt::get(_builder->getInt32Ty(), 0), llvm::ConstantInt::get(_builder->getInt32Ty(), var_index)});
            // llvm::Value* load = convert_to_right_value(_builder, pointer);

            _builder->CreateStore(value, pointer);

            var_index++;
        }
    }

    llvm::Value* Generator::paste_function(Enviroment::FunctionStore* store) {
        #define IS_ENTRY_POINT() (store->node->name == _SNOWBALL_FUNCTION_ENTRY && store->node->is_lop_level)
        #define _MODULE_NAME_IF_EXISTS(_sufix) (store->current_module != nullptr ? (store->current_module->module_name + _sufix) : "")
        #define _ADD_MODULE_NAME_IF_EXISTS(_sufix) _MODULE_NAME_IF_EXISTS(_sufix) +
        #define _SET_TO_GLOBAL_OR_CLASS(_name, value) \
            if (store->current_class != nullptr) { \
                _enviroment->get(_ADD_MODULE_NAME_IF_EXISTS(".") store->current_class->name, nullptr)->scope_value->set(_name, std::move(value)); \
            } else if (store->current_namespace != nullptr) { \
                store->current_namespace->scope_value->set(_name, std::move(value)); \
            } else if (store->current_module != nullptr) { \
                store->current_module->scope_value->set(_name, std::move(value)); \
            } else { \
                _enviroment->global_scope()->set(_name, std::move(value)); \
            }

        auto bb_backup = _builder->GetInsertBlock();
        auto cls_backup = _context._current_class;
        auto mod_backup = _context._current_module;
        auto namespace_backup = _context._current_namespace;

        _context._current_class = store->current_class;
        _context._current_module = store->current_module;
        _context._current_namespace = store->current_namespace;
        // Skip if the function contains a template

        std::string llvm_error;
        llvm::raw_string_ostream message_stream(llvm_error);

        ScopeValue* returnType = TypeChecker::get_type(_enviroment, store->node->return_type, store->node);
        auto retType =
            IS_ENTRY_POINT()
                ? get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder)
                : TypeChecker::type2llvm(_builder, *returnType->llvm_struct);

        std::vector<Type*> arg_tnames;
        std::vector<llvm::Type*> arg_types;
        for (ArgumentNode* argument : store->node->arguments) {

            // check if type exists
            ScopeValue* value = TypeChecker::get_type(_enviroment, argument->arg_type, argument);
            if (!TypeChecker::is_class(value)) {
                FunctionNode* p_node = store->node; // for DBGInfo
                COMPILER_ERROR(ARGUMENT_ERROR, Logger::format("'%s' must be a referece to a class", store->node->name.c_str()))
            }

            llvm::StructType* type = *value->llvm_struct;

            arg_types.push_back(TypeChecker::type2llvm(_builder, type));
            arg_tnames.push_back(TypeChecker::to_type(type->getName().str()).first);
        }

        if (store->current_class != nullptr && store->node->name != op2str(OperatorNode::OpType::CONSTRUCTOR) && !store->node->is_static) {
            // We asume that the class has already been assigned
            arg_types.insert(
                arg_types.begin(),
                ((llvm::Type*)*_enviroment->get(store->current_class->name, store->node)->llvm_struct)->getPointerTo()
            );
            arg_tnames.insert(arg_tnames.begin(), TypeChecker::to_type(store->current_class->name).first);
        }

        std::string fname = IS_ENTRY_POINT() ? _SNOWBALL_FUNCTION_ENTRY : (store->node->is_extern ? store->node->name : mangle(
            (_ADD_MODULE_NAME_IF_EXISTS(".")
                ADD_NAMESPACE_NAME_IF_EXISTS(".")

                (store->current_class == nullptr ? store->node->name : Logger::format(
                    "%s.%s", store->current_class->name.c_str(),
                    store->node->name.c_str()
                ))), arg_tnames, store->node->is_public));


        auto prototype = llvm::FunctionType::get(retType, arg_types, store->node->has_vargs);
        auto function = (llvm::Function*)_module->getOrInsertFunction(fname, prototype).getCallee();

        std::unique_ptr<ScopeValue*> func_scopev = std::make_unique<ScopeValue*>(new ScopeValue(std::make_shared<llvm::Function*>(function)));
        (*func_scopev)->isStaticFunction = store->node->is_static;
        (*func_scopev)->hasVArg = store->node->has_vargs;
        (*func_scopev)->isPublic = store->node->is_public;
        (*func_scopev)->arguments = arg_tnames;
        _SET_TO_GLOBAL_OR_CLASS(mangle(
                store->node->name, arg_tnames, store->node->is_public), func_scopev);

        Scope* current_scope = _enviroment->create_scope(store->node->name);

        int parameter_index = store->current_class != nullptr ? 0 : 1;
        for (auto& arg : function->args()) {
            std::string name;
            if (store->current_class != nullptr && store->node->name != "__init" && parameter_index == 0 && !store->node->is_static) /* self argument */ {
                name = "self";
            } else {
                name = store->node->arguments.at(parameter_index == 0 ? 0 : parameter_index-1)->name;
            }

            if (store->current_class != nullptr && parameter_index>0 && name == "self") {
                FunctionNode* p_node = store->node; // for DBGInfo
                COMPILER_ERROR(SYNTAX_ERROR, "Class method can't contain self as a parameter")
            }

            arg.setName(name);

            std::unique_ptr<ScopeValue*> param_scope_value = std::make_unique<ScopeValue*>(new ScopeValue(std::make_unique<llvm::Value*>(&arg)));
            current_scope->set(name, std::move(param_scope_value));

            parameter_index++;
        }

        // BODY GENERATION

        if (!store->node->is_foward) {
            llvm::BasicBlock *body = llvm::BasicBlock::Create(_builder->getContext(), "body", function);
            _builder->SetInsertPoint(body);

            if (store->current_class != nullptr && store->node->name == op2str(OperatorNode::OpType::CONSTRUCTOR) && !store->node->is_static) {
                generate_contructor_meta(store->current_class);
            }

            for (auto expr : store->node->body->exprs) {
                generate(expr);
            }

            auto bb = _builder->GetInsertBlock();

            if (bb->size() == 0 || !bb->back().isTerminator()) {
                if (IS_ENTRY_POINT()) {
                    llvm::Type * i32 = _builder->getInt32Ty();
                    _builder->CreateRet(llvm::ConstantInt::get(i32, 0));
                } else if (store->current_class != nullptr && store->node->name == op2str(OperatorNode::OpType::CONSTRUCTOR)) {
                    _builder->CreateRet(*current_scope->get("self", nullptr)->llvm_value);
                } else if (retType->isVoidTy()) {
                    _builder->CreateRet(nullptr);
                } else {
                    FunctionNode* p_node = store->node; // for DBGInfo
                    COMPILER_ERROR(FUNCTION_RET_ERR, Logger::format("Function '%s' does not have a return statement for all paths!", p_node->name.c_str()))
                }
            }
        }

        llvm::verifyFunction(*function, &message_stream);
        if (!llvm_error.empty()) {
            _module->print(llvm::outs(), nullptr);
            FunctionNode* p_node = store->node; // for DBGInfo
            COMPILER_ERROR(LLVM_INTERNAL, llvm_error)
        }

        _enviroment->delete_scope();
        _builder->SetInsertPoint(bb_backup);

        _context._current_class = cls_backup;
        _context._current_module = mod_backup;
        _context._current_namespace = namespace_backup;
        return function;

        #undef _MODULE_NAME_IF_EXISTS
        #undef _ADD_MODULE_NAME_IF_EXISTS
        #undef _SET_TO_GLOBAL_OR_CLASS
        #undef IS_ENTRY_POINT

    }

    llvm::Value* Generator::convert_to_right_value(std::shared_ptr<llvm::IRBuilder<>> p_builder, llvm::Value* value) {

        auto type = value->getType();
        return p_builder->CreateLoad((type->isPointerTy()) ? type->getPointerElementType() : type, value);
    }
}

#undef MODULE_NAME_IF_EXISTS
#undef ADD_MODULE_NAME_IF_EXISTS
#undef SET_TO_GLOBAL_OR_CLASS
#undef IS_ENTRY_POINT
#undef CALL_OPERATOR