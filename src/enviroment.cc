
#include "snowball/scopes.h"
#include "snowball/enviroment.h"

namespace snowball {
    Enviroment::Enviroment() {
        _scopes.push_back(Scope());
    }

    Scope Enviroment::global_scope() {
        return _scopes.at(0);
    }
}
