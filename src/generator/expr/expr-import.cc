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
}