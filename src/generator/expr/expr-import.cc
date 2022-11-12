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

// FUTURE MAURO:
// - add prefix to functions inside `_enviroment->_functions` and variables
// - create a "global" scope (scope n 1) and generate "true global" (scope n 0) for Strings, etc...
// - emit llvm with module prefix

namespace snowball {
    llvm::Value* Generator::generate_import(ImportNode* p_node) {

        std::string module_name;
        std::string module_path;

        bool sn_lib_found = false;
        auto bk_context = _api->context;

        if (snowball_utils::endsWith(p_node->path, ".so")) {
            // TODO
        } else if (Library::is_snowball_lib(p_node->path)) {
            // Here, we check if the given path is a built in snowball library
            // e.g. System, Math, etc...
            // By doing this, we prevent the core libraries to be re-placen by
            // third party libraries the user has installed.

            // If library is a compiled object file, we don't need to
            // process it as a normal .sn file, we can just call the
            // "sn_export" function.
            if (Library::snlib_is_object(p_node->path)) {

                auto module_identifier = Logger::format("$sn_core:%s", p_node->path.c_str());
                auto existant_module = _enviroment->modules.find(module_identifier);
                if (existant_module != _enviroment->modules.end()) {
                    _enviroment->current_scope()->set(mangle(p_node->path, {}, true, true), std::make_unique<ScopeValue*>(existant_module->second));
                } else {
                    auto [fn, path] = Library::get_sn_export_lib(p_node->path);
                    ScopeValue* mod = fn(_api);

                    _linked_libraries.push_back(path);
                    _enviroment->current_scope()->set(mangle(p_node->path, {}, true, true), std::make_unique<ScopeValue*>(mod));

                    _enviroment->modules.insert({ module_identifier, mod });
                }

                sn_lib_found = true;
            } else {
                module_name = p_node->path;
                module_path = Library::get_sn_lib_src(p_node->path);
            }

            // This is used to differentiate between the main program and
            // third party/core modules
            _api->context.is_crate = false;
        } else {
            module_path = Library::find_lib_by_path(p_node->path);
            module_name = Library::get_module_name(p_node->path);
            DUMP_S(module_name.c_str())
        }

        // Module path will be empty if the module wasn't found
        if (module_path.empty() && (!sn_lib_found)) {
            COMPILER_ERROR(IO_ERROR, Logger::format("Module '%s' not found.", p_node->path.c_str()))
        } else if (_enviroment->item_exists(module_name)) {
            COMPILER_ERROR(VARIABLE_ERROR, Logger::format("module '%s' is already defined", p_node->path.c_str()))
        }

        // note: sn_lib_found means that
        //  the object file of a core module
        //  has been found. It does not mean
        //  that the path has not been found
        if (!sn_lib_found) {

            auto existant_module = _enviroment->modules.find(module_path);
            bool module_already_exists = existant_module != _enviroment->modules.end();
            if (module_already_exists) {
                _enviroment->current_scope()->set(mangle(module_path, {}, true, true), std::make_unique<ScopeValue*>(existant_module->second));
            }

            // Save the latest state of the enviroment and set the module
            // as a new global. note that global != global types.
            auto scope_state = _enviroment->save_state(false);
            auto module_data = _enviroment->create_scope(Logger::format("$current_module:%s", module_path.c_str()));

            ScopeValue* module_scope = new ScopeValue(module_data);

            if (!module_already_exists) {
                _enviroment->modules.insert({ module_path, module_scope });

                // Create a struct for the only purpose of geting it's type name.
                // this struct will not be used in any way, just as a helper.
                auto class_struct = llvm::StructType::create(_builder->getContext(), module_name);

                // Set an empty body in order to declare it.
                class_struct->setBody({}, true);

                // Fill out scope's information.
                module_scope->llvm_struct = std::make_shared<llvm::StructType *>(class_struct);
                module_scope->module_name = module_name;
                module_scope->type = ScopeType::MODULE;

                // Get last module and save it as a backup to restore it later.
                // We also set it as context in order to tell the Gernator that
                // we are generating insdie a module.
                auto module_bk = _context._current_module;
                _context._current_module = module_scope;

                // CREATE MODULE
                // TODO: new loading bar for modules as status
                SourceInfo* source_bk = _source_info;

                std::ifstream ifs(module_path);
                if (ifs.fail()) {
                    // TODO: better error because if the path didn't exist,
                    //       it woudve had checked much before.
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

                _enviroment->delete_scope();

                // Restore the last saved state and set the module
                // to the current scope (in order to avoid conflicts,
                // we are not adding it to the global scope)
                _enviroment->restore_state(scope_state, false);
                _enviroment->current_scope()->set(module_name, std::make_unique<ScopeValue*>(module_scope));
            }
        }

        _api->context.is_crate = bk_context.is_crate;

        // We don't need to return anything as "import" can't be in assigments.
        return llvm::ConstantInt::get(_builder->getInt8Ty(), 0);
    }
}