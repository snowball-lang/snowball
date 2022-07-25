
#include "snowball/snowball.h"
#include "snowball/generics.h"
#include "snowball/generics.h"
#include "snowball/utils/utils.h"

#include <algorithm>
#include <map>
#include <vector>

namespace snowball {
    class Generics;

    void Generics::add_generic(std::string p_name, std::vector<std::string> p_args, std::string ret, std::vector<std::string> p_generics, Node* p_node) {
        GenericStore* store = new GenericStore();

        store->name = p_name;
        store->args = p_args;
        store->return_ty = ret;
        store->generics = p_generics;
        store->node = (FunctionNode*)p_node;

        _stores.push_back(store);
    }

    Generics::GenericValue Generics::get_generic(std::string p_name, std::vector<std::string> p_args, std::vector<std::string> p_generics, Node* p_node) {
        for (const auto& store : _stores) {

            if (store->generics.size() == p_generics.size() && p_args.size() == store->args.size()) {
                std::map<std::string, std::string> completed_generics;
                for (int generic_index = 0; generic_index < p_generics.size(); generic_index++) {
                    completed_generics.insert({store->generics[generic_index], p_generics[generic_index]});
                }

                std::vector<std::string> function_args;
                for (std::string st_arg : store->args) {
                    std::map<std::string, std::string>::iterator argument = completed_generics.find(st_arg);
                    function_args.push_back(argument != completed_generics.end() ? argument->second : st_arg);
                }

                ASSERT(store->node->arguments.size() == function_args.size())
                if (function_args == p_args) {
                    FunctionNode* node = new FunctionNode();
                    std::map<std::string, std::string>::iterator ret_ty = completed_generics.find(store->return_ty);

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

                    return result;
                }
            }
        }

        std::string args;
        int arg_index = 0;
        for (std::string arg : p_args) {
            args += arg;
            if (arg_index < (p_args.size()-1)) {
                args += ", ";
            }
        }

        // TODO: output with generics inside <>

        DBGSourceInfo* dbg_info = new DBGSourceInfo(_compiler->get_source_info(), p_node->pos, p_node->width);
        throw CompilerError(Error::VARIABLE_ERROR, Logger::format("'%s(%s)' is not defined", unmangle(p_name).name.c_str(), args.c_str()), dbg_info);
    }
}
