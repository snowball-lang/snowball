

#include "FunctionType.h"

#include "../../ast/syntax/nodes.h"
#include "../../common.h"
#include "../../constants.h"
#include "../../ir/values/Argument.h"
#include "../../ir/values/Func.h"
#include "../../utils/utils.h"
#include "Type.h"

#include <memory>
#include <string>
#include <vector>

namespace snowball {
namespace types {

std::string FunctionType::getPrettyName() const {
  auto stringArgs = Syntax::Expression::FunctionCall::getArgumentsAsString(args);
  auto stringRet = retTy->getPrettyName();

  if (variadic) {
    if (stringArgs.size() > 0) stringArgs += ", ";
    stringArgs += "...";
  }

  return FMT("function (%s) mut -> %s", stringArgs.c_str(), stringRet.c_str());
}

bool FunctionType::is(FunctionType* other) const {
  auto otherArgs = other->getArgs();
  if (args.size() != otherArgs.size()) return false;
  bool argumentsEqual = args.size() == 0 ? true : std::all_of(otherArgs.begin(), otherArgs.end(), [&, idx = 0](Type* i) mutable {
    idx++;
    return args.at(idx-1)->is(i);
  });

  auto returnEquals = retTy->is(other->getRetType());
  return returnEquals && argumentsEqual && (variadic == other->isVariadic());
}

std::string FunctionType::getMangledName() const {
  std::string result = "_FntY."; // Function type indicator
  result += retTy->getMangledName();
  result += "fAr"; // start of arguments list indicator

  for (auto a : args) result += a->getMangledName();

  if (variadic) result += "VaGv";

  result += "fAe"; // end of arguments indicator
  return result;
}

FunctionType* FunctionType::from(ir::Func* fn, Syntax::Statement::FunctionDef* node) {
  auto args = utils::map<std::string, std::shared_ptr<ir::Argument>, Type*>(
          fn->getArgs(), [&](auto map) -> auto{ return map.second->getType(); });
  bool isMutable = node ? node->isMutable() : false;
  if (fn->hasParent() && (!fn->isStatic()) &&
      services::OperatorService::opEquals<services::OperatorService::CONSTRUCTOR>(fn->getName())) {
    args.insert(args.begin(), fn->getParent());
  }

  auto ret = fn->getRetTy();
  return new FunctionType(args, ret, fn->isVariadic(), isMutable);
}

}; // namespace types
}; // namespace snowball
