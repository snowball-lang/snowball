
#include "../ast/types/PrimitiveTypes.h"
#include "../common.h"
#include "../token.h"
#include "./Parser.h"

#include <assert.h>

#define CHECK_PRIVACY(var)                                                     \
    var = true;                                                                \
    if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(                 \
            peek(-4, true))) {                                                 \
        isPublic = is<TokenType::KWORD_PUBLIC>(peek(-4, true));                \
    }

using namespace snowball::Syntax::Statement;

namespace snowball::parser {

ptr<FunctionDef> Parser::parseFunction(bool isConstructor) {
    assert(is<TokenType::KWORD_FUNC>() ||
           (is<TokenType::IDENTIFIER>() && isConstructor));

    if (!isConstructor) next();

    bool isExtern  = false;
    bool isPublic  = false;
    bool isStatic  = false;
    bool isVirtual = false;

    std::string name;
    std::string externName;

    // Check if the tokens behind the function keyword
    // have some meaning to this statement. For example,
    // you can have:
    //     pub fn ...
    //     ^^^
    // to indicate that the function is public.
    auto pk = peek(-3, true);
    if (is<TokenType::KWORD_EXTERN>(pk)) {
        CHECK_PRIVACY(isExtern)
    } else if (is<TokenType::KWORD_STATIC>(pk)) {
        CHECK_PRIVACY(isStatic)
    } else if (is<TokenType::KWORD_VIRTUAL>(pk)) {
        CHECK_PRIVACY(isVirtual)
    } else if (is<TokenType::KWORD_PUBLIC, TokenType::KWORD_PRIVATE>(pk)) {
        isPublic = pk.type == TokenType::KWORD_PUBLIC;
    }

    auto dbg   = m_current.get_pos();
    auto width = 0;

    // Get the function name
    if (is<TokenType::IDENTIFIER>()) {
        name  = m_current.to_string();
        width = name.size();

        externName = name;
    } else if (is<TokenType::VALUE_STRING>() && isExtern) {
        // External functions can have the capacity of having 2 separate names.
        // This can be useful for things such as accessing external functions
        // that contians special characters.
        //
        // example:
        //     extern fn "hello.world$woah" as my_fn() ...
        //
        // =========================================

        // We get a substring from the first and last
        // characters. This is because string literals
        // contains '"' inside them.
        auto s     = m_current.to_string();
        externName = s.substr(1, s.size() - 2);

        next();
        consume<TokenType::KWORD_AS>("'as' keyword");

        dbg  = m_current.get_pos();
        name = assert_tok<TokenType::IDENTIFIER>("an identifier").to_string();

        width = name.size();
    } else {
        std::string e =
            isExtern ? "Expected an identifier or a string constant but got "
                       "'%s' while parsing an extern function declaration"
                     : "Expected an identifier but got '%s' while parsing a "
                       "function declaration";

        createError<SYNTAX_ERROR>(e, m_current.to_string().c_str());
    }

    next();

    // Create a new instance of a node
    auto privacy = Syntax::Statement::Privacy::fromInt(isPublic);

    // Check for generic expressions
    std::vector<ptr<Syntax::Expression::Param>> generics;
    if (is<TokenType::OP_LT>()) {

        if (isExtern) {
            createError<SYNTAX_ERROR>(
                "Can't define an external function with generics");
        }

        generics = parseGenericParams();
        width    = (m_current.get_pos().second - dbg.second);
    }

    assert_tok<TokenType::BRACKET_LPARENT>("'('");

    int argumentCount = 0;
    bool isVarArg     = false;

    std::vector<ptr<Syntax::Expression::Param>> arguments;
    while (true) {
        auto pk = peek();

        if (is<TokenType::BRACKET_RPARENT>(pk)) {
            break;
        }

        next();
        if (isExtern && is<TokenType::IDENTIFIER>() &&
            (!is<TokenType::SYM_COLCOL>())) {
            assert_tok<TokenType::IDENTIFIER>("a type reference");
            auto type = parseType();

            auto arg = new Syntax::Expression::Param(
                FMT("$extern-arg-%i", argumentCount), type);
            arguments.push_back(arg);
        } else if (is<TokenType::SYM_DOT>() && is<TokenType::SYM_DOT>(peek()) &&
                   is<TokenType::SYM_DOT>(peek(1, true))) {
            next(2);
            isVarArg = true;
        } else {
            auto name = m_current.to_string();
            consume<TokenType::IDENTIFIER>("an identifier").to_string();

            consume<TokenType::SYM_COLLON>("':'");

            assert_tok<TokenType::IDENTIFIER>("an identifier");
            auto type = parseType();

            auto arg = new Syntax::Expression::Param(name, type);
            if (is<TokenType::OP_EQ>()) {
                auto expr = parseExpr();
                arg->setDefaultValue(expr);
                next();
            }

            arguments.push_back(arg);
        }

        argumentCount++;
        if (is<TokenType::SYM_COMMA>()) {
            if (isVarArg)
                createError<SYNTAX_ERROR>(
                    "Variadic arguments should be the last argument!");
            if (!isExtern) prev();
        } else if (is<TokenType::BRACKET_RPARENT>()) {
            prev();
        } else {
            createError<SYNTAX_ERROR>(
                "Expected a ',' or a ')' but found '%s' instead",
                m_current.to_string().c_str());
        }
    }

    next();
    consume<TokenType::BRACKET_RPARENT>("')'");

    ptr<Syntax::Expression::TypeRef> returnType = nullptr;
    if (is<TokenType::IDENTIFIER>()) {
        if (isConstructor) {
            createError<SYNTAX_ERROR>(
                "Contructor can't have return types.",
                "Constructors return type default to the parent's class type!");
        }

        returnType = parseType();
    } else {
        auto info  = new DBGSourceInfo(m_source_info, m_current.get_pos(),
                                       m_current.get_width());
        returnType = new Syntax::Expression::TypeRef(SN_VOID_TYPE, info);
    }

    auto info = new DBGSourceInfo(m_source_info, dbg, width);

    ptr<Syntax::Block> block;
    bool hasBlock = false;

    if (isExtern) {
        // TODO: external functions can have bodies!
        assert_tok<TokenType::SYM_SEMI_COLLON>("';'");
    } else {
        assert_tok<TokenType::BRACKET_LCURLY>("'{'");
        block    = parseBlock();
        hasBlock = true;

        assert_tok<TokenType::BRACKET_RCURLY>("'}'");
    }

    ptr<FunctionDef> fn = nullptr;
    if (isExtern) {
        fn = Syntax::N<ExternFnDef>(externName, name);
    } else if (hasBlock) {
        fn = Syntax::N<BodiedFunction>(block, name);
    } else {
        fn = Syntax::N<FunctionDef>(name);
    }

    fn->setVirtual(isVirtual);
    fn->setVariadic(isVarArg);
    fn->setPrivacy(privacy);
    fn->setArgs(arguments);
    fn->setDBGInfo(info);
    fn->setRetType(returnType);
    fn->setGenerics(generics);
    fn->setStatic(isStatic);

    return fn;
}

} // namespace snowball::parser
