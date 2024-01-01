
#include "EnumType.h"

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

EnumType::EnumType(
    const std::string& name,
    const std::string uuid,
    std::shared_ptr<ir::Module> module,
    std::vector<EnumField*> fields,
    std::vector<Type*> generics,
    Privacy::Status privacy
) : AcceptorExtend(Kind::ENUM, name), fields(fields) {
  setGenerics(generics);
  setPrivacy(privacy);
  unsafeSetUUID(uuid);
  unsafeSetModule(module);
}
EnumType::EnumField::EnumField(
      const std::string& name,
      std::vector<types::Type*> types,
      Privacy privacy)
    : name(name), types(types), Syntax::Statement::Privacy(privacy) { }
bool EnumType::is(EnumType* ty) const {
  auto otherArgs = ty->getGenerics();
  bool genericSizeEqual = otherArgs.size() == generics.size();
  bool argumentsEqual = genericSizeEqual ? std::all_of(
                                                   otherArgs.begin(),
                                                   otherArgs.end(),
                                                   [&, idx = 0](Type* i) mutable {
                                                     idx++;
                                                     return generics.at(idx - 1)->is(i);
                                                   }
                                           ) :
                                           false;
  return (ty->getUUID() == uuid) && argumentsEqual;
}

std::string EnumType::getPrettyName() const {
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
  return n + genericString;
}

std::string EnumType::getMangledName() const {
  auto base = module->getUniqueName();
  auto _tyID = static_cast<ir::id_t>(getId());
  std::stringstream sstm;
  sstm << (utils::startsWith(base, _SN_MANGLE_PREFIX) ? base : _SN_MANGLE_PREFIX) << "&" << name.size() << name << "Ev"
       << _tyID;
  auto prefix = sstm.str(); // disambiguator

  std::string mangledArgs; // Start args tag
  if (generics.size() > 0) {
    mangledArgs = "EnuGSt";

    int argCounter = 1;
    for (auto g : generics) {
      mangledArgs += "A" + std::to_string(argCounter) + g->getMangledName();
      argCounter++;
    }
  }

  std::string mangled = prefix + mangledArgs + "EnuE"; // Enu = end enum
  return mangled;
}

Syntax::Expression::TypeRef* EnumType::toRef() {
  auto tRef = Syntax::TR(getUUID(), nullptr, this, getUUID());
  std::vector<Syntax::Expression::TypeRef*> genericRef;
  for (auto g : generics) { genericRef.push_back(g->toRef()); }

  tRef->setGenerics(genericRef);
  return tRef;
}

bool EnumType::canCast(Type* ty) const {
  if (auto x = utils::cast<EnumType>(ty)) return canCast(x);
  return false;
}

bool EnumType::canCast(EnumType* ty) const {
  SNOWBALL_MUTABLE_CAST_CHECK

  // TODO: maybe do something here?
  return false;
}

// - https://en.wikipedia.org/wiki/Data_structure_alignment#Computing_padding
std::int64_t EnumType::sizeOf() const {
  auto address = (std::int64_t) 0;
  for (const auto& f : fields) {
    auto typeSize = 0;
    for (const auto& t : f->types) {
      typeSize += t->sizeOf();
    }
    auto typeAlignment = 0;
    for (const auto& t : f->types) {
      auto alignment = t->alignmentOf();
      if (alignment > typeAlignment) typeAlignment = alignment;
    }
    address += (address - (address % typeAlignment)) % typeAlignment;
    address += (typeAlignment - (address % typeAlignment)) % typeAlignment;
    address += typeSize;
  }
  auto alignment = alignmentOf();
  address += (address - (address % alignment)) % alignment;
  address += (alignment - (address % alignment)) % alignment;
  address += (hasVtable * 8);
  if (address == 0) address = 1; // prevent 0-sized types
  return address;
}

std::int64_t EnumType::alignmentOf() const {
  auto maximumAlignment = (std::int64_t) 0;
  for (const auto& f : fields) {
    auto alignment = 0;
    for (const auto& t : f->types) {
      auto a = t->alignmentOf();
      if (a > alignment) alignment = a;
    }
    if (alignment > maximumAlignment) maximumAlignment = alignment;
  }
  if (maximumAlignment == 0) maximumAlignment = 1; // prevent 0-sized types
  return maximumAlignment;
}

}; // namespace types
}; // namespace snowball
