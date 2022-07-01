
#include "snowball/nodes.h"
#include "snowball/errors.h"
#include "snowball/scopes.h"

#include <optional>

namespace snowball {
    Scope::Scope(std::string p_scope_name, SourceInfo* p_source_info)
        : _source_info(p_source_info), _scope_name(p_scope_name) {}

    bool Scope::item_exists(std::string p_name) {
        std::map<std::string, ScopeValue*>::iterator _it = this->_data.find(p_name);

        return !(this->_data.find(p_name) == this->_data.end());
    }

    ScopeValue* Scope::get(std::string p_name, Node* p_node) {

        bool _value = item_exists(p_name);

        if (!_value) {
            DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
            throw CompilerError(Error::UNDEFINED_VARIABLE, Logger::format("Undefined variable: %s%s%s%s", BCYN, p_name.c_str(), RESET, BOLD), dbg_info);
        }

        return this->_data[p_name];
    }


    void Scope::set(std::string p_name, ScopeValue* p_value) {
        this->_data.insert ( std::pair<std::string,ScopeValue*>(p_name, p_value) );
    }

}
