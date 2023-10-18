
#include "DefinedType.h"

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

DefinedType::DefinedType(
        const std::string& name,
        const std::string uuid,
        std::shared_ptr<ir::Module> module,
        Syntax::Statement::DefinedTypeDef* ast,
        std::vector<ClassField*> fields,
        DefinedType* parent,
        std::vector<Type*> generics,
        bool isStruct
)
    : AcceptorExtend(Kind::CLASS, name), parent(parent), ast(ast), fields(fields), _struct(isStruct) {
  setGenerics(generics);
  setPrivacy(PRIVATE);
  unsafeSetUUID(uuid);
  unsafeSetModule(module);
}
DefinedType::ClassField::ClassField(
        const std::string& name, Type* type, Privacy privacy, Syntax::Expression::Base* initializedValue, bool isMutable
)
    : name(name)
    , type(type)
    , Syntax::Statement::Privacy(privacy)
    , initializedValue(initializedValue)
    , isMutable(isMutable) { }
Syntax::Statement::DefinedTypeDef* DefinedType::getAST() const { return ast; }
void DefinedType::addField(ClassField* f) { fields.emplace_back(f); }
bool DefinedType::is(DefinedType* other) const {
  auto otherArgs = other->getGenerics();
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
  return (other->getUUID() == uuid) && argumentsEqual;
}

std::string DefinedType::getPrettyName() const {
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

std::string DefinedType::getMangledName() const {
  auto base = module->getUniqueName();
  auto _tyID = static_cast<ir::id_t>(getId());
  std::stringstream sstm;
  sstm << (utils::startsWith(base, _SN_MANGLE_PREFIX) ? base : _SN_MANGLE_PREFIX) << "&" << name.size() << name << "Cv"
       << _tyID;
  auto prefix = sstm.str(); // disambiguator

  std::string mangledArgs; // Start args tag
  if (generics.size() > 0) {
    mangledArgs = "ClsGSt";

    int argCounter = 1;
    for (auto g : generics) {
      mangledArgs += "A" + std::to_string(argCounter) + g->getMangledName();
      argCounter++;
    }
  }

  std::string mangled = prefix + mangledArgs + "ClsE"; // ClsE = end of class
  return mangled;
}

Syntax::Expression::TypeRef* DefinedType::toRef() {
  auto tRef = Syntax::TR(getUUID(), nullptr, this, getUUID());
  std::vector<Syntax::Expression::TypeRef*> genericRef;
  for (auto g : generics) { genericRef.push_back(g->toRef()); }

  tRef->setGenerics(genericRef);
  return tRef;
}

bool DefinedType::canCast(Type* ty) const {
  SNOWBALL_MUTABLE_CAST_CHECK

  if (auto x = utils::cast<DefinedType>(ty)) return canCast(x);
  return false;
}

bool DefinedType::canCast(DefinedType* ty) const {
  // TODO: test this:
  return hasParent() && (ty->is(getParent()));
}

// - https://en.wikipedia.org/wiki/Data_structure_alignment#Computing_padding
std::int64_t DefinedType::sizeOf() const {
  auto address = (std::int64_t) 0;
  for (const auto& f : fields) {
    auto typeSize = f->type->sizeOf();
    auto typeAlignment = f->type->alignmentOf();
    address += (address - (address % typeAlignment)) % typeAlignment;
    address += (typeAlignment - (address % typeAlignment)) % typeAlignment;
    address += typeSize;
  }
  auto alignment = alignmentOf();
  address += (address - (address % alignment)) % alignment;
  address += (alignment - (address % alignment)) % alignment;
  return address;
}

std::int64_t DefinedType::alignmentOf() const {
  auto maximumAlignment = (std::int64_t) 0;
  for (const auto& f : fields) {
    auto alignment = f->type->alignmentOf();
    if (alignment > maximumAlignment) maximumAlignment = alignment;
  }
  return maximumAlignment;
}

}; // namespace types
}; // namespace snowball
