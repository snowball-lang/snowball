
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
      arg = builder->CreateLoad(closure.closureType->getPointerTo(), builder->CreateStructGEP(getLambdaContextType(), ctx->getCurrentFunction()->getArg(argumentIndex), 1));\
    } else {\
      closure = ctx->closures.at(x->getId());\
      arg = closure.closure; \
    }\
    auto index = std::distance(\
                               closure.variables.begin(),\
                               std::find_if(\
                                            closure.variables.begin(),\
                                            closure.variables.end(),\
                                            [variable](auto v2) { return v2 == variable->getId(); }\
                                           )\
                              );\
    assert(index != (int)closure.variables.size());\
    value = builder->CreateStructGEP(closure.closureType, arg, index);\
  } else {\
    auto id = variable->getId();\
    value = ctx->getSymbol(id);\
  }

#endif // GET_VAR_IMPL
