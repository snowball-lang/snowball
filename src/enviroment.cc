
#include "snowball/errors.h"
#include "snowball/scopes.h"
#include "snowball/enviroment.h"

#include <algorithm>

namespace snowball {
    Enviroment::Enviroment(SourceInfo* p_source_info) : _source_info(p_source_info) {
        _scopes.push_back(new Scope("__sn__global__", _source_info));
    }

    ScopeValue Enviroment::get(std::string name, Node p_node) {

        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node.pos, p_node.width);
        size_t pos_start = 0, pos_end, delim_len = 1;
        std::string token;
        std::vector<std::string> parts;

        while ((pos_end = p_node.name.find (".", pos_start)) != std::string::npos) {
            token = p_node.name.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            parts.push_back (token);
        }

        parts.push_back (p_node.name.substr (pos_start));

        if (parts.size() > 1) {
            auto scope = get(parts[0], p_node);

            // TODO: check if scope is NULL
            return scope;
        }

        std::vector<Scope*> reversed_scopes = _scopes;
        std::reverse(reversed_scopes.begin(), reversed_scopes.end());

        for (Scope* scope : reversed_scopes) {
            bool value = scope->item_exists(p_node.name);

            if (value) {
                return scope->get(p_node.name, p_node);
            }
        }

        throw CompilerError(Error::VARIABLE_ERROR, Logger::format("'%s' is not defined", p_node.name.c_str()), dbg_info);
    }

    Scope* Enviroment::global_scope() {
        return _scopes.at(0);
    }

    Scope* Enviroment::current_scope() {
        return _scopes.at(_scopes.size()-1);
    }

    Scope* Enviroment::create_scope(std::string p_name) {
        _scopes.push_back(new Scope(p_name, _source_info));
        return current_scope();
    }

    void Enviroment::delete_scope() {
        _scopes.pop_back();
    }
}
