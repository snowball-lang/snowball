
#include "scopes.h"
#include "enviroment.h"

namespace snowball {
    Enviroment::Enviroment() {
        _scopes.push_back(Scope(ScopeType::));
    }
}
