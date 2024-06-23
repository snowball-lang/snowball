
#include "compiler/utils/utils.h"
#include "compiler/frontend/ast/nodes.h"
#include "compiler/frontend/ast/types.h"

namespace snowball {
namespace frontend {
namespace ast {
namespace types {

unsigned int Type::reference_depth() {
  unsigned int depth = 0;
  Type* current = this;
  while (current->is_reference()) {
    depth++;
    current = current->as_reference()->get_ref();
  }
  return depth;
}

std::string IntType::get_printable_name() {
  if (bits == 1) {
    return "bool";
  }
  return fmt::format("{}{}", is_signed() ? "i" : "u", bits);
}

std::string IntType::get_mangled_name() {
  std::string name = is_signed() ? "i" : "u";
  name += std::to_string(bits);
  return fmt::format("{}{}", name.size(), name);
}

std::string FloatType::get_printable_name() {
  return fmt::format("f{}", bits);
}

std::string FloatType::get_mangled_name() {
  auto name = get_printable_name();
  return fmt::format("{}{}", name.size(), name);
}

std::string FuncType::get_printable_name() {
  std::string name = std::string(unsafe ? "unsafe " : "") + "fn(";
  auto param_types = get_param_types();
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

std::string FuncType::get_mangled_name() {
  std::string name = "fnTy";
  if (unsafe) {
    name += "U";
  }
  for (auto param : get_param_types()) {
    name += param->get_mangled_name();
  }
  name += "R";
  name += return_type->get_mangled_name();
  return fmt::format("{}{}", name.size(), name);
}

std::string GenericType::get_printable_name() {
  return name;
}

std::string GenericType::get_mangled_name() {
  return fmt::format("{}{}", name.size(), name);
}

std::string ErrorType::get_printable_name() {
  return "<error>";
}

std::string ErrorType::get_mangled_name() {
  sn_assert(false, "error type should not be mangled");
}

std::string UnknownType::get_printable_name()  {
  return "_";
}

std::string UnknownType::get_mangled_name() {
  sn_assert(false, "unknown type should not be mangled");
}

std::string VoidType::get_printable_name() {
  return "void";
}

std::string VoidType::get_mangled_name() {
  return "4void";
}

std::string ClassType::get_printable_name() {
  std::string generic_string = "";
  if (has_generics()) {
    generic_string = "<";
    const auto& generics = get_generics();
    for (size_t i = 0; i < generics.size(); i++) {
      generic_string += generics[i]->get_printable_name();
      if (i != generics.size() - 1) {
        generic_string += ", ";
      }
    }
    generic_string += ">";
  }
  return fmt::format("{}{}", path, generic_string);
}

bool ClassType::is_interface_decl() const { return decl->is_interface(); }
bool ClassType::is_class_decl() const { return decl->is_class(); }

std::string ClassType::get_mangled_name() {
  std::string name = "cTy";
  name += path.get_path_string();
  if (has_generics()) {
    name += "G";  
    for (const auto& generic : get_generics()) {
      name += generic->get_mangled_name();
    }
    name += "EG";
  }
  return fmt::format("{}{}", name.size(), name);
}

bool ClassType::is_deep_unknown() const {
  bool unknown = false;
  if (has_generics()) {
    for (const auto& generic : get_generics()) {
      if (generic->is_deep_unknown()) {
        unknown = true;
        break;
      }
    }
  }
  return unknown;
}

bool ClassType::is_deep_generic() const {
  bool is_generic = false;
  if (has_generics()) {
    for (const auto& generic : get_generics()) {
      if (generic->is_deep_generic()) {
        is_generic = true;
        break;
      }
    }
  }
  return is_generic;
}

Type* Type::get_reference_to() {
  return ReferenceType::create(this);
}

Type* Type::get_pointer_to(bool is_const) {
  return PointerType::create(this, is_const);
}

std::string ReferenceType::get_printable_name() {
  return fmt::format("&{}", ref->get_printable_name());
}

std::string ReferenceType::get_mangled_name() {
  return fmt::format("R{}", ref->get_mangled_name());
}

std::string PointerType::get_printable_name() {
  return fmt::format("*{}", pointee->get_printable_name());
}

std::string PointerType::get_mangled_name() {
  return fmt::format("P{}", pointee->get_mangled_name());
}

std::vector<Type*> FuncType::get_param_types() {
  if (param_types_cache.has_value()) {
    return param_types_cache.value();
  }
  recalibrate_cache();
  return get_param_types();
}

void FuncType::recalibrate_cache() {
  std::vector<Type*> types;
  auto args = linked->get_params();
  types.reserve(args.size());
  for (auto& arg : args) {
    types.push_back(arg->get_type());
  }
  param_types_cache = types;
}

std::string SelfType::get_printable_name() {
  return self->get_printable_name();
}

std::string SelfType::get_mangled_name() {
  sn_assert(false, "self type should be replaced by the time mangling occurs");
}

// Mark: Type equality

bool Type::equals(Type* other, bool ignore_self) {
  return equals_impl(other, ignore_self) && is_mutable == other->is_mutable;
}

bool UnknownType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_unknown = other->as_unknown()) {
    return id == other_unknown->id;
  }
  return false;
}

bool IntType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_int = other->as_int()) {
    return bits == other_int->bits && is_signed() == other_int->is_signed();
  }
  return false;
}

bool FloatType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_float = other->as_float()) {
    return bits == other_float->bits;
  }
  return false;
}

bool FuncType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_func = other->as_func()) {
    if (unsafe != other_func->unsafe) {
      return false;
    }
    auto other_params = other_func->get_param_types();
    auto params = get_param_types();
    if (params.size() != other_params.size()) {
      return false;
    }
    for (size_t i = ignore_self; i < params.size(); i++) {
      if (!params[i]->equals(other_params[i])) {
        return false;
      }
    }
    return return_type->equals(other_func->get_return_type());
  }
  return false;
}

bool GenericType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_generic = other->as_generic()) {
    return name == other_generic->name;
  }
  return false;
}

bool ClassType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_class = other->as_class()) {
    if (path != other_class->path) {
      return false;
    }
    if (has_generics() != other_class->has_generics()) {
      return false;
    }
    if (has_generics()) {
      auto generics = get_generics();
      auto other_generics = other_class->get_generics();
      if (generics.size() != other_generics.size()) {
        return false;
      }
      for (size_t i = 0; i < generics.size(); i++) {
        if (!generics[i]->equals(other_generics[i])) {
          return false;
        }
      }
    }
    return true;
  }
  return false;
}

bool ReferenceType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_ref = other->as_reference()) {
    return ref->equals(other_ref->get_ref());
  }
  return false;
}

bool PointerType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_ptr = other->as_pointer()) {
    return pointee->equals(other_ptr->get_pointee());
  }
  return false;
}

bool SelfType::equals_impl(Type* other, bool ignore_self) {
  if (auto other_self = other->as_self_type()) {
    return self->equals(other_self->get_self());
  }
  return false;
}

bool GenericType::is_copyable() const {
  for (const auto& constraint : constraints) {
    if (auto as_class = constraint->as_class()) {
      if (as_class->get_decl()->get_builtin_name() == "copy") {
        return true;
      }
    }
  }
  return false;
}

}
}
}
}
