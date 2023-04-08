
#include "DefiniteAssigment.h"

#include <optional>

namespace snowball {
namespace Syntax {

void DefiniteAssigment::withScope(std::function<void()> cb) {
    this->scopes.push_front({});

    cb();
    this->scopes.pop_front();
}

void DefiniteAssigment::withState(std::function<void()> cb) {
    auto currentState = this->state;
    this->state       = {.inited = {}};

    cb();
    this->state = currentState;
}

void DefiniteAssigment::asBlock(std::function<void()> cb) {
    withScope([&] { withState([&] { cb(); }); });
}

std::optional<
    std::pair<Statement::VariableDecl, DefiniteAssigment::ReferenceStatus>>
DefiniteAssigment::getIdentifier(std::string x) {
    for (auto s : scopes) {
        for (auto i : s) {
            if (i.first.getName() == x) {
                return i;
            }
        }
    }

    return std::nullopt;
}

} // namespace Syntax
} // namespace snowball
