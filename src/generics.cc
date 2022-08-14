
#include "snowball/snowball.h"
#include "snowball/generics.h"
#include "snowball/generics.h"
#include "snowball/utils/utils.h"

#include <algorithm>
#include <map>
#include <vector>

namespace snowball {
    class Generics;

    void Generics::add_generic(std::string p_name, std::vector<Type*> p_args, Type* ret, std::vector<Type*> p_generics, Node* p_node) {
        GenericStore* store = new GenericStore();

        store->name = p_name;
        store->args = p_args;
        store->return_ty = ret;
        store->generics = p_generics;
        store->node = (FunctionNode*)p_node;

        if (std::find_if(_stores.begin(), _stores.end(), [store](GenericStore* p_store) {
            return (store->name == p_store->name && store->args == p_store->args);
        }) != _stores.end()) {
            DBGSourceInfo* dbg_info = new DBGSourceInfo(_compiler->get_source_info(), p_node->pos, p_node->width);
            throw CompilerError(Error::VARIABLE_ERROR, Logger::format("Generic function '%s' has already been defined", unmangle(store->name).name.c_str()), dbg_info);
        }

        _stores.push_back(store);
    }

    std::pair<Generics::GenericValue, bool> Generics::get_generic(std::string p_name, std::vector<Type*> p_args, std::vector<Type*> p_generics, Node* p_node) {
        for (const auto& store : _stores) {

            unmangledResult unmangled = unmangle(p_name);

            // TODO: fix generics not found!!!!!!
            if (store->generics.size() == p_generics.size() && p_args.size() == store->args.size() && unmangled.isPublic == store->node->is_public) {
                std::map<std::string, Type*> completed_generics;
                for (int generic_index = 0; generic_index < p_generics.size(); generic_index++) {
                    completed_generics.insert({TypeChecker::to_mangle(store->generics[generic_index]), p_generics[generic_index]});
                }

                std::vector<Type*> function_args;
                for (Type* st_arg : store->args) {
                    std::map<std::string, Type*>::iterator argument = completed_generics.find(TypeChecker::to_mangle(st_arg));
                    function_args.push_back(argument != completed_generics.end() ? argument->second : st_arg);
                }

                ASSERT(store->node->arguments.size() == function_args.size())
                if (function_args == p_args) {
                    FunctionNode* node = new FunctionNode();
                    std::map<std::string, Type*>::iterator ret_ty = completed_generics.find(TypeChecker::to_mangle(store->return_ty));

		            std::vector<ArgumentNode *> arguments;
                    for (int i = 0; i < function_args.size(); i++) {
                        arguments.push_back(new ArgumentNode(store->node->arguments[i]->name, function_args[i]));
                    }

                    node->name = unmangle(p_name).name;

                    node->is_static = store->node->is_static;
                    node->is_public = store->node->is_public;
                    node->has_return = store->node->has_return;
                    node->is_lop_level = store->node->is_lop_level;

                    node->body = store->node->body;
                    node->arguments = arguments;

                    node->generic_map = completed_generics;

                    node->return_type = (
                        ret_ty != completed_generics.end() ?
                            ret_ty->second :
                            store->return_ty
                    );

                    GenericValue result;

                    result.node = node;
                    result.name = unmangle(p_name).name;
                    result.args = function_args;
                    result.return_ty = node->return_type;

                    return { result, true };
                }
            }
        }

        GenericValue dummy;
        return { dummy, false };
    }
}
