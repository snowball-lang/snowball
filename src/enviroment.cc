
#include "snowball/types.h"
#include "snowball/errors.h"
#include "snowball/scopes.h"
#include "snowball/enviroment.h"
#include "snowball/utils/mangle.h"

#include <llvm-10/llvm/Support/raw_ostream.h>
#include <llvm/IR/Type.h>

#include <memory>
#include <numeric>
#include <sstream>
#include <algorithm>

namespace snowball_utils {
    template <typename Iter>
    std::string join(Iter begin, Iter end, std::string const& separator)
    {
        std::ostringstream result;
        if (begin != end)
            result << *begin++;
        while (begin != end)
            result << separator << *begin++;
        return result.str();
    }
}

namespace snowball {
    Enviroment::Enviroment(SourceInfo* p_source_info) : _source_info(p_source_info) {
        Scope* global_scope = new Scope("__sn__global__", _source_info);
        _scopes.push_back(global_scope);
    }

    ScopeValue* Enviroment::get(std::string name, Node* p_node, std::string p_o_name) {

        if (p_o_name.empty()) p_o_name = name;

        size_t pos_start = 0, pos_end, delim_len = 1;
        std::string token;
        std::vector<std::string> parts;

        while ((pos_end = name.find (".", pos_start)) != std::string::npos) {
            token = name.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            parts.push_back (token);
        }

        parts.push_back (name.substr (pos_start));
        if (parts.size() > 1) {
            ScopeValue* scope = get(parts[0], p_node, p_o_name);
            if (scope->type == ScopeType::SCOPE || scope->type == ScopeType::CLASS || scope->type == ScopeType::MODULE) {
                return scope->scope_value->get(snowball_utils::join(++parts.begin(), parts.end(), "."), p_node, p_o_name);
            }
        }

        std::vector<Scope*> reversed_scopes = _scopes;
        std::reverse(reversed_scopes.begin(), reversed_scopes.end());

        for (Scope* scope : reversed_scopes) {
            bool value = scope->item_exists(name);

            if (value) {
                return scope->get(name, p_node, p_o_name);
            }
        }

        if (p_node == nullptr) {
            throw SNError(Error::BUG, Logger::format("'%s' is not defined (p_node has not been passed to Enviroment::get)", p_o_name.c_str()));
        }

        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
        throw CompilerError(Error::VARIABLE_ERROR, Logger::format("'%s' is not defined", p_o_name.c_str()), dbg_info);
    }

    bool Enviroment::item_exists(std::string name) {
        size_t pos_start = 0, pos_end, delim_len = 1;
        std::string token;
        std::vector<std::string> parts;

        while ((pos_end = name.find (".", pos_start)) != std::string::npos) {
            token = name.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            parts.push_back (token);
        }

        parts.push_back (name.substr (pos_start));
        if (parts.size() > 1) {
            if (item_exists(parts[0])) {
                ScopeValue* scope = get(parts[0], nullptr);
                if (scope->type == ScopeType::SCOPE || scope->type == ScopeType::CLASS || scope->type == ScopeType::MODULE) {
                    return scope->scope_value->item_exists(snowball_utils::join(++parts.begin(), parts.end(), "."));
                }
            }
        }

        std::vector<Scope*> reversed_scopes = _scopes;
        std::reverse(reversed_scopes.begin(), reversed_scopes.end());

        for (Scope* scope : reversed_scopes) {
            bool value = scope->item_exists(name);

            if (value) {
                return true;
            }
        }

        return false;
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

    Scope* Enviroment::create_scope(Scope* p_scope) {
        _scopes.push_back(p_scope);
        return current_scope();
    }

    #if _SNOWBALL_SYMTABLE_DEBUG
    void Enviroment::debug(Scope* current_scope, int depth) {
        std::map<std::string, std::unique_ptr<ScopeValue*>> scope = (current_scope == nullptr ? std::move(_scopes.at(0)->data()) : std::move(current_scope->data()));
        std::map<std::string, std::unique_ptr<ScopeValue*>>::iterator it;
        for (it = scope.begin(); it != scope.end(); it++) {
            DEBUG_SYMTABLE("%s", it->first.c_str())

            if ((*it->second)->type == ScopeType::CLASS || (*it->second)->type == ScopeType::SCOPE || (*it->second)->type == ScopeType::MODULE) {
                debug((*it->second)->scope_value, depth+1);
            } else if ((*it->second)->type == ScopeType::FUNC_CONTAINER) {
                for (int i = 0; i < (*it->second)->instances.size(); i++) {
                    ScopeValue* scope_value = *(*it->second)->instances[i];
                    DEBUG_SYMTABLE("    %s", (*scope_value->llvm_function)->getName())
                }
            }
        }
    }
    #endif

    void Enviroment::delete_scope() {
        _scopes.pop_back();
    }
}
