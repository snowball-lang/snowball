
#include "snowball/nodes.h"
#include "snowball/errors.h"
#include "snowball/scopes.h"
#include "snowball/utils/mangle.h"
#include "snowball/utils/utils.h"

#include <llvm/Support/raw_ostream.h>
#include <memory>
#include <optional>

#include <llvm/IR/Function.h>

namespace snowball {
    Scope::Scope(std::string p_scope_name, SourceInfo* p_source_info)
        : _source_info(p_source_info), _scope_name(p_scope_name) {
        }

    bool Scope::item_exists(std::string p_name) {
        size_t pos_start = 0, pos_end, delim_len = 1;
        std::string token;
        std::vector<std::string> parts;

        while ((pos_end = p_name.find (".", pos_start)) != std::string::npos) {
            token = p_name.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            parts.push_back (token);
        }

        parts.push_back (p_name.substr (pos_start));
        if (parts.size() > 1) {
            if (item_exists(parts[0])) {
                ScopeValue* scope = get(parts[0], nullptr);
                if (scope->type == ScopeType::SCOPE || scope->type == ScopeType::NAMESPACE || scope->type == ScopeType::CLASS || scope->type == ScopeType::MODULE) {
                    return scope->scope_value->item_exists(snowball_utils::join(++parts.begin(), parts.end(), "."));
                }
            }
        }

        unmangledResult result = unmangle(p_name);

        std::map<std::string, std::unique_ptr<ScopeValue*>>::iterator _it = this->_data.find(result.name);
        if (_it != this->_data.end() && result.isMangled && result.isFunction && (*_it->second)->type == ScopeType::FUNC_CONTAINER) {
            for (int i = 0; i < (*_it->second)->instances.size(); i++) {
                ScopeValue* scope_value = *(*_it->second)->instances[i];
                // TODO: check for argv and default values
                if (TypeChecker::functions_equal(result.name, result.name, result.arguments, scope_value->arguments, result.isPublic, scope_value->isPublic, scope_value->hasVArg)) {
                    return true;
                }
            }

            return false;
        }

        return this->_data.find(p_name) != this->_data.end();
    }

    ScopeValue* Scope::get(std::string p_name, Node* p_node, std::string p_o_name) {

        if (p_o_name.empty()) p_o_name = p_name;

        size_t pos_start = 0, pos_end, delim_len = 1;
        std::string token;
        std::vector<std::string> parts;

        while ((pos_end = p_name.find (".", pos_start)) != std::string::npos) {
            token = p_name.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            parts.push_back (token);
        }

        parts.push_back (p_name.substr (pos_start));
        if (parts.size() > 1) {
            ScopeValue* scope = get(parts[0], p_node, p_o_name);
            if (scope->type == ScopeType::SCOPE || scope->type == ScopeType::NAMESPACE || scope->type == ScopeType::CLASS || scope->type == ScopeType::MODULE) {
                return scope->scope_value->get(snowball_utils::join(++parts.begin(), parts.end(), "."), p_node, p_o_name);
            }
        }

        bool _value = item_exists(p_name);

        if (!_value) {
            if (p_node == nullptr)
                throw SNError(
                    Error::VARIABLE_ERROR,
                    Logger::format("Undefined variable: %s%s%s%s (no p_node has been passed to Scope::get)", BCYN, p_o_name.c_str(), RESET, BOLD)
                );

            DBGSourceInfo* dbg_info = new DBGSourceInfo(_source_info, p_node->pos, p_node->width);
            throw CompilerError(Error::UNDEFINED_VARIABLE, Logger::format("Undefined variable: %s%s%s%s", BCYN, p_o_name.c_str(), RESET, BOLD), dbg_info);
        }

        unmangledResult unmangled = unmangle(p_name);

        std::map<std::string, std::unique_ptr<ScopeValue*>>::iterator _it = this->_data.find(unmangled.name);
        if (_it != this->_data.end() && unmangled.isMangled && unmangled.isFunction && (*_it->second)->type == ScopeType::FUNC_CONTAINER) {
            for (int i = 0; i < (*_it->second)->instances.size(); i++) {
                ScopeValue* scope_value = *(*_it->second)->instances[i];

                // TODO: (re-write) check for argv and default values
                if (TypeChecker::functions_equal(unmangled.name, unmangled.name, unmangled.arguments, scope_value->arguments, unmangled.isPublic, scope_value->isPublic, scope_value->hasVArg)) {
                    return scope_value;
                }
            }
        }

        return *_data.find(p_name)->second;
    }


    void Scope::set(std::string p_name, std::unique_ptr<ScopeValue*> p_value) {
        (*p_value)->parent_scope = std::move(this);

        if ((*p_value)->type == ScopeType::FUNC) {
            unmangledResult result = unmangle(p_name);

            if (result.isMangled && result.isFunction) {
                if (item_exists(result.name)) {
                    (*(*this->_data.find(result.name)).second)->instances.push_back(std::move(p_value));
                    return;
                }

                ScopeValue* container = new ScopeValue(ScopeType::FUNC_CONTAINER);

                container->parent_scope = std::move(this);

                container->instances.push_back(std::move(p_value));

                this->_data.emplace( result.name, std::make_unique<ScopeValue*>(container) );

                return;
            }
        }

        this->_data.emplace ( p_name, std::move(p_value) );
    }

}
