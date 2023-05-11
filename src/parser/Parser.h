
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

    SourceInfo *m_source_info;

  public:
    Parser(std::vector<Token> p_tokens, SourceInfo *p_source_info);
    ~Parser() noexcept = default;

  private:
    /// @brief Utility function to throw errors
    template <Error E, class... Args>
    [[nodiscard]] auto
    createError(std::pair<int, int> location, std::string message,
                const std::string info = "", Args&&...args) const {
        auto dbg_info = new DBGSourceInfo(m_source_info, location,
                                          std::forward<Args>(args)...);
        throw ParserError(E, message, dbg_info, info);
    }

    template <Error E>
    [[nodiscard]] auto createError(const std::string msg,
                                   std::string info = "") const {
        auto pos = std::pair<int, int>(m_current.line, m_current.col);
        createError<E>(pos, msg, info, m_current.to_string().size());
    }

  public:
    /// @brief Parse from the lexer tree
    /// @return AST containing parsed node
    std::vector<Syntax::Node *> parse();
    using NodeVec = std::vector<Syntax::Node *>;

  private:
    // Utility functions for parsing

    /// Check if the current token is a certain token type
    template <TokenType Ty> bool is() const { return m_current.type == Ty; }
    // Check if a token type is a certain type
    template <TokenType Ty> bool is(Token p_tok) const {
        return p_tok.type == Ty;
    }
    // Comparison between 2 token types
    template <TokenType Ty> bool is(TokenType p_ty) const { return p_ty == Ty; }

    // Check if a token mactches any of 2 types
    template <TokenType Ty, TokenType Ty2> bool is(Token p_tok) const {
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
     * @brief It checks if the current token is viable
     *  for parsing a type.
     */
    bool isTypeValid() const {
        return is<TokenType::IDENTIFIER>() || is<TokenType::KWORD_DECLTYPE>();
    }

    /**
     * @brief Throws an error if the current token does
     *  not match the @fn isTypeValid standard
     */
    void throwIfNotType() const {
        if (!isTypeValid()) {
            createError<SYNTAX_ERROR>(
                FMT("Expected a valid type declaration but found '%s' instead",
                    m_current.to_string().c_str()),
                "Types cant start like this");
        }
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
     * Joins a list of expressions into a single expression tree that
     * follows the order of operations defined by BIDMAS (Brackets,
     * Indices, Division, Multiplication, Addition, Subtraction).
     *
     * @param exprs A vector of pointers to Syntax::Expression::Base
     *              objects to be joined and ordered.
     * @return A pointer to a new Syntax::Expression::Base object
     *         representing the expression tree.
     *
     * @example
     *  - Input:  {NUMBER, PLUS_OPERATOR, NUMBER}
     *  - Output: OperatorExpr(l: NUMBER, r: NUMBER, op: PLUS_OPERATOR)
     */
    Syntax::Expression::Base *
    buildOperatorTree(std::vector<Syntax::Expression::Base *>& exprs);

  private:
    // Parsing functions
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
    Syntax::Statement::FunctionDef *parseFunction(bool isConstructor = false,
                                                  bool isOperator    = false,
                                                  bool isLambda      = false);

    /**
     * params        ::=  "<" [param_args] ">"
     * param_args    ::=  identifier ["=" default_type]
     */
    std::vector<Syntax::Expression::Param *> parseGenericParams();

    /**
     * generics_expr ::=  "<" [type] ["," [type]...] ">"
     */
    std::vector<Syntax::Expression::TypeRef *> parseGenericExpr();

    /**
     * type          ::=  identifier [generics_expr]
     */
    Syntax::Expression::TypeRef *parseType();

    /**
     * variable      ::=  "let" ["mut"] identifier[: [type]] = [expr]
     *
     * @example
     *    let a = "hello"
     *    let b: i32 = 2.4
     */
    Syntax::Statement::VariableDecl *parseVariable();

    /**
     * block         ::=  "{" [body] "}"
     * body          ::=  [stmt] | [expr]
     */
    Syntax::Block *parseBlock(std::vector<TokenType> termination = {
                                  TokenType::BRACKET_RCURLY});

    /**
     * return stmt   ::=  "return" [stmt]
     */
    Syntax::Statement::Return *parseReturn();

    /**
     * while stmt   ::=  "while" [stmt] [block]
     */
    Syntax::Statement::WhileLoop *parseWhile();

    /**
     * conditional   ::=  "if" [expr] [block]
     *                |   "if" [expr]: [expr]
     */
    Syntax::Statement::Conditional *parseConditional();

    /**
     * visibility    ::=  pub | priv
     * class_name    ::=  identifier
     * class_inherit ::=  "extends" [type]
     *
     * operator_decl ::=  "operator" [op | "String" | "bool"] [function_like]
     * constructor   ::=  [class_name == actual class name] [function_like]
     * constructor   ::=  "~" [class_name == actual class name] [function_like]
     *
     * class_decls   ::=  [visibility] ":"
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
    Syntax::Statement::ClassDef *parseClass();

    /**
     * function_call ::= [expr] "(" [args] ")"
     * arguments     ::= [[expr] "," ...]
     *
     * @param callee expression being called
     */
    Syntax::Expression::FunctionCall *
    parseFunctionCall(Syntax::Expression::Base *callee);

    /**
     * function_call ::= [expr] "(" [args] ")"
     * arguments     ::= [[expr] "," ...]
     *
     * @param callee expression being called
     */
    Syntax::Statement::ImportStmt *parseImportStatement();

    /**
     * identifier    ::= [A-Za-z0-9_] [?genericss expr]
     *
     * @return Syntax::Expression::Identifier* 
     */
    Syntax::Expression::Identifier* parseIdentifier();

    /**
     * expr          ::=  [constant_value] |
     *                    [function_call]  |
     *                    [index_node]     |
     *                    [new_instance]
     * new_instance  ::=  "new" [type_ref][call]
     *
     * @param allowAssign Whether or not allow the assign operator.
     */
    Syntax::Expression::Base *parseExpr(bool allowAssign = true);
};

} // namespace parser
} // namespace snowball

#endif // __SNOWBALL_PARSER_H_
