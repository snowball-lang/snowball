
#include "types.h"
#include "parser.h"
#include "enviroment.h"
#include "source_info.h"

#include <memory>

#include <llvm/IR/IRBuilder.h>

#ifndef __SNOWBALL_GENERATOR_H_
#define __SNOWBALL_GENERATOR_H_

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
    auto __f = _enviroment->find_function_if(FNAME_NO_MANGLE(opty), [=](auto store) -> std::pair<bool, bool> { \
        auto node_args = store.node->arguments; \
        ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first); \
        node_args.insert(node_args.begin(), arg); \
        if ((node_args.size() <= __u.arguments.size()) && store.node->has_vargs) {} \
        else if (node_args.size() != __u.arguments.size()) return {false, false}; \
        return TypeChecker::functions_equal( \
            store.node->name, \
            store.node->name, \
            TypeChecker::args2types(node_args), \
            __u.arguments, \
            __u.isPublic, \
            store.node->is_public, \
            store.node->has_vargs); \
    }, p_node); \
    if (__f == nullptr) { \
        function = *_enviroment->get( \
        GET_FUNCTION_FROM_CLASS( \
            TypeChecker::get_type_name(left_type).c_str(), \
            Logger::format("#%s", op2str(opty).c_str()), \
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
    auto __f = _enviroment->find_function_if(FNAME_NO_MANGLE(opty), [=](auto store) -> std::pair<bool, bool> { \
        auto node_args = store.node->arguments; \
        ArgumentNode* arg = new ArgumentNode("self", TypeChecker::to_type(TypeChecker::get_type_name(left_type)).first); \
        node_args.insert(node_args.begin(), arg); \
        if ((node_args.size() <= __u.arguments.size()) && store.node->has_vargs) {} \
        else if (node_args.size() != __u.arguments.size()) return {false, false}; \
        return TypeChecker::functions_equal( \
            store.node->name, \
            store.node->name, \
            TypeChecker::args2types(node_args), \
            __u.arguments, \
            __u.isPublic, \
            store.node->is_public, \
            store.node->has_vargs); \
    }, p_node); \
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

    class SNAPI;

    class Generator {

        public:
            Generator(
                SNAPI* p_api,
                Parser* p_parser,
                Enviroment* p_enviroment,
                SourceInfo* p_source_info,
                std::shared_ptr<llvm::IRBuilder<>> p_builder,
                llvm::Module* p_module,
                std::vector<std::string>& p_linked_libraries,
                bool p_testsEnabled = false)
                  :
                    _module(p_module),
                    _parser(p_parser),
                    _enviroment(p_enviroment),
                    _tests_enabled(p_testsEnabled),
                    _linked_libraries(p_linked_libraries),
                    _api(p_api) {
                _source_info = p_source_info;
                _builder = p_builder;
            };

            llvm::Value* generate(Node* p_node);

            ~Generator() {};

        private:
            SNAPI* _api;
            Parser* _parser;
            bool _tests_enabled;

            llvm::Module* _module;
            Enviroment* _enviroment;
            SourceInfo* _source_info;

            std::shared_ptr<llvm::IRBuilder<>> _builder;

            std::vector<std::string>& _linked_libraries;

            // some context
            struct {
                ScopeValue* _current_module = nullptr;
                ScopeValue* _current_namespace = nullptr;
                ClassNode* _current_class = nullptr;
            } _context;

            // methods
            llvm::Value* generate_new(NewNode* p_node);
            llvm::Value* generate_call(CallNode* p_node);
            llvm::Value* generate_cast(CastNode* p_node);
            llvm::Value* generate_index(IndexNode* p_node);
            llvm::Value* generate_class(ClassNode* p_node);
            llvm::Value* generate_block(BlockNode * p_node);
            llvm::Value* generate_import(ImportNode* p_node);
            llvm::Value* generate_operator(BinaryOp* p_node);
            llvm::Value* generate_module(ModuleNode* p_node);
            llvm::Value* generate_return(ReturnNode* p_node);
            llvm::Value* generate_function(FunctionNode* p_node);
            llvm::Value* generate_variable_decl(VarNode* p_node);
            llvm::Value* generate_operator(OperatorNode* p_node);
            llvm::Value* generate_attribute(AttributeNode* p_node);
            llvm::Value* generate_if_stmt(IfStatementNode *p_node);
            llvm::Value* generate_identifier(IdentifierNode* p_node);
            llvm::Value* generate_const_value(ConstantValue* p_node);

            // utils
            void generate_contructor_meta(ClassNode* current_class);

        public:
            llvm::Value* paste_function(Enviroment::FunctionStore* p_node);
            static llvm::Value* convert_to_right_value(std::shared_ptr<llvm::IRBuilder<>> p_builder, llvm::Value* value);
    };
}

#endif // __SNOWBALL_GENERATOR_H_
