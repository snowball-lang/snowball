
#include "Interface.h"

#include "../../common.h"
#include "../../constants.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "../syntax/common.h"
#include "Type.h"

#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace snowball {
namespace types {

bool InterfaceType::is(InterfaceType* other) const {
  auto otherArgs = other->getGenerics();
  bool genericSizeEqual = otherArgs.size() == generics.size();
  bool argumentsEqual = genericSizeEqual ? std::all_of(otherArgs.begin(),
                                                   otherArgs.end(),
                                                   [&, idx = 0](Type* i) mutable {
                                                     idx++;
                                                     return generics.at(idx - 1)->is(i);
                                                   })
                                         : false;
    DUMP_S(other->getUUID().c_str())
    DUMP_S(uuid.c_str())
  return (other->getUUID() == uuid) && argumentsEqual;
}

std::string InterfaceType::getPrettyName() const {
  auto base = module->isMain() ? "" : module->getName() + "::";
  auto n = base + getName();

  std::string genericString; // Start args tag
  if (generics.size() > 0) {
    genericString = "<";

    for (auto g : generics) {
      genericString += g->getPrettyName();
      if (g != generics.back()) genericString += ", ";
    }

    genericString += ">";
  }

  std::string mut = isMutable() ? "mut " : "";
  auto res = mut + n + genericString;
  if (getName() == _SNOWBALL_CONST_PTR) {
    res = "(*const " + generics.at(0)->getName() + ")";
  } else if (getName() == _SNOWBALL_MUT_PTR) {
    res = "(*mut " + generics.at(0)->getName() + ")";
  } 

  return res;
}

std::string InterfaceType::getMangledName() const {
  auto base = module->getUniqueName();
  auto _tyID = static_cast<ir::id_t>(getId());
  std::stringstream sstm;
  sstm << (utils::startsWith(base, _SN_MANGLE_PREFIX) ? base : _SN_MANGLE_PREFIX) << "&" << name.size() << name << "I"
       << _tyID;
  auto prefix = sstm.str(); // disambiguator

  std::string mangledArgs; // Start args tag
  if (generics.size() > 0) {
    mangledArgs = "IGSt";

    int argCounter = 1;
    for (auto g : generics) {
      mangledArgs += "A" + std::to_string(argCounter) + g->getMangledName();
      argCounter++;
    }
  }

  std::string mangled = prefix + mangledArgs + "IE"; // ClsE = end of class
  return mangled;
}

}; // namespace types
}; // namespace snowball
