
#include "snowball/nodes.h"
#include "snowball/errors.h"
#include "snowball/scopes.h"

#include <optional>

namespace snowball {
    Scope::Scope(std::string p_scope_name, SourceInfo* p_source_info)
        : _source_info(p_source_info), _scope_name(p_scope_name) {}

    std::experimental::optional<ScopeValue> Scope::get_optional(std::string p_name) {
        std::map<std::string, ScopeValue>::iterator _it = _data.find(p_name);

        if (_it == _data.end()) {
            return std::experimental::optional<ScopeValue>();
        }

        return std::experimental::optional<ScopeValue>((ScopeValue)_it->second);
    }

    ScopeValue Scope::get(std::string p_name, Node p_node) {

        std::experimental::optional<ScopeValue> _value = get_optional(p_name);

        if (!_value) {
            DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node.pos, p_node.width);
            throw CompilerError(Error::UNDEFINED_VARIABLE, Logger::format("Undefined variable: %s%s%s%s", BCYN, p_node.name.c_str(), RESET, BOLD), dbg_info);
        }

        return *_value;
    }


    void Scope::set(std::string p_name, ScopeValue p_value) {
        _data[p_name] = p_value;
    }

}
