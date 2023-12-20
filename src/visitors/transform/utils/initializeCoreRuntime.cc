#include "../../../ast/syntax/nodes.h"
#include "../../Transformer.h"

#include "../../../lexer/lexer.h"
#include "../../../parser/Parser.h"
#include "../../../utils/utils.h"
#include "../../../visitors/Analyzer.h"
#include "../../../visitors/Transformer.h"
#include "../../../visitors/TypeChecker.h"
#include "../../../visitors/analyzers/DefinitveAssigment.h"
#include <fstream>

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

void Transformer::initializeCoreRuntime() {
  auto dbg = new DBGSourceInfo(ctx->module->getSourceInfo(), 0);
  auto import = Syntax::N<Syntax::Statement::ImportStmt>(std::vector<std::string>{"std"}, "std");
  import->setDBGInfo(dbg);
  ctx->uuidStack.push_back(ctx->imports->CORE_UUID + "std");
  trans(import);
}

} // namespace Syntax
} // namespace snowball