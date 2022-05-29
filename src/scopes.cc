
#include "snowball/scopes.h"

#include <optional>

namespace snowball {
    Scope::Scope(std::string p_scope_name, ScopeValue p_scope_value) {
        _data[p_scope_name] = p_scope_value;
    }

    std::experimental::optional<ScopeValue> Scope::get_optional(std::string p_name) {
        std::map<std::string, ScopeValue>::iterator _it = _data.find(p_name);

        if (_it == _data.end()) {
            return std::experimental::optional<ScopeValue>();
        }

        return std::experimental::optional<ScopeValue>((ScopeValue)_it->second);
    }

    ScopeValue Scope::get(std::string p_name) {

        std::experimental::optional<ScopeValue> _value = get_optional(p_name);

        if (!_value) {
            // TODO: throw error
        }

        return *_value;
    }


    void Scope::set(std::string p_name, ScopeValue p_value) {
        _data[p_name] = p_value;
    }

}
