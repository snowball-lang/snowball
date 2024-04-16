#include "../../Transformer.h"
#include <cstring>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::executeGenericTests(Expression::WhereClause* clause, types::Type* _generic, const std::string& name) {
  auto generic = _generic;
  if (clause == nullptr) { return; }
  for (auto test : clause->getChecks()) {
    auto type = transformType(test);
    if (auto interface = utils::cast<types::InterfaceType>(type)) {
      bool found = false;
      bool isFunctionType = utils::is<types::FunctionType>(generic);
      if ((utils::is<types::PointerType>(generic) ||
           utils::is<types::ReferenceType>(generic) ||
           isFunctionType) && interface->is(ctx->getBuiltinTypeImpl("Sized"))) {
        found = true;
      } else if (isFunctionType && interface->is(ctx->getBuiltinTypeImpl("Callable"))) {
        found = true;
      } else {
        if (auto x = utils::cast<types::ReferenceType>(generic)) {
          generic = x->getPointedType();
        }
        for (auto impl : generic->getImpls()) {
          if (impl->is(interface)) {
            found = true;
            break;
          }
        }
      }
      if (!found) {
        if ((utils::is<types::IntType>(generic) || utils::is<types::FloatType>(generic))
            && (interface->getUUID() == (ctx->imports->CORE_UUID + "std.ToString:0"))) { // note: Make sure to always match the UUID
          found = true;
        } else if (utils::is<types::EnumType>(generic) && interface->is(ctx->getBuiltinTypeImpl("EnumType"))) {
          found = true;
        }
      }
      if (!found) {
        auto impls = generic->getImpls();
        E<TYPE_ERROR>(
          test,
          FMT("Type '%s' does not implement '%s'",
              _generic->getPrettyName().c_str(),
        interface->getPrettyName().c_str()), {
          .info = "Failed to execute where clause",
          .note = impls.empty() ? "" : FMT("Type '%s' implements the following interfaces:\n  %s", _generic->getPrettyName().c_str(), utils::join<std::vector<types::InterfaceType*>::iterator>(impls.begin(), impls.end(), ",\n  ", [](auto x) { return (*x)->getPrettyName(); }).c_str()),
          .help = FMT(
            "Implement '%s' for '%s'", interface->getPrettyName().c_str(), _generic->getPrettyName().c_str()
          ),
          .tail = ctx->latestCall ? EI<>(ctx->latestCall->getDBGInfo(),
                                         "",
          {
            .info = FMT("Error caused by this call"),
            .note =
            FMT("This call is the reason why the given generic '%s' "
                "does\nnot implement '%s'",
                name.c_str(),
                interface->getPrettyName().c_str())
          }) :
            nullptr
          }
          );
      }
    } else {
      E<TYPE_ERROR>(test, FMT("Type '%s' is not an interface", type->getPrettyName().c_str()));
    }
  }
}

} // namespace Syntax
} // namespace snowball