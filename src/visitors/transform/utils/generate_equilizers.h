
// Set the default '=' operator for the class
#define GENERATE_EQUALIZERS                                                                                            \
  if (ty->getName() != _SNOWBALL_CONST_PTR && ty->getName() != _SNOWBALL_MUT_PTR &&                                    \
      ty->getName() != _SNOWBALL_INT_IMPL && ty->getName() != _SNOWBALL_FUNC_IMPL) {                                                                           \
    for (int allowPointer = 0; allowPointer < 2; ++allowPointer) {                                                     \
      auto fn = Syntax::N<Statement::FunctionDef>(                                                                     \
              OperatorService::getOperatorMangle(OperatorType::EQ), Statement::Privacy::Status::PUBLIC                 \
      );                                                                                                               \
      fn->addAttribute(Attributes::BUILTIN);                                                                           \
      fn->setArgs({new Expression::Param(                                                                              \
              "other", allowPointer ? transformedType->getReferenceTo()->toRef() : transformedType->toRef()            \
      )});                                                                                                             \
      fn->setRetType(ctx->getVoidType()->toRef());                                                                     \
      trans(fn);                                                                                                       \
    }                                                                                                                  \
  }
