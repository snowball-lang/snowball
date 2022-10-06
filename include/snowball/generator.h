
#include "types.h"
#include "parser.h"
#include "enviroment.h"
#include "source_info.h"

#include <memory>

#include <llvm/IR/IRBuilder.h>

#ifndef __SNOWBALL_GENERATOR_H_
#define __SNOWBALL_GENERATOR_H_

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
