
#include "compiler/frontend/ast/types.h"
#include "compiler/utils/utils.h"

namespace snowball {
namespace frontend {
namespace ast {
namespace types {

std::string IntType::get_printable_name() const {
  if (bits == 1) {
    return "bool";
  }
  return fmt::format("{}{}", is_signed() ? "i" : "u", bits);
}

std::string IntType::get_mangled_name() const {
  std::string name = is_signed() ? "i" : "u";
  name += std::to_string(bits);
  return fmt::format("{}{}", name.size(), name);
}

std::string FloatType::get_printable_name() const {
  return fmt::format("f{}", bits);
}

std::string FloatType::get_mangled_name() const {
  auto name = get_printable_name();
  return fmt::format("{}{}", name.size(), name);
}

std::string FuncType::get_printable_name() const {
  std::string name = "fn(";
  for (size_t i = 0; i < param_types.size(); i++) {
    name += param_types[i]->get_printable_name();
    if (i != param_types.size() - 1) {
      name += ", ";
    }
  }
  name += ") -> ";
  name += return_type->get_printable_name();
  return name;
}

std::string FuncType::get_mangled_name() const {
  std::string name = "fnTy";
  for (auto& param : param_types) {
    name += param->get_mangled_name();
  }
  name += "R";
  name += return_type->get_mangled_name();
  return fmt::format("{}{}", name.size(), name);
}

std::string GenericType::get_printable_name() const {
  return name;
}

std::string GenericType::get_mangled_name() const {
  return fmt::format("{}{}", name.size(), name);
}

std::string ErrorType::get_printable_name() const {
  return "<error>";
}

std::string ErrorType::get_mangled_name() const {
  sn_assert(false, "error type should not be mangled");
}

std::string UnknownType::get_printable_name() const  {
  return "_";
}

std::string UnknownType::get_mangled_name() const {
  sn_assert(false, "unknown type should not be mangled");
}

std::string VoidType::get_printable_name() const {
  return "void";
}

std::string VoidType::get_mangled_name() const {
  return "4void";
}

}
}
}
}
