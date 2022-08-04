
#include "snowball/nodes.h"
#include "snowball/errors.h"
#include "snowball/scopes.h"
#include "snowball/utils/mangle.h"

#include <llvm-10/llvm/Support/raw_ostream.h>
#include <memory>
#include <optional>

#include <llvm/IR/Function.h>

namespace snowball {
    Scope::Scope(std::string p_scope_name, SourceInfo* p_source_info)
        : _source_info(p_source_info), _scope_name(p_scope_name) {
        }

    bool Scope::item_exists(std::string p_name) {
        unmangledResult result = unmangle(p_name);

        std::map<std::string, std::unique_ptr<ScopeValue*>>::iterator _it = this->_data.find(result.name);
        if (_it != this->_data.end() && result.isMangled && (*_it->second)->type == ScopeType::FUNC_CONTAINER) {
            for (int i = 0; i < (*_it->second)->instances.size(); i++) {
                ScopeValue* scope_value = *(*_it->second)->instances[i];

                // TODO: (re-write) check for argv and default values
                if (result.arguments == scope_value->arguments) {
                    if (result.isPublic == scope_value->isPublic) {
                        return true;
                    }
                }
            }

            return false;
        }

        return _it != this->_data.end();
    }

    ScopeValue* Scope::get(std::string p_name, Node* p_node, std::string p_o_name) {

        if (p_o_name.empty()) p_o_name = p_name;
        bool _value = item_exists(p_name);

        if (!_value) {
            if (p_node == nullptr)
                throw SNError(
                    Error::VARIABLE_ERROR,
                    Logger::format("Undefined variable: %s%s%s%s (no p_node has been passed to Scope::get)", BCYN, p_o_name.c_str(), RESET, BOLD)
                );

            DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
            throw CompilerError(Error::UNDEFINED_VARIABLE, Logger::format("Undefined variable: %s%s%s%s", BCYN, p_o_name.c_str(), RESET, BOLD), dbg_info);
        }

        unmangledResult unmangled = unmangle(p_name);

        std::map<std::string, std::unique_ptr<ScopeValue*>>::iterator _it = this->_data.find(unmangled.name);
        if (_it != this->_data.end() && unmangled.isMangled && (*_it->second)->type == ScopeType::FUNC_CONTAINER) {
            for (int i = 0; i < (*_it->second)->instances.size(); i++) {
                ScopeValue* scope_value = *(*_it->second)->instances[i];

                // TODO: (re-write) check for argv and default values
                if (unmangled.arguments == scope_value->arguments) {
                    if (unmangled.isPublic == scope_value->isPublic) {
                        return scope_value;
                    }
                }
            }
        }

        return *_data.find(p_name)->second;
    }


    void Scope::set(std::string p_name, std::unique_ptr<ScopeValue*> p_value) {
        (*p_value)->parent_scope = std::move(this);

        if ((*p_value)->type == ScopeType::FUNC) {
            unmangledResult result = unmangle(p_name);

            if (result.isMangled) {
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
