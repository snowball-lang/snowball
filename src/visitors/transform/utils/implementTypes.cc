
#include "../../Transformer.h"

namespace snowball {
namespace Syntax {

void Transformer::implementTypes(
types::DefinedType* ty, std::vector<Expression::TypeRef*> types, std::vector<Statement::FunctionDef*>& functions
) {
  std::vector<types::InterfaceType*> interfaces;
  for (auto type : types) {
    auto ty = transformType(type);
    if (auto interface = utils::cast<types::InterfaceType>(ty)) {
      interfaces.emplace_back(interface);
    } else {
      E<TYPE_ERROR>(
      type,
      FMT("Type '%s' is not an interface!", type->getPrettyName().c_str()), {
        .info = "Not an interface!",
        .note = "Only interfaces can be implemented!",
        .help = "Maybe you meant to use 'extends' instead of 'implements'?"
      }
      );
    }
  }
  auto typeFields = ty->getFields();
  for (auto interface : interfaces) {
    for (auto field : interface->getFields()) {
      if (field->kind == types::InterfaceType::Member::Kind::FIELD) {
        auto ast = utils::cast<Statement::VariableDecl>(field->ast);
        assert(ast);
        auto name = ast->getName();
        auto type = field->type;
        auto classField = std::find_if(typeFields.begin(), typeFields.end(), [&](auto f) { return f->name == name; });
        if (classField == typeFields.end()) {
          if (ast->getValue() == nullptr) {
            E<TYPE_ERROR>(
            ty,
            FMT("Field '%s' is not implemented!", name.c_str()), {
              .info = "Lacks of implementation!",
              .note = "All fields of an interface must be implemented!",
              .help = "Maybe you meant to use 'extends' instead of 'implements'?",
              .tail = EI<>(
              ast,
              "",
              {
                .info = "Field declared here!",
                .note =
                FMT("Field '%s' declared here without a default\nimplementation values!",
                    name.c_str()),
              }
              )
            }
            );
          }
          ty->addField(
          new types::DefinedType::ClassField(name, type, ast->getPrivacy(), ast->getValue(), ast->isMutable())
          );
        } else {
          if (!(*classField)->type->is(type)) {
            E<TYPE_ERROR>(
            ast,
            FMT("Field %s type does not match the interface type!", name.c_str()), {
              .info = "Type mismatch!",
              .note = FMT("Field '%s' declared here with a different type!", name.c_str()),
              .help =
              FMT("Here its declared as '%s' but the interface declares it as '%s'!",
                  (*classField)->type->getPrettyName().c_str(),
                  type->getPrettyName().c_str()),
              .tail =
              EI<>(ast,
                   "",
              {
                .info = "Field declared here!",
                .note = FMT("Field '%s' declared here with a different type!", name.c_str()),
              })
            }
            );
          } else if ((*classField)->isMutable != ast->isMutable()) {
            E<TYPE_ERROR>(
            ast,
            FMT("Field %s mutability does not match the interface mutability!", name.c_str()), {
              .info = "Mutability mismatch!",
              .note = FMT("Field '%s' declared here with a different mutability!", name.c_str()),
              .help =
              FMT("Here its declared as '%s' but the interface declares it as '%s'!",
                  (*classField)->isMutable ? "mutable" : "immutable",
                  ast->isMutable() ? "mutable" : "immutable"),
              .tail = EI<>(
              ast,
              "",
              {
                .info = "Field declared here!",
                .note = FMT("Field '%s' declared here with a different mutability!", name.c_str()),
              }
              )
            }
            );
          } else if ((*classField)->getPrivacy() != ast->getPrivacy()) {
            E<TYPE_ERROR>(
            ast,
            FMT("Field (%s) privacy does not match the interface privacy!", name.c_str()), {
              .info = "Privacy mismatch!",
              .note = FMT("Field '%s' declared here with a different privacy!", name.c_str()),
              .help =
              FMT("Here its declared as '%s' but the interface declares it as '%s'!",
                  (*classField)->getPrivacy() == Statement::Privacy::PUBLIC ? "public" : "private",
                  ast->getPrivacy() == Statement::Privacy::PUBLIC ? "public" : "private"),
              .tail = EI<>(
              ast,
              "",
              {
                .info = "Field declared here!",
                .note = FMT("Field '%s' declared here with a different privacy!", name.c_str()),
              }
              )
            }
            );
          }
        }
      }
    }
    ty->addImpl(interface);
  }
}

} // namespace Syntax
} // namespace snowball
