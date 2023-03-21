
#include "../DBGSourceInfo.h"
#include "../ast/syntax/nodes.h"
#include "../common.h"
#include "../errors.h"
#include "../token.h"

#ifndef __SNOWBALL_PARSER_H_
#define __SNOWBALL_PARSER_H_

namespace snowball {
namespace parser {

/**
 * The parser performs syntactic analysis.
 *
 * Syntactic analysis is the process of analyzing a string of symbols,
 * conforming to the rules of a formal grammar.
 *
 * This parser will generate an AST for later use to generate
 * the llvm IR.
 */
class Parser {
    int m_tok_index = 0;
    Token m_current;
    std::vector<Token> m_tokens;

    ptr<SourceInfo> m_source_info;

  public:
    Parser(std::vector<Token> p_tokens, ptr<SourceInfo> p_source_info);
    ~Parser() = default;

  private:
    /// @brief Utility function to throw errors
    template <Error E, class... Args>
    [[nodiscard]] auto
    createError(std::pair<int, int> location, std::string message,
                const std::string info = "", Args&&...args) const {
        auto dbg_info =
            new DBGSourceInfo(m_source_info, {m_current.line, m_current.col},
                              std::forward<Args>(args)...);
        throw ParserError(E, message, dbg_info, info);
    }

    template <Error E>
    [[nodiscard]] auto createError(const std::string msg,
                                   std::string info = "") const {
        createError<E>(std::pair<int, int>(m_current.line, m_current.col), msg,
                       info, m_current.to_string().size());
    }

  public:
    /// @brief Parse from the lexer tree
    /// @return AST containing parsed node
    std::vector<Syntax::Node *> parse();

  private:
    // Utility functions for parsing

    /// Check if the current token is a certain token type
    template <TokenType Ty> bool is() { return m_current.type == Ty; }
    // Check if a token type is a certain type
    template <TokenType Ty> bool is(Token p_tok) { return p_tok.type == Ty; }
    // Comparison between 2 token types
    template <TokenType Ty> bool is(TokenType p_ty) { return p_ty == Ty; }

    // Check if a token mactches any of 2 types
    template <TokenType Ty, TokenType Ty2> bool is(Token p_tok) {
        return p_tok.type == Ty || p_tok.type == Ty2;
    }

    /**
     * Throws an error if the current token does not
     * match. If it does, just go to the next token.
     *
     * @param expectation string expectation
     * @return next token
     */
    template <TokenType Ty> Token consume(std::string expectation) {
        assert_tok<Ty>(expectation);
        return next();
    }

    /**
     * This function throws an error if
     * the current token does not match
     * with the given type
     *
     * @param expectation string expectation
     * @return given token
     */
    template <TokenType Ty> Token assert_tok(std::string expectation) {
        if (!is<Ty>()) {
            createError<SYNTAX_ERROR>(
                FMT("Expected %s but got %s", expectation.c_str(),
                    (is<TokenType::_EOF>(m_current) ? "an unexpected EOF"
                                                    : m_current.to_string())
                        .c_str()));
        }

        return m_current;
    }

    // Increment @var "m_tok_index" and
    // return the current token
    Token next(int p_offset = 0);
    // Increment @var "m_tok_index" (+ offset) and
    // return the respective token for that index.
    Token peek(int p_offset = 0, bool p_safe = false);
    // Decrement @var "m_tok_index" and
    // return the current token
    Token prev(int p_offset = 0);

    /**
     * This function gets a list of expressions (or nodes)
     * and joins them into a single one. It also orders them
     * so that snowball follows BIDMAS.
     *
     * e.g. NUMBER PLUS_OPERATOR NUMBER -> OPERATOR (l: NUMBER, r: NUMBER)
     */
    ptr<Syntax::Expression::Base>
    buildOperatorTree(std::vector<ptr<Syntax::Expression::Base>>& exprs);

  private:
    // Parsing functions
    using NodeVec = std::vector<ptr<Syntax::Node>>;

    /**
     * visibility    ::=  pub | priv
     * funcname      ::=  identifier
     *
     * funcdef       ::=  [decorators] [extern] [visibility] "fn" funcname
     *                    [generic_expr] "(" [parameter_list] ")" type "{" block
     * "}"
     *
     * arrowfn       ::=  [decorators] "fn" funcname "(" [parameter_list] ")"
     * type "=>" stmt
     */
    ptr<Syntax::Statement::FunctionDef>
    parseFunction(bool isConstructor = false);

    /**
     * params        ::=  "<" [param_args] ">"
     * param_args    ::=  identifier ["=" default_type]
     */
    std::vector<ptr<Syntax::Expression::Param>> parseGenericParams();

    /**
     * generics_expr ::=  "<" [type] ["," [type]...] ">"
     */
    std::vector<ptr<Syntax::Expression::TypeRef>> parseGenericExpr();

    /**
     * type          ::=  identifier [generics_expr]
     */
    ptr<Syntax::Expression::TypeRef> parseType();

    /**
     * variable      ::=  "let" ["mut"] identifier[: [type]] = [expr]
     *
     * @example
     *    let a = "hello"
     *    let b: i32 = 2.4
     */
    ptr<Syntax::Statement::VariableDecl> parseVariable();

    /**
     * block         ::=  "{" [body] "}"
     * body          ::=  [stmt] | [expr]
     */
    ptr<Syntax::Block> parseBlock(std::vector<TokenType> termination = {
                                      TokenType::BRACKET_RCURLY});

    /**
     * return stmt   ::=  "return" [stmt]
     */
    ptr<Syntax::Statement::Return> parseReturn();

    /**
     * visibility    ::=  pub | priv
     * class_name    ::=  identifier
     * class_inherit ::=  "extends" [type]
     *
     * operator_decl ::=  "operator" [op | "String" | "bool"] [function_like]
     * constructor   ::=  [class_name == actual class name] [function_like]
     * constructor   ::=  "~" [class_name == actual class name] [function_like]
     *
     * class_decls   ::=  [visibility]
     *                |   [function_declaration] ";"
     *                |   [variable_declaration] ";"
     *                |   [operator_decl] ";"
     *                |   [constructor] ";"
     *                |   [destructor] ";"
     * class_body    ::=  "{" [class_decls] "}"
     *
     * class         ::=  [visibility] "class" [class_name]
     *                    [class_inherit] [class_body]
     */
    ptr<Syntax::Statement::ClassDef> parseClass();

    /**
     * function_call ::= [expr] "(" [args] ")"
     * arguments     ::= [[expr] "," ...]
     *
     * @param callee expression being called
     */
    ptr<Syntax::Expression::FunctionCall>
    parseFunctionCall(ptr<Syntax::Expression::Base> callee);

    /**
     * function_call ::= [expr] "(" [args] ")"
     * arguments     ::= [[expr] "," ...]
     *
     * @param callee expression being called
     */
    ptr<Syntax::Statement::ImportStmt> parseImportStatement();

    /**
     * expr          ::=  [constant_value] |
     *                    [function_call]  |
     *                    [index_node]     |
     *                    [new_instance]
     * new_instance  ::=  "new" [type_ref][call]
     *
     * @param allowAssign Whether or not allow the assign operator.
     */
    ptr<Syntax::Expression::Base> parseExpr(bool allowAssign = true);
};

} // namespace parser
} // namespace snowball

#endif // __SNOWBALL_PARSER_H_
