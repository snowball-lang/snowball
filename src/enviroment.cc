
#include "snowball/scopes.h"
#include "snowball/enviroment.h"

namespace snowball {
    Enviroment::Enviroment(SourceInfo* p_source_info) : _source_info(p_source_info) {
        _scopes.push_back(Scope("__sn__global__", _source_info));
    }

    Scope Enviroment::global_scope() {
        return _scopes.at(0);
    }

    Scope Enviroment::current_scope() {
        return _scopes.at(-1);
    }

    Scope Enviroment::create_scope(std::string p_name) {
        _scopes.push_back(Scope(p_name, _source_info));
        return current_scope();
    }

    void Enviroment::delete_scope() {

    }
}
