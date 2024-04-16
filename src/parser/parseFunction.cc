
#include "../ast/types/PrimitiveTypes.h"
#include "../common.h"
#include "../lexer/tokens/token.h"
#include "Parser.h"

#include <assert.h>

#define CHECK_PRIVACY(var) \
  var = true; \
  if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(peek(peekCount - 1, true))) { \
    isPublic = is<TokenType::KWORD_PUBLIC>(peek(peekCount - 1, true)); \
  }

using namespace snowball::Syntax;
using namespace snowball::Syntax::Statement;

namespace snowball::parser {

FunctionDef* Parser::parseFunction(bool isConstructor, bool isOperator, bool isLambda, bool allowDecl) {
  assert((is<TokenType::KWORD_FUNC>() && (!isConstructor && !isOperator)) ||
         (is<TokenType::IDENTIFIER>() && (isConstructor && !isOperator)) || (isOperator));
  auto comment = parseDocstring(m_current.getComment());
  if (!isConstructor && (!isLambda)) next();
  bool isExtern = false;
  bool isPublic = false;
  bool isStatic = false;
  bool isVirtual = false;
  bool isMutable = false;
  bool isGeneric = false;
  bool isUnsafe = false;
  bool isOverride = false;
  bool isNotImplemented = false;
  std::string name;
  std::string externName;
  // Constructor specific only
  std::vector<Syntax::Expression::Base*> superArgs;
  bool hasSuperArgs = false;
  std::map<Expression::Identifier*, Expression::Base*> constructorInitArgs;
  bool isLLVMFunction = false;
  // Check if the tokens behind the function keyword
  // have some meaning to this statement. For example,
  // you can have:
  // pub fn ...
  // ^^^
  // to indicate that the function is public.
  int peekCount = -3;
fetch_attrs:
  auto pk = peek(peekCount, true);
  if (is<TokenType::KWORD_UNSAFE>(pk)) {
    isUnsafe = true;
    peekCount--;
    goto fetch_attrs;
  } else if (is<TokenType::KWORD_EXTERN>(pk)) {
    CHECK_PRIVACY(isExtern)
  } else if (is<TokenType::KWORD_STATIC>(pk)) {
    CHECK_PRIVACY(isStatic)
  } else if (is<TokenType::KWORD_VIRTUAL>(pk)) {
    isVirtual = true;
    peekCount--;
    goto fetch_attrs;
  } else if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(pk)) {
    isPublic = pk.type == TokenType::KWORD_PUBLIC;
  } else if (is<TokenType::KWORD_MUTABLE>(pk)) {
    isMutable = true;
    peekCount--;
    goto fetch_attrs;
  } else if (is<TokenType::KWORD_OVERRIDE>(pk)) {
    isOverride = true;
    peekCount--;
    goto fetch_attrs;
  }
  if (isOperator) {
    consume<TokenType::KWORD_FUNC>("'func' keyword");
  }
  if (isOverride && isStatic) {
    createError<SYNTAX_ERROR>("Static functions can't be overriden!");
  }
  auto dbg = m_current.get_pos();
  auto width = 0;
  auto attributes = verifyAttributes([&](std::string attr) {
                                       if (attr == "llvm_function") {
                                         isLLVMFunction = true;
                                         return Attributes::LLVM_FUNC;
  } else if (attr == "internal_linkage") {
    return Attributes::INTERNAL_LINKAGE;
  } else if (attr == "external_linkage") {
    return Attributes::EXTERNAL_LINKAGE;
  } else if (attr == "inline") {
    return Attributes::INLINE;
  } else if (attr == "no_inline") {
    return Attributes::NO_INLINE;
  } else if (attr == "test") {
    return Attributes::TEST;
  } else if (attr == "no_mangle") {
    return Attributes::NO_MANGLE;
  } else if (attr == "export") {
    return Attributes::EXPORT;
  } else if (attr == "explicit") {
    return Attributes::EXPLICIT;
  } else if (attr == "bench") {
    return Attributes::BENCH;
  } else if (attr == "__internal__") {
    return Attributes::BUILTIN;
  } else if (attr == "__no_pointer_self__") {
    return Attributes::NO_POINTER_SELF;
  } else if (attr == "unsafe_fn_not_body") {
    return Attributes::UNSAFE_FUNC_NOT_BODY;
  } else if (attr == "intrinsic") {
    return Attributes::INTRINSIC;
  }
return Attributes::INVALID;
                                   });
  if (isOverride) {
    attributes[Attributes::OVERRIDE] = {};
  }
  if (isOperator) {
    services::OperatorService::OperatorType opType = services::OperatorService::OperatorType::INVALID;
    switch (m_current.type) {
      case TokenType::OP_EQ: {
        opType = services::OperatorService::OperatorType::EQ;
        break;
      }
      case TokenType::OP_EQEQ: {
        opType = services::OperatorService::OperatorType::EQEQ;
        break;
      }
      case TokenType::OP_PLUS: {
        opType = services::OperatorService::OperatorType::PLUS;
        break;
      }
      case TokenType::OP_PLUSEQ: {
        opType = services::OperatorService::OperatorType::PLUSEQ;
        break;
      }
      case TokenType::OP_MINUS: {
        opType = services::OperatorService::OperatorType::MINUS;
        break;
      }
      case TokenType::OP_MINUSEQ: {
        opType = services::OperatorService::OperatorType::MINUSEQ;
        break;
      }
      case TokenType::OP_MUL: {
        opType = services::OperatorService::OperatorType::MUL;
        break;
      }
      case TokenType::OP_MULEQ: {
        opType = services::OperatorService::OperatorType::MULEQ;
        break;
      }
      case TokenType::OP_DIV: {
        opType = services::OperatorService::OperatorType::DIV;
        break;
      }
      case TokenType::OP_DIVEQ: {
        opType = services::OperatorService::OperatorType::DIVEQ;
        break;
      }
      case TokenType::OP_MOD: {
        opType = services::OperatorService::OperatorType::MOD;
        break;
      }
      case TokenType::OP_MOD_EQ: {
        opType = services::OperatorService::OperatorType::MOD_EQ;
        break;
      }
      case TokenType::OP_LT: {
        opType = services::OperatorService::OperatorType::LT;
        break;
      }
      case TokenType::OP_LTEQ: {
        opType = services::OperatorService::OperatorType::LTEQ;
        break;
      }
      case TokenType::OP_GT: {
        opType = services::OperatorService::OperatorType::GT;
        break;
      }
      case TokenType::OP_GTEQ: {
        opType = services::OperatorService::OperatorType::GTEQ;
        break;
      }
      case TokenType::OP_AND: {
        opType = services::OperatorService::OperatorType::AND;
        break;
      }
      case TokenType::OP_OR: {
        opType = services::OperatorService::OperatorType::OR;
        break;
      }
      case TokenType::OP_NOT: {
        opType = services::OperatorService::OperatorType::NOT;
        break;
      }
      case TokenType::OP_NOTEQ: {
        opType = services::OperatorService::OperatorType::NOTEQ;
        break;
      }
      case TokenType::OP_BIT_NOT: {
        opType = services::OperatorService::OperatorType::BIT_NOT;
        break;
      }
      case TokenType::OP_BIT_LSHIFT: {
        opType = services::OperatorService::OperatorType::BIT_LSHIFT;
        break;
      }
      case TokenType::OP_BIT_LSHIFT_EQ: {
        opType = services::OperatorService::OperatorType::BIT_LSHIFT_EQ;
        break;
      }
      case TokenType::OP_BIT_RSHIFT: {
        opType = services::OperatorService::OperatorType::BIT_RSHIFT;
        break;
      }
      case TokenType::OP_BIT_RSHIFT_EQ: {
        opType = services::OperatorService::OperatorType::BIT_RSHIFT_EQ;
        break;
      }
      case TokenType::OP_BIT_OR: {
        opType = services::OperatorService::OperatorType::BIT_OR;
        break;
      }
      case TokenType::OP_BIT_OR_EQ: {
        opType = services::OperatorService::OperatorType::BIT_OR_EQ;
        break;
      }
      case TokenType::OP_BIT_AND: {
        opType = services::OperatorService::OperatorType::BIT_AND;
        break;
      }
      case TokenType::OP_BIT_AND_EQ: {
        opType = services::OperatorService::OperatorType::BIT_AND_EQ;
        break;
      }
      case TokenType::OP_BIT_XOR: {
        opType = services::OperatorService::OperatorType::BIT_XOR;
        break;
      }
      case TokenType::OP_BIT_XOR_EQ: {
        opType = services::OperatorService::OperatorType::BIT_XOR_EQ;
        break;
      }
      case TokenType::BRACKET_LSQUARED: {
        if (is<TokenType::BRACKET_RSQUARED>(peek())) {
          opType = services::OperatorService::OperatorType::INDEX;
          next();
          break;
        }
        goto snowballInvalidDefaultOperatorCase;
      }
      case TokenType::IDENTIFIER: {
        if (m_current.to_string() == "bool") {
          opType = services::OperatorService::OperatorType::BOOL;
          break;
        }
        goto snowballInvalidDefaultOperatorCase;
      }
      case TokenType::BRACKET_LPARENT: {
        if (is<TokenType::BRACKET_RPARENT>(peek())) {
          opType = services::OperatorService::OperatorType::CALL;
          break;
        }
        goto snowballInvalidDefaultOperatorCase;
      }
snowballInvalidDefaultOperatorCase:
      default: {
        createError<SYNTAX_ERROR>(
          FMT("Expected a valid operator type but instead got '%s'", m_current.to_string().c_str())
        );
      }
    }
    name = services::OperatorService::getOperatorMangle(opType);
    externName = name;
  } else if (isLambda) {
  } else {
    // Get the function name
    if (is<TokenType::IDENTIFIER>()) {
      name = m_current.to_string();
      width = name.size();
      externName = name;
    } else if (is<TokenType::VALUE_STRING>() && isExtern) {
      // External functions can have the capacity of having 2 separate
      // names. This can be useful for things such as accessing
      // external functions that contians special characters.
      //
      // example:
      // extern fn "hello.world$woah" as my_fn() ...
      //
      // =========================================
      //
      // We get a substring from the first and last
      // characters. This is because string literals
      // contains '"' inside them.
      auto s = m_current.to_string();
      externName = s.substr(1, s.size() - 2);
      next();
      consume<TokenType::KWORD_AS>("'as' keyword");
      dbg = m_current.get_pos();
      name = assert_tok<TokenType::IDENTIFIER>("an identifier").to_string();
      width = name.size();
    } else {
      std::string e = isExtern ? "Expected an identifier or a string constant but got "
                      "'%s' while parsing an extern function declaration" :
                      "Expected an identifier but got '%s' while parsing a "
                      "function declaration";
      createError<SYNTAX_ERROR>(FMT(e.c_str(), m_current.to_string().c_str()));
    }
  }
  next();
  // Create a new instance of a node
  auto privacy = Syntax::Statement::Privacy::fromInt(isPublic);
  // Check for generic expressions
  std::vector<Syntax::Expression::Param*> generics;
  if (is<TokenType::OP_LT>()) {
    isGeneric = true;
    if (isLambda) { createError<SYNTAX_ERROR>("Cant define a lambda with generics"); }
    generics = parseGenericParams();
    width = (m_current.get_pos().second - dbg.second);
  }
  assert_tok<TokenType::BRACKET_LPARENT>("'('");
  int argumentCount = 0;
  bool isVarArg = false;
  std::vector<Syntax::Expression::Param*> arguments;
  while (true) {
    auto pk = peek();
    if (is<TokenType::BRACKET_RPARENT>(pk)) { break; }
    next();
    if (isExtern && isTypeValid() && (!is<TokenType::SYM_COLLON>(peek()))) {
      throwIfNotType();
      auto type = parseType();
      auto arg = new Syntax::Expression::Param(FMT("$extern-arg-%i", argumentCount), type);
      if (is<TokenType::OP_EQ>()) {
        auto expr = parseExpr(false);
        arg->setDefaultValue(expr);
        next();
      }
      arguments.push_back(arg);
    } else if (is<TokenType::SYM_DOT>() && is<TokenType::SYM_DOT>(peek()) && is<TokenType::SYM_DOT>(peek(1, true))) {
      next(2);
      isVarArg = true;
    } else {
      bool isMutable = false;
      if (is<TokenType::KWORD_MUTABLE>()) {
        isMutable = true;
        next();
      }
      auto name = m_current.to_string();
      consume<TokenType::IDENTIFIER>("an identifier");
      consume<TokenType::SYM_COLLON>("':'");
      auto type = parseType();
      if (name == "self" && argumentCount == 0 && (!isStatic) && (!isConstructor) && (m_current_class != nullptr)) {
        attributes[Attributes::FIRST_ARG_IS_SELF] = {};
      } else if (name == "self") {
        createError<SYNTAX_ERROR>("'self' can only be used as the first argument inside a class non-static function!");
      }
      auto arg = new Syntax::Expression::Param(name, type);
      arg->setMutable(isMutable);
      if (is<TokenType::OP_EQ>()) {
        auto expr = parseExpr(false);
        arg->setDefaultValue(expr);
        next();
      }
      arguments.push_back(arg);
    }
    argumentCount++;
    if (is<TokenType::SYM_COMMA>()) {
      if (isVarArg) createError<SYNTAX_ERROR>("Variadic arguments should be the last argument!");
      // if (!isExtern) prev();
    } else if (is<TokenType::BRACKET_RPARENT>()) {
      prev();
    } else {
      createError<SYNTAX_ERROR>(FMT("Expected a ',' or a ')' but found '%s' instead", m_current.to_string().c_str()));
    }
  }
  next();
  consume<TokenType::BRACKET_RPARENT>("')'");
  Syntax::Expression::TypeRef* returnType = nullptr;
  if (isTypeValid()) {
    if (isConstructor) {
      createError<SYNTAX_ERROR>(
      "Contructor can't have return types.", {
        .info = "Constructors return type default to the parent's "
        "class type!"
      }
      );
    }
    returnType = parseType();
  } else {
    auto info = new DBGSourceInfo(m_source_info, m_current.get_pos(), m_current.get_width());
    returnType = new Syntax::Expression::TypeRef(SN_VOID_TYPE, info);
  }
  if (isConstructor) { // We assume m_current_class is not nullptr
    if (is<TokenType::SYM_COLLON>()) {
      next();
      if (is<TokenType::KWORD_SUPER>()) {
        hasSuperArgs = true;
        if (!m_current_class->getParent()) {
          createError<SYNTAX_ERROR>("Cant call super on a class that doesnt extend "
                                    "from another class!");
        }
        next();
        assert_tok<TokenType::BRACKET_LPARENT>("'('");
        while (true) {
          auto pk = peek();
          if (is<TokenType::BRACKET_RPARENT>(pk)) { break; }
          auto expr = parseExpr(false);
          superArgs.push_back(expr);
          next();
          if (is<TokenType::SYM_COMMA>()) {
          } else if (is<TokenType::BRACKET_RPARENT>()) {
            prev();
            break;
          } else {
            createError<SYNTAX_ERROR>(
              FMT("Expected a ',' or a ')' but found '%s' instead", m_current.to_string().c_str())
            );
          }
        }
        next();
        consume<TokenType::BRACKET_RPARENT>("')'");
        if (is<TokenType::SYM_COMMA>()) {
          next();
          assert_tok<TokenType::IDENTIFIER>("an identifier");
        }
      }
      while (is<TokenType::IDENTIFIER>()) {
        auto name = parseIdentifier(false, false);
        if (constructorInitArgs.find(name) != constructorInitArgs.end()) {
          createError<SYNTAX_ERROR>(FMT("Duplicate constructor init argument '%s'", name->getIdentifier().c_str()));
        }
        next();
        assert_tok<TokenType::BRACKET_LPARENT>("'('");
        auto expr = parseExpr(false);
        constructorInitArgs[name] = expr;
        next();
        consume<TokenType::BRACKET_RPARENT>("')'");
        if (is<TokenType::SYM_COMMA>()) {
          next();
          assert_tok<TokenType::IDENTIFIER>("an identifier");
        } else if (is<TokenType::BRACKET_LCURLY>()) {
          break;
        } else {
          createError<SYNTAX_ERROR>(FMT("Expected a ',' or a '{' but found '%s' instead", m_current.to_string().c_str())
                                   );
        }
      }
    }
    if (m_current_class->getParent() && !hasSuperArgs) {
      createError<SYNTAX_ERROR>("Expected a 'super' call for constructors inside a class "
                                "that extends form a type!");
    }
  }
  auto info = new DBGSourceInfo(m_source_info, dbg, width);
  Syntax::Block* block = nullptr;
  std::string llvmCode;
  std::vector<Syntax::Expression::TypeRef*> llvmTypesUsed;
  bool hasBlock = false;
  if (isExtern) {
    // TODO: external functions can have bodies!
    assert_tok<TokenType::SYM_SEMI_COLLON>("';'");
  } else if (is<TokenType::OP_EQ>()) {
    next();
    if (is<TokenType::VALUE_NUMBER>()) {
      auto number = m_current.to_string();
      if (number != "0") {
        createError<SYNTAX_ERROR>(
        "Expected a '0' for the function body!", {
          .info = "Expected a '0' for the function body!",
          .note = "The function body must be a '0' for now.",
          .help = "You have to set the function body to '0'.\n"
          "For example:\n"
          "1 |  virt fn my_fn() = 0\n"
          "2 |"
        }
        );
      }
      if (!isVirtual) {
        createError<SYNTAX_ERROR>(
        "Function body can only be '0' for virtual functions!", {
          .info = "Function body can only be '0' for virtual functions!",
          .note = "The function body must be a '0' for now.",
          .help = "You have to set the function body to '0'.\n"
          "For example:\n"
          "1 |  virt fn my_fn() = 0\n"
          "2 |"
        }
        );
      }
      isNotImplemented = true;
      hasBlock = true;
      block = new Syntax::Block();
      next();
    } else {
      createError<SYNTAX_ERROR>("Expected a number literal for the function body!");
    }
  } else if (is<TokenType::SYM_SEMI_COLLON>()) {
    if (isConstructor) { createError<SYNTAX_ERROR>("Constructors cant be declared as extern!"); }
  } else {
    assert_tok<TokenType::BRACKET_LCURLY>("'{'");
    if (isLLVMFunction) {
      auto startPos = m_current.get_pos();
      auto depth = 1;
      while (depth != 0) {
        next();
        if (is<TokenType::BRACKET_LCURLY>()) {
          depth++;
          if (is<TokenType::OP_EQ>(peek())) {
            next(1);
            llvmTypesUsed.push_back(parseType());
            depth--;
            // TODO: make sure they are in the same line
            assert_tok<TokenType::BRACKET_RCURLY>("'}'");
          }
        } else if (is<TokenType::BRACKET_RCURLY>()) {
          depth--;
        } else if (is<TokenType::_EOF>()) {
          createError<SYNTAX_ERROR>("Unterminated LLVM function block code!");
        }
      }
      auto endPos = m_current.get_pos();
      llvmCode = utils::getSubstringByRange(m_source_info->getSource(), startPos, endPos);
      llvmCode = llvmCode.substr(1, llvmCode.size() - 1); // Ignore speech marks
    } else {
      block = parseBlock();
    }
    hasBlock = true;
    assert_tok<TokenType::BRACKET_RCURLY>("'}'");
  }
  if (!hasBlock && isLLVMFunction) { createError<SYNTAX_ERROR>("LLVM defined functions must have a body!"); }
  if (isOperator && ((arguments.size() == 0) || ((arguments.size() == 1)
                     && attributes.count(Attributes::FIRST_ARG_IS_SELF)))) {
    // Transform to unary operators for +, - (TODO: some more)
    auto op = services::OperatorService::operatorID(name);
    OperatorService::OperatorType newType;
    bool valid = true;
    switch (op) {
      case services::OperatorService::OperatorType::MINUS: {
        newType = OperatorService::OperatorType::UMINUS;
        break;
      }
      case services::OperatorService::OperatorType::PLUS: {
        newType = OperatorService::OperatorType::UPLUS;
        break;
      }
      default: valid = false;
    }
    if (valid) { name = OperatorService::getOperatorMangle(newType); }
  }
  FunctionDef* fn = nullptr;
  if (isConstructor) {
    assert(hasBlock);
    isMutable = true;
    auto constructor = Syntax::N<ConstructorDef>(hasSuperArgs, block, name);
    constructor->setSuperArgs(superArgs);
    constructor->setInitArgs(constructorInitArgs);
    fn = utils::cast<FunctionDef>(constructor);
  } else if (isExtern) {
    fn = Syntax::N<ExternFnDef>(externName, name);
  } else if (isLLVMFunction) {
    fn = Syntax::N<LLVMFunction>(llvmCode, llvmTypesUsed, name);
  } else if (hasBlock) {
    fn = Syntax::N<BodiedFunction>(block, name);
  } else {
    fn = Syntax::N<FunctionDef>(name);
  }
  for (auto[n, a] : attributes) { fn->addAttribute(n, a); }
  if (isUnsafe) fn->addAttribute(Attributes::UNSAFE);
  fn->setVirtual(isVirtual);
  fn->setVariadic(isVarArg);
  fn->setPrivacy(privacy);
  fn->setArgs(arguments);
  fn->setDBGInfo(info);
  fn->setRetType(returnType);
  if (isGeneric) fn->setGenerics(generics);
  if (isNotImplemented) fn->addAttribute(Attributes::NOT_IMPLEMENTED);
  fn->setStatic(isStatic);
  fn->isMutable(isMutable);
  fn->setComment(comment);
  return fn;
}

} // namespace snowball::parser
