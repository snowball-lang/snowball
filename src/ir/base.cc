
#include "id.h"

#include <cstdint>

namespace snowball
{
namespace ir
{

id_t IdMixin::currentId = 0;
void
IdMixin::resetId() {
    currentId = 0;
}

} // namespace ir
} // namespace snowball
