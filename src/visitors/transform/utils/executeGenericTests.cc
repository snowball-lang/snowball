#include "../../Transformer.h"
#include <cstring>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::executeGenericTests(Expression::WhereClause* clause, types::Type* generic, const std::string& name) {
  if (clause == nullptr) { return; }
  for (auto test : clause->getChecks()) {
    auto implementations = generic->getImpls();
    auto type = transformType(test);

    if (auto interface = utils::cast<types::InterfaceType>(type)) {
      bool found = false;
      for (auto impl : implementations) {
        if (impl->is(interface)) {
          found = true;
          break;
        }
      }
      if (!found) {
        E<TYPE_ERROR>(test, FMT("Type '%s' does not implement '%s'", generic->getPrettyName().c_str(), interface->getPrettyName().c_str()), {
          .info = "Failed to execute where clause",
          .help = FMT("Implement '%s' for '%s'", interface->getPrettyName().c_str(), generic->getPrettyName().c_str()),
          .tail = ctx->latestCall ? EI<>(
            ctx->latestCall->getDBGInfo(), "",
            {
              .info = FMT("Error caused by this call"),
              .note = FMT("This call is the reason why the given generic '%s' does\nnot implement '%s'", name.c_str(), interface->getPrettyName().c_str())
            }
          ) : nullptr
        });
      }
    } else {
      E<TYPE_ERROR>(test, FMT("Type '%s' is not an interface", type->getPrettyName().c_str()));
    }
  }
}

} // namespace Syntax
} // namespace snowball