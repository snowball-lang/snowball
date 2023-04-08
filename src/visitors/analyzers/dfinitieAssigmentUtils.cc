
#include "DefiniteAssigment.h"

namespace snowball {
namespace Syntax {

void DefiniteAssigment::withScope(std::function<void ()> cb) {

}

void DefiniteAssigment::withState(std::function<void ()> cb) {

}

void DefiniteAssigment::asBlock(std::function<void ()> cb) {
    withScope([&] {
        withState([&] {
            cb();
        });
    });
}

}
}
