#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::initializePerModuleMacros() {
  auto pkgMacro = N<Macro>(
          "pkg",
          std::vector<std::tuple<std::string, Macro::ArguementType, Node*>>{
                  {"e", Macro::ArguementType::EXPRESSION, nullptr}},
          nullptr
  );
  auto pkgInstance = new transform::MacroInstance(pkgMacro, ctx->module);
  auto pkgMacroItem = std::make_shared<transform::Item>(pkgInstance);
  ctx->addItem("pkg", pkgMacroItem);

  auto zeroInitMacro = N<Macro>(
          "zero_initialized",
          std::vector<std::tuple<std::string, Macro::ArguementType, Node*>>{
                  {"type", Macro::ArguementType::TYPE, nullptr}},
          nullptr
  );
  auto zeroInitInstance = new transform::MacroInstance(zeroInitMacro, ctx->module);
  auto zeroInitMacroItem = std::make_shared<transform::Item>(zeroInitInstance);
  ctx->addItem("zero_initialized", zeroInitMacroItem);

  auto sizeofMacro = N<Macro>(
          "sizeof",
          std::vector<std::tuple<std::string, Macro::ArguementType, Node*>>{
                  {"type", Macro::ArguementType::TYPE, nullptr}},
          nullptr
  );
  auto sizeofInstance = new transform::MacroInstance(sizeofMacro, ctx->module);
  auto sizeofMacroItem = std::make_shared<transform::Item>(sizeofInstance);
  ctx->addItem("sizeof", sizeofMacroItem);

  auto alignOfMacro = N<Macro>(
          "alignof",
          std::vector<std::tuple<std::string, Macro::ArguementType, Node*>>{
                  {"type", Macro::ArguementType::TYPE, nullptr}},
          nullptr
  );
  auto alignOfInstance = new transform::MacroInstance(alignOfMacro, ctx->module);
  auto alignOfMacroItem = std::make_shared<transform::Item>(alignOfInstance);
  ctx->addItem("alignof", alignOfMacroItem);

  auto includeStringMacro = N<Macro>(
          "include_str",
          std::vector<std::tuple<std::string, Macro::ArguementType, Node*>>{
                  {"path", Macro::ArguementType::CONSTANT_STRING, nullptr}},
          nullptr
  );
  auto includeStringInstance = new transform::MacroInstance(includeStringMacro, ctx->module);
  auto includeStringMacroItem = std::make_shared<transform::Item>(includeStringInstance);
  ctx->addItem("include_str", includeStringMacroItem);

  auto envMacro = N<Macro>(
          "env",
          std::vector<std::tuple<std::string, Macro::ArguementType, Node*>>{
                  {"name", Macro::ArguementType::CONSTANT_STRING, nullptr}},
          nullptr
  );
  auto envInstance = new transform::MacroInstance(envMacro, ctx->module);
  auto envMacroItem = std::make_shared<transform::Item>(envInstance);
  ctx->addItem("env", envMacroItem);
}

} // namespace Syntax
} // namespace snowball