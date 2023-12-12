
#ifndef GET_VAR_IMPL

// note(argument): "x + 1" because ir::Argument (x - 1) gets
// created after ir::Variable (x). note(note argument): They are
// declared as usual with normal ID incrementation
#define GET_VAR_IMPL(variable, value) \
  auto x = ctx->getCurrentIRFunction();\
  if (x && variable->isUsedInLambda()) {\
    llvm::Value* arg = nullptr;\
    LLVMBuilderContext::ClosureContext closure;\
    if (x->getId() != variable->getParentFunc()->getId()) {\
      closure = ctx->closures.at(x->getParentScope()->getId());\
      int argumentIndex = 0;\
      if (utils::is<types::BaseType>(x->getRetTy()))\
        argumentIndex++;\
      arg = ctx->getCurrentFunction()->getArg(argumentIndex);\
    } else {\
      closure = ctx->closures.at(x->getId());\
      arg = builder->CreateLoad(builder->getPtrTy(), closure.closure);        \
    }\
    auto index = std::distance(\
      closure.variables.begin(),\
      std::find_if(\
        closure.variables.begin(),\
        closure.variables.end(),\
        [variable](auto v2) { return v2 == variable->getId(); }\
      )\
    );\
    value = builder->CreateStructGEP(closure.closureType, builder->CreateStructGEP(getLambdaContextType(), arg, 1), index);\
  } else {\
    auto id = variable->getId() + variable->isArgument();\
    value = ctx->getSymbol(id);\
  }

#endif // GET_VAR_IMPL
