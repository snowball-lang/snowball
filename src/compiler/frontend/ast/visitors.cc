
#include "compiler/utils/logger.h"
#include "compiler/frontend/ast/visitors.h"

#include "compiler/globals.h"

namespace snowball {
namespace frontend {
namespace ast {

using namespace utils;

AstVisitor::AstVisitor(const Ctx& ctx)
  : vctx(ctx) {
}

void AstVisitor::debug(const std::string& msg) const {
  if (global.debug_verbose) {
    Logger::debug(msg);
  }
}

} // namespace ast
} // namespace frontend
} // namespace snowball
