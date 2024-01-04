
#include "Transformer.h"

#include "../ast/syntax/nodes.h"
#include "../ast/types/FunctionType.h"
#include "../ast/visitor/Visitor.h"
#include "../ir/module/Module.h"
#include "../ir/values/Argument.h"
#include "../ir/values/Call.h"
#include "../ir/values/EnumInit.h"
#include "../ir/values/Constants.h"
#include "../ir/values/Func.h"
#include "../ir/values/Return.h"
#include "../ir/values/Throw.h"
#include "../ir/values/ValueExtract.h"
#include "../utils/utils.h"
#include "TransformContext.h"

#include <assert.h>
#include <memory>
#include <string>
#include <vector>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

Transformer::Transformer(std::shared_ptr<ir::Module> mod, const SourceInfo* srci, std::filesystem::path packagePath, bool allowTests, bool allowBenchmarks)
    : AcceptorExtend<Transformer, Visitor>(srci) {
  auto builder = ir::IRBuilder(mod);
  ctx = new TransformContext(mod, builder, allowTests, allowBenchmarks);
  ctx->imports->setCurrentPackagePath(packagePath);
  initializeCoreRuntime();
}

std::shared_ptr<ir::Value> Transformer::trans(Node* node) {
  if (auto x = utils::cast<AttributeHolder>(node)) {
    if (x->hasAttribute(Attributes::CFG)) {
      auto args = x->getAttributeArgs(Attributes::CFG);
      for (auto [type, _] : args) {
        if (type == "tests") {
          if (!ctx->testMode) {
            return nullptr; // TODO: check if this causes problems
          }
        } else if (type == "bench") {
          if (!ctx->benchMode) {
            return nullptr; // TODO: check if this causes problems
          }
        } else if (type == "target_os") {
          auto os = _;
          bool isNot = utils::startsWith(os, "!"); 
          if (isNot)
            os = os.substr(1);
          if (os != _SNOWBALL_OS && !isNot) {
            return nullptr; // TODO: check if this causes problems
          }
        } else {
          E<SYNTAX_ERROR>(node, "Unknown attribute!", {.info = FMT("Unknown config attribute '%s'", type.c_str())});
        }
      }
    }
  }

  node->accept(this);
  return this->value;
}

std::vector<std::shared_ptr<ir::Module>> Transformer::getModules() const { return modules; }
void Transformer::addModule(std::shared_ptr<ir::Module> m) {
  ctx->cache->addModule(m->getUniqueName(), m);
  modules.push_back(m);
}
auto Transformer::getModule() const { return ctx->module; }
void Transformer::visitGlobal(std::vector<Node*> p_nodes) {
  ctx->withScope([&] {
    initializePerModuleMacros();

    bool backup = ctx->generateFunction;
    ctx->generateFunction = false;
    for (auto node : p_nodes) {
      SN_TRANSFORMER_CAN_GENERATE(node) { trans(node); }
    }

    ctx->generateFunction = true;
    for (auto node : p_nodes) 
      trans(node);
    ctx->generateFunction = backup;
  });
}

// mark: - noops

SN_TRANSFORMER_VISIT(Expression::TypeRef) { assert(false); }

ir::IRBuilder& Transformer::getBuilder() { return ctx->getBuilder(); }

} // namespace Syntax
} // namespace snowball