
#include "snowball/nodes.h"
#include "snowball/colors.h"
#include "snowball/errors.h"
#include "snowball/parser.h"
#include "snowball/logger.h"
#include "snowball/utils/utils.h"

#include "snowball/snowball.h"

#include <string>
#include <memory>
#include <utility>

#include <assert.h>

#define PARSER_ERROR(err, msg) _parser_error(err, msg);
#define UNEXPECTED_TOK(expectation) PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Expected %s, got %s%s%s", expectation, RED, _current_token.to_string().c_str(), RESET));
#define UNEXPECTED_TOK2(expectation, method) PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Expected %s, got %s%s%s while parsing %s", expectation, RED, _current_token.to_string().c_str(), RESET, BOLD, method));
#define ASSERT_TOKEN(tk, ty, idnt) if (tk.type != ty) UNEXPECTED_TOK(idnt);
#define ASSERT_TOKEN2(tk, ty, idnt, method) if (tk.type != ty) UNEXPECTED_TOK2(idnt, method);
#define TOKEN_EQUAL(token, _comp) (token.type == TokenType::_comp)
#define CONSUME(tk, ty, process)  \
    ASSERT_TOKEN_EOF(_current_token, TokenType::ty, tk, process) \
    next_token(); // consume
#define ASSERT_TOKEN_EOF(tk, ty, idnt, method) \
    if (tk.type == TokenType::_EOF) PARSER_ERROR(Error::UNEXPECTED_EOF, Logger::format("Found an unexpected EOF while parsing %s", method)); \
    ASSERT_TOKEN2(tk, ty, idnt, method)

namespace snowball {

    void Parser::parse() {
        bool keep_parsing = true;

        while (keep_parsing) {
            switch (_current_token.type)
            {
                case TokenType::_EOF: {
                    keep_parsing = false;
                    break;
                }

                case TokenType::KWORD_CLASS: {
                    ClassNode* cls = _parse_class();
                    _nodes.push_back(cls);
                    break;
                }

                case TokenType::KWORD_IMPORT: {
                    ImportNode* import_node = _parse_import();
                    _nodes.push_back(import_node);
                    break;
                }

                case TokenType::KWORD_EXTERN: {
                    if (peek(0, true).type != TokenType::KWORD_FUNC) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "expected keyword an extern function declaration");
                    }

                    break;
                }

                case TokenType::SYM_AT: {
                    _nodes.push_back(_parse_decorator());
                    break;
                }

                case TokenType::KWORD_PUBLIC:
                case TokenType::KWORD_PRIVATE: {
                    if (
                        peek(0, true).type != TokenType::KWORD_FUNC
                        && peek(0, true).type != TokenType::KWORD_VAR) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "expected keyword \"func\" or \"var\" after pub/priv declaration");
                    }

                    break;
                }

                case TokenType::KWORD_FUNC: {
                    FunctionNode* function = _parse_function();
                    function->is_lop_level = true;
                    _nodes.push_back(function);
                    break;
                }

                case TokenType::KWORD_MOD: {
                    ModuleNode* mod = _parse_module();
                    _nodes.push_back(mod);
                    break;
                }

                case TokenType::KWORD_VAR: {
                    int _width = _current_token.col;
                    std::pair<int, int> _pos = std::make_pair(_current_token.line, _current_token.col);

                    VarNode* var = _parse_variable();
                    _width = _width - _current_token.col;

                    var->pos = _pos;
                    var->width = (uint32_t)_width;

                    var->isGlobal = true;

                    _nodes.push_back(var);
                    break;
                }

                case TokenType::SYM_SEMI_COLLON:
                    break;

                default:
                    PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Unexpected token found: %s%s%s", BLU, _current_token.to_string().c_str(), RESET))
                    break;
            }

            if (keep_parsing)
                next_token();
        }

        #if _SNOWBALL_PARSER_DEBUG

            PRINT_LINE("Nodes:")
			PRINT_LINE(LINE_SEPARATOR)

			int index = 0;
			for (Node* node : _nodes) {
				DEBUG_PARSER("[%i]: type %d", index, node->type)
				index++;

                if (node->type == Node::Ty::FUNCTION) {
                    for (Node* expr : ((BlockNode*)((FunctionNode*)node)->body)->exprs) {
                        DEBUG_PARSER("  - [%i]: type %d", index, expr->type)
                        index++;
                    }
                }
			}

			PRINT_LINE(LINE_SEPARATOR)

        #endif
    }

    // Parse methods

    ModuleNode* Parser::_parse_module() {
        ASSERT(_current_token.type == TokenType::KWORD_MOD)
        next_token();

        ModuleNode* node = new ModuleNode();
        ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "identifier", "a module body")
        node->name = _current_token.to_string(); next_token();

        ASSERT_TOKEN_EOF(_current_token, TokenType::BRACKET_LCURLY, "{", "a class body")
        while (true) {
            next_token();
            switch (_current_token.type)
            {
                case TokenType::BRACKET_RCURLY: {
                    return node;
                }

                case TokenType::KWORD_CLASS: {
                    ClassNode* cls = _parse_class();
                    node->nodes.push_back(cls);
                    break;
                }

                case TokenType::KWORD_IMPORT: {
                    ImportNode* import_node = _parse_import();
                    node->nodes.push_back(import_node);
                    break;
                }

                case TokenType::KWORD_EXTERN: {
                    if (peek(0, true).type != TokenType::KWORD_FUNC) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "expected keyword an extern function declaration");
                    }

                    break;
                }

                case TokenType::SYM_AT: {
                    node->nodes.push_back(_parse_decorator());
                    break;
                }

                case TokenType::KWORD_PUBLIC:
                case TokenType::KWORD_PRIVATE: {
                    if (
                        peek(0, true).type != TokenType::KWORD_FUNC
                        && peek(0, true).type != TokenType::KWORD_VAR) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "expected keyword \"func\" or \"var\" after pub/priv declaration");
                    }

                    break;
                }

                case TokenType::KWORD_FUNC: {
                    FunctionNode* function = _parse_function();
                    function->is_lop_level = true;
                    node->nodes.push_back(function);
                    break;
                }

                case TokenType::KWORD_MOD: {
                    ModuleNode* mod = _parse_module();
                    node->nodes.push_back(mod);
                    break;
                }

                case TokenType::KWORD_VAR: {
                    int _width = _current_token.col;
                    std::pair<int, int> _pos = std::make_pair(_current_token.line, _current_token.col);

                    VarNode* var = _parse_variable();
                    _width = _width - _current_token.col;

                    var->pos = _pos;
                    var->width = (uint32_t)_width;

                    var->isGlobal = true;

                    node->nodes.push_back(var);
                    break;
                }

                case TokenType::SYM_SEMI_COLLON:
                    break;

                default:
                    PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("'%s' is not allowed inside module blocks", _current_token.to_string().c_str()))
            }
        }
    }

    Node* Parser::_parse_decorator() {
        ASSERT(_current_token.type == TokenType::SYM_AT)
        next_token();

        PARSER_ERROR(TODO, "Decorators are not yet supported!")
    }

    ImportNode* Parser::_parse_import() {
        ASSERT(_current_token.type == TokenType::KWORD_IMPORT)
        next_token();

        ImportNode* node = new ImportNode();

        switch (_current_token.type)
        {
            case TokenType::VALUE_STRING: {
                std::string path = _current_token.to_string();
                path = path.substr(1, path.size() - 2);
                node->path = path;
                break;
            }

            case TokenType::IDENTIFIER: {
                node->path = _current_token.to_string();
                // TODO: check if there is a dot
                break;
            }

            default: {
                UNEXPECTED_TOK2("a string or an identifier", "an import statement")
            }
        }


        return node;
    }

    IfStatementNode* Parser::_parse_ifstmt() {
        ASSERT(_current_token.type == TokenType::KWORD_IF);

        IfStatementNode* stmt = new IfStatementNode();

        stmt->stmt = _parse_expression();
        next_token();

        stmt->body = _parse_block();

        if (peek().type == TokenType::KWORD_ELSE) {
            next_token(); // Consume 'else'
            next_token(); // Consume '}'
            stmt->else_stmt = _parse_block();
        }

        return stmt;
    }

    ClassNode* Parser::_parse_class() {
        ASSERT(_current_token.type == TokenType::KWORD_CLASS);
        next_token();

        ClassNode* cls = new ClassNode();

        // TODO: inheritance
        ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "an identifier", "a class declaration")
        cls->name = _current_token.to_string();
        next_token();

        if (_current_token.type == TokenType::OP_LT) {
            std::vector<Type*> generics = _parse_generic_expr();
            cls->generics = generics;
        }

        if (_current_token.type == TokenType::SYM_COLLON) {
            next_token();

            // TODO: multiple inheritance
            ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "an identifier", "a class inheritance expression")
            cls->parents.push_back(_current_token.to_string());
            next_token();
        }

        ASSERT_TOKEN_EOF(_current_token, TokenType::BRACKET_LCURLY, "{", "a class body")
        ClassNode* top_clas = std::move(_context.current_class);
        _context.current_class = cls;
        while (true) {
            next_token();
            switch (_current_token.type)
            {
                case TokenType::BRACKET_RCURLY: {
                    _context.current_class = top_clas;
                    return cls;
                }

                case TokenType::KWORD_STATIC: {
                    if (peek(0, true).type != TokenType::KWORD_FUNC && peek(0, true).type != TokenType::KWORD_VAR) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "expected keyword \"func\" or \"var\" after static");
                    }
                } break;

                case TokenType::KWORD_PUBLIC:
                case TokenType::KWORD_PRIVATE: {
                    if (
                        peek(0, true).type != TokenType::KWORD_FUNC
                        && peek(0, true).type != TokenType::KWORD_VAR
                        && peek(0, true).type != TokenType::KWORD_STATIC) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "expected keyword \"func\", \"var\" or \"static\" after pub/priv declaration");
                    }
                    break;
                }

                case TokenType::KWORD_VAR: {
                    VarNode* func = _parse_variable();
                    cls->vars.push_back(func);
                } break;

                case TokenType::KWORD_FUNC: {
                    FunctionNode* func = _parse_function();
                    cls->functions.push_back(func);
                } break;

                default:
                    PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("'%s' is not allowed inside function blocks", _current_token.to_string().c_str()))
            }
        }

        // TODO: this does not work if class has 2 duplicate variables
        auto vars_duplicate = std::unique(cls->vars.begin(), cls->vars.end());
        if (vars_duplicate != cls->vars.end()) {
            PARSER_ERROR(VARIABLE_ERROR, Logger::format("Class attribute already exist names '%s'", (*vars_duplicate)->name.c_str()))
        }

        _context.current_class = top_clas;
        return cls;
    }

    VarNode* Parser::_parse_variable() {
        ASSERT(_current_token.type == TokenType::KWORD_VAR)
        next_token();

        VarNode* var = new VarNode();
        ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "an identifier", "variable")

        var->name = _current_token.to_string();
        next_token();

        if ((_context.current_class != nullptr && _context.current_function == nullptr) || peek(0, true).type == TokenType::SYM_COLLON) {
            CONSUME(":", SYM_COLLON, "a variable declaration")
            ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "an identifier", "a variable declaration")

            var->vtype = _parse_type();
            // next_token();
        }

        ASSERT_TOKEN_EOF(_current_token, TokenType::OP_EQ, "=", "variable")

        if (peek().type == TokenType::_EOF) {
            PARSER_ERROR(Error::UNEXPECTED_EOF, "Found an unexpected EOF while parsing variable's statement");
        }

        Node* value = _parse_expression();
        var->value = value;

        if (_current_token.type == TokenType::SYM_SEMI_COLLON) {
            next_token();
        }

        return var;
    }

    FunctionNode* Parser::_parse_function() {
        // PARSER_ERROR(Error::TODO, "Functions are not yet supported.")

        // Assert if the token is the "func" keyword
        // and consume it.
        ASSERT(_current_token.type == TokenType::KWORD_FUNC)

        // todo: move to snowball utils
        struct compareArgs
        {
            ArgumentNode* key;
            compareArgs(ArgumentNode* i): key(i) {}

            bool operator()(ArgumentNode* i) {
                return (i->name == key->name);
            }
        };

        FunctionNode* func = new FunctionNode();
        next_token();

        Token pk = peek(-3, true);
        if (pk.type == TokenType::KWORD_EXTERN) {
            func->is_extern = true;
        } else if (pk.type == TokenType::KWORD_STATIC) {
            func->is_static = true;
            if (peek(-4, true).type == TokenType::KWORD_PUBLIC || peek(-4, true).type == TokenType::KWORD_PRIVATE ) {
                func->is_public = peek(-4, true).type == TokenType::KWORD_PUBLIC;
            }
        } else if (pk.type == TokenType::KWORD_PUBLIC || pk.type == TokenType::KWORD_PRIVATE ) {
            func->is_public = pk.type == TokenType::KWORD_PUBLIC;
        }

        // Find function's name
        ASSERT_TOKEN(_current_token, TokenType::IDENTIFIER, "an identifier")
        func->name = _current_token.to_string();

        next_token();

        if (_current_token.type == TokenType::OP_LT) {

            if (func->is_extern) {
                PARSER_ERROR(SYNTAX_ERROR, "Can't define an extern function with generics")
            }

            std::vector<Type*> generics = _parse_generic_expr();
            func->generics = generics;
        }

        std::vector<ArgumentNode*> arguments;

        // TODO: check for args
        if (_current_token.type == TokenType::BRACKET_LPARENT) {
            next_token();
            while (true) {
                if (_current_token.type == TokenType::IDENTIFIER) {
                    // Argument structure: (name: type, name2: type2 = default, ...argv)
                    // TODO: argv, default

                    if (func->is_extern) {
                        Type* arg_type = _parse_type();
                        ArgumentNode* argument = new ArgumentNode("", arg_type);

                        arguments.push_back(argument);

                       if (_current_token.type == TokenType::SYM_COMMA) {
                            next_token();
                        } else if (_current_token.type == TokenType::BRACKET_RPARENT) {
                            next_token(); break;
                        } else {
                            UNEXPECTED_TOK("A comma")
                        }
                    } else {
                        std::string name = _current_token.to_string();
                        Type* arg_type;

                        next_token(); // consume name

                        CONSUME(":", SYM_COLLON, "argument statement")

                        ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "<type>", "argument type declaration")
                        arg_type = _parse_type();

                        ArgumentNode* argument = new ArgumentNode(name, arg_type);

                        if (std::any_of(arguments.begin(), arguments.end(), compareArgs(argument))) {
                            PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("duplicate argument '%s' in function definition", argument->name.c_str()))
                        }

                        arguments.push_back(argument);

                        // cleanup
                        if (_current_token.type == TokenType::SYM_COMMA) {
                            next_token();
                        } else if (_current_token.type == TokenType::BRACKET_RPARENT) {
                            next_token(); break;
                        } else {
                            UNEXPECTED_TOK("a comma")
                        }
                    }
                } else if (_current_token.type == TokenType::BRACKET_RPARENT) {
                    next_token();
                    break;
                } else if (_current_token.type == TokenType::SYM_DOT && peek().type == TokenType::SYM_DOT && peek(1, true).type == TokenType::SYM_DOT) {

                    if (!func->is_extern) {
                        PARSER_ERROR(TODO, "Variadic Arguments for non extern functions")
                    }

                    func->has_vargs = true;
                    next_token(2);
                } else {
                    UNEXPECTED_TOK("An identifier or a ')'")
                }
            }
        }

        Type* return_type;

        // Consume an arrow
        // TODO: if there is no arrow, return type is Void
        // TODO: if it is a constructor, return type is the parent Class
        if (!(_context.current_class != nullptr && func->name == "__init")) {
            ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "Identifier", "Function return type")
            return_type = _parse_type();
        } else {
            return_type = new Type(_context.current_class->name);
        }


        func->arguments = arguments;
        func->return_type = return_type;

        _context.current_function = func;

        if (_current_token.type == TokenType::SYM_SEMI_COLLON) {
            func->is_foward = true;
            next_token();
        } else {

            if (func->is_extern) {
                PARSER_ERROR(SYNTAX_ERROR, "External functions can't have body blocks!")
            }

            BlockNode* body = _parse_block();
            func->body = body;
        }

        _context.current_function = nullptr;
        return func;
    }



    BlockNode* Parser::_parse_block(std::vector<TokenType> p_termination) {
        std::vector<Node *> stmts;
        BlockNode* b_node = new BlockNode();
        Token tk = _current_token;

        while (true) {

            tk = peek();

            switch (tk.type)
            {
                case TokenType::_EOF: {
                    PARSER_ERROR(Error::UNEXPECTED_EOF, "Found an unexpected EOF while parsing a block");
                    break;
                }

                case TokenType::BRACKET_LCURLY: {
                    next_token();
                    stmts.push_back(_parse_block());
                    break;
                }

                case TokenType::KWORD_IF: {
                    next_token();
                    IfStatementNode* stmt = _parse_ifstmt();
                    stmts.push_back(stmt);
                    break;
                }

                case TokenType::KWORD_VAR: {
                    int _width = _current_token.col;
                    std::pair<int, int> _pos = std::make_pair(_current_token.line, _current_token.col);

                    next_token();
                    VarNode* var = _parse_variable();
                    _width = _width - _current_token.col;

                    var->pos = _pos;
                    var->width = (uint32_t)_width;

                    stmts.push_back(var);
                    break;
                }

                case TokenType::KWORD_RETURN: {
                    if (_context.current_function == nullptr) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "Return statements can only be used inside functions")
                    }

                    int _width = _current_token.col;
                    std::pair<int, int> _pos = std::make_pair(_current_token.line, _current_token.col);

                    next_token();
                    ReturnNode* ret = _parse_return();
                    _width = _width - _current_token.col;

                    ret->pos = _pos;
                    ret->width = (uint32_t)_width;

                    _context.current_function->has_return = true;
                    stmts.push_back(ret);
                    break;
                }

                default: {
                    for (TokenType termination : p_termination) {
                        if (tk.type == termination) {
                            next_token();
                            b_node->exprs = stmts;
                            return b_node;
                        }
                    }

                    Node* expr = _parse_expression(true);
                    stmts.push_back(expr);
                }
            }
        }

        b_node->exprs = stmts;
        return b_node;
    }

    ReturnNode* Parser::_parse_return() {
        ASSERT(_current_token.type == TokenType::KWORD_RETURN)
        ASSERT(_context.current_function != nullptr)

        ReturnNode* node = new ReturnNode();
        node->value = _parse_expression();
        node->parent = _context.current_function;
        return node;
    }

    // Private

    void Parser::previous_token(int p_offset) {
        try {
            __token_possition--;
            _current_token = _tokens.at(__token_possition);
        } catch (std::out_of_range& _) {
            PARSER_ERROR(Error::BUG, "Index error")
        }
    }

    void Parser::next_token(int p_offset) {
        try {
            __token_possition += (p_offset + 1);
            _current_token = _tokens.at(__token_possition);
        } catch (std::out_of_range& _) {
            PARSER_ERROR(Error::BUG, "Index error")
        }
    }

    Token Parser::peek(int p_offset, bool p_safe) {
        Token tmp = { TokenType::_EOF };
        if ((__token_possition + 1) + p_offset < 0 || (__token_possition + 1) + p_offset >= (int)_tokens.size()) {
            if (p_safe) return tmp;
            else PARSER_ERROR(Error::BUG, "Parser::peek() index out of bounds");
        }
        return _tokens.at((__token_possition + 1) + p_offset);
    }

    void Parser::_parser_error(Error type, std::string msg) {
        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, std::pair<int, int>(_current_token.line, _current_token.col), _current_token.to_string().size());
        throw ParserError(type, msg, dbg_info);
    }

    CallNode* Parser::_parse_function_call() {
        ASSERT(_current_token.type == TokenType::IDENTIFIER)

        CallNode* callNode = new CallNode();
        callNode->method = _current_token.to_string();
        next_token();

        std::vector<Type*> generics;
        bool has_generics = false;
        if (_current_token.type == TokenType::OP_LT) {
            has_generics = true;
            generics = _parse_generic_expr();
        }

        if (_current_token.type == TokenType::BRACKET_LPARENT) {
            ASSERT(_current_token.type == TokenType::BRACKET_LPARENT)

            std::vector<Node*> arguments;
            Token tk = peek();

            if (tk.type == TokenType::BRACKET_RPARENT) {
                next_token(); // eat BRACKET_RPARAN
            } else {
                while (true) {

                    Node* arg = _parse_expression();
                    arguments.push_back(arg);

                    next_token();
                    tk = _current_token;

                    if (tk.type == TokenType::SYM_COMMA) {
                        // pass
                    } else if (tk.type == TokenType::BRACKET_RPARENT) {
                        break;
                    } else {
                        PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Expected a comma or a right paren. found ('%s') while parsing function call", _current_token.to_string().c_str()))
                    }
                }
            }

            callNode->arguments = arguments;
            if (generics.size() > 0) callNode->generics = generics;
            return callNode;
        }


        UNEXPECTED_TOK("a left parenthesis or a generic statement")
        return nullptr; // Used to remove those anoying warnings >:(
    }

    Node* Parser::_parse_expression(bool p_allow_assign) {
        std::vector<Node *> expressions;

        while (true) {
            Node* expression;
            next_token();

            Token tk = _current_token;

            #define IF_TOKEN(comp) TOKEN_EQUAL(tk, comp)
            if (IF_TOKEN(VALUE_BOOL) || IF_TOKEN(VALUE_NULL) || IF_TOKEN(VALUE_FLOAT) || IF_TOKEN(VALUE_NUMBER) || IF_TOKEN(VALUE_STRING) || IF_TOKEN(VALUE_UNDEFINED)) {
                expression = new ConstantValue(tk.type, tk.to_string());
            } else if (IF_TOKEN(KWORD_NEW)) {
                next_token();
                expression = new NewNode(_parse_function_call());
            } else if (IF_TOKEN(OP_NOT) || IF_TOKEN(OP_PLUS) || IF_TOKEN(OP_MINUS) || IF_TOKEN(OP_BIT_NOT)) {
                if (tk.type == TokenType::OP_NOT)          expressions.push_back(new BinaryOp(OpType::OP_NOT))      ;
                else if (tk.type == TokenType::OP_PLUS)    expressions.push_back(new BinaryOp(OpType::OP_POSITIVE)) ;
                else if (tk.type == TokenType::OP_MINUS)   expressions.push_back(new BinaryOp(OpType::OP_NEGATIVE)) ;
                else if (tk.type == TokenType::OP_BIT_NOT) expressions.push_back(new BinaryOp(OpType::OP_BIT_NOT))  ;

                continue;
            } else if (IF_TOKEN(IDENTIFIER)) {
                if (peek(0, true).type == TokenType::BRACKET_LPARENT || peek(0, true).type == TokenType::OP_LT) {
                    expression = _parse_function_call();
                } else {
                    expression = new IdentifierNode(tk);
                }
            } else {
                UNEXPECTED_TOK("a valid expression")
            }
            #undef IF_TOKEN

            // Indexing
            while (true) {
                tk = peek(0, true);
                if (tk.type == TokenType::SYM_DOT) {
                    next_token(1);
                    tk = _current_token;

                    ASSERT_TOKEN_EOF(tk, TokenType::IDENTIFIER, "an identifier", "function index/call")

                    if (peek().type == TokenType::BRACKET_LPARENT || peek().type == TokenType::OP_LT)  {
                        CallNode* call = _parse_function_call();

                        call->base = expression;
                        expression = call;
                    } else {
                        IndexNode* index = new IndexNode();

                        index->base = expression;
                        index->member = new IdentifierNode(_current_token);

                        expression = index;
                    }
                } if (tk.type == TokenType::SYM_COLCOL) { // same thing but calling static function
                    next_token(1);
                    ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "an identifier", "static function index/call")

                    if (peek(0, true).type == TokenType::BRACKET_LPARENT || peek(0, true).type == TokenType::OP_LT)  {
                        CallNode* call = _parse_function_call();

                        call->base = expression;
                        call->is_static_call = true;

                        expression = call;
                    } else {
                        IndexNode* index = new IndexNode();

                        index->base = expression;
                        index->member = new IdentifierNode(_current_token);

                        expression = index;
                    }
                } else {
                    break;
                }
            }

            expressions.emplace_back(expression);
            tk = peek();

            OpType op;
            bool valid = true;

            switch (tk.type) {
            #define OP_CASE(m_op) case TokenType::m_op: {op = OpType::m_op; break;}
                OP_CASE(OP_EQ);
                OP_CASE(OP_EQEQ);
                OP_CASE(OP_PLUS);
                OP_CASE(OP_PLUSEQ);
                OP_CASE(OP_MINUS);
                OP_CASE(OP_MINUSEQ);
                OP_CASE(OP_MUL);
                OP_CASE(OP_MULEQ);
                OP_CASE(OP_DIV);
                OP_CASE(OP_DIVEQ);
                OP_CASE(OP_MOD);
                OP_CASE(OP_MOD_EQ);
                OP_CASE(OP_LT);
                OP_CASE(OP_LTEQ);
                OP_CASE(OP_GT);
                OP_CASE(OP_GTEQ);
                OP_CASE(OP_AND);
                OP_CASE(OP_OR);
                OP_CASE(OP_NOT);
                OP_CASE(OP_NOTEQ);
                OP_CASE(OP_BIT_NOT);
                OP_CASE(OP_BIT_LSHIFT);
                OP_CASE(OP_BIT_LSHIFT_EQ);
                OP_CASE(OP_BIT_RSHIFT);
                OP_CASE(OP_BIT_RSHIFT_EQ);
                OP_CASE(OP_BIT_OR);
                OP_CASE(OP_BIT_OR_EQ);
                OP_CASE(OP_BIT_AND);
                OP_CASE(OP_BIT_AND_EQ);
                OP_CASE(OP_BIT_XOR);
                OP_CASE(OP_BIT_XOR_EQ);

            #undef OP_CASE

                default: valid = false;
            }

            if (valid) {
                next_token(); // Eat peeked token.
                expressions.push_back(new BinaryOp(op));
            } else {

                // Casting will be done with the "as" keyword.
                if (tk.type == TokenType::KWORD_AS) {
                    next_token();
                    tk = peek();
                    if (tk.type == TokenType::IDENTIFIER) {
                        next_token();
                        CastNode* cast_node = new CastNode();
                        cast_node->cast_type = _parse_type();
                        previous_token();
                        cast_node->expr = expressions.at(expressions.size() - 1);

                        expressions.at(expressions.size() - 1) = cast_node;
                    }
                }

                break;
            }

        }

        Node* tree = _build_op_tree(expressions);
        if (tree->type == Node::Ty::OPERATOR) {
            if (!p_allow_assign && BinaryOp::is_assignment((BinaryOp*)tree)) {
                PARSER_ERROR(Error::SYNTAX_ERROR, "assignment is not allowed inside expression.");
            }
        }

        return tree;
    }

    Node* Parser::_build_op_tree(std::vector<Node*> &expressions) {
        ASSERT(expressions.size() > 0)

        while (expressions.size() > 1) {

            int next_op = -1;
            int min_precedence = 0xFFFFF;
            bool unary = false;

            for (int i = 0; i < (int)expressions.size(); i++) {
                BinaryOp* expression = static_cast<BinaryOp*>(expressions[i]);
                if (expression->type != Node::Ty::OPERATOR) {
                    continue;
                }

                int precedence = -1;
                switch (expression->op_type) {
                    case OpType::OP_NOT:
                    case OpType::OP_BIT_NOT:
                    case OpType::OP_POSITIVE:
                    case OpType::OP_NEGATIVE: {
                        precedence = 0;
                        break;
                    }

                    case OpType::OP_MUL:
                    case OpType::OP_DIV:
                    case OpType::OP_MOD: {
                        precedence = 1;
                        break;
                    }

                    case OpType::OP_PLUS:
                    case OpType::OP_MINUS: {
                        precedence = 2;
                        break;
                    }

                    case OpType::OP_BIT_LSHIFT:
                    case OpType::OP_BIT_RSHIFT: {
                        precedence = 3;
                        break;
                    }

                    case OpType::OP_LT:
                    case OpType::OP_LTEQ:
                    case OpType::OP_GT:
                    case OpType::OP_GTEQ: {
                        precedence = 4;
                        break;
                    }

                    case OpType::OP_EQEQ:
                    case OpType::OP_NOTEQ: {
                        precedence = 5;
                        break;
                    }

                    case OpType::OP_BIT_AND: {
                        precedence = 6;
                        break;
                    }

                    case OpType::OP_BIT_XOR: {
                        precedence = 7;
                        break;
                    }

                    case OpType::OP_BIT_OR: {
                        precedence = 8;
                        break;
                    }

                    case OpType::OP_AND: {
                        precedence = 9;
                        break;
                    }

                    case OpType::OP_OR: {
                        precedence = 10;
                        break;
                    }

                    case OpType::OP_EQ:
                    case OpType::OP_PLUSEQ:
                    case OpType::OP_MINUSEQ:
                    case OpType::OP_MULEQ:
                    case OpType::OP_DIVEQ:
                    case OpType::OP_MOD_EQ:
                    case OpType::OP_BIT_LSHIFT_EQ:
                    case OpType::OP_BIT_RSHIFT_EQ:
                    case OpType::OP_BIT_AND_EQ:
                    case OpType::OP_BIT_XOR_EQ:
                    case OpType::OP_BIT_OR_EQ: {
                        precedence = 11;
                        break;
                    }

                    case OpType::NONE: {
                        precedence = -1;
                        break;
                    }
                }

                if (precedence < min_precedence) {
                    min_precedence = precedence;
                    next_op = i;
                    OpType op = expression->op_type;
                    unary = (
                        op == OpType::OP_NOT      ||
                        op == OpType::OP_BIT_NOT  ||
                        op == OpType::OP_POSITIVE ||
                        op == OpType::OP_NEGATIVE );
                    // break;
                }
            }

            ASSERT(next_op >= 0);

            if (unary) {

                int next_expr = next_op;
                while (expressions[next_expr]->type == Node::Ty::OPERATOR) {
                    if (++next_expr == expressions.size()) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "expected an expression.");
                    }
                }

                for (int i = next_expr - 1; i >= next_op; i--) {
                    BinaryOp* op_node = new BinaryOp(((BinaryOp*)expressions[(size_t)i])->op_type);

                    op_node->left = expressions[(size_t)i + 1];

                    expressions.at(i) = op_node;
                    expressions.erase(expressions.begin() + i + 1);

                }
            } else {
                ASSERT(next_op >= 1 && next_op < (int)expressions.size() - 1)
                ASSERT((!(expressions[(size_t)next_op - 1]->type == Node::Ty::OPERATOR)) && (!(expressions[(size_t)next_op + 1]->type == Node::Ty::OPERATOR)));

                BinaryOp* op_node = new BinaryOp(((BinaryOp*)expressions[(size_t)next_op])->op_type);

                if (expressions[(size_t)next_op - 1]->type == Node::Ty::OPERATOR) {
                    if (BinaryOp::is_assignment((BinaryOp*)expressions[(size_t)next_op - 1])) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "unexpected assignment.")
                    }
                }

                if (expressions[(size_t)next_op + 1]->type == Node::Ty::OPERATOR) {
                    if (BinaryOp::is_assignment((BinaryOp*)expressions[(size_t)next_op - 1])) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "unexpected assignment.")
                    }
                }

                op_node->left = expressions[(size_t)next_op - 1];
                op_node->right = expressions[(size_t)next_op + 1];

                expressions.at((next_op - 1)) = op_node;

                expressions.erase(expressions.begin() + next_op);
                expressions.erase(expressions.begin() + next_op);
            }
        }

        return expressions[0];
    }

    Type* Parser::_parse_type() {
        ASSERT(_current_token.type == TokenType::IDENTIFIER)

        std::string name = _current_token.to_string();
        std::vector<Type*> type_generics;
        next_token();

        if (_current_token.type == TokenType::OP_LT) {
            type_generics = _parse_generic_expr();
        }

        return new Type(name, type_generics);
    }

    std::vector<Type*> Parser::_parse_generic_expr() {
        ASSERT(_current_token.type == TokenType::OP_LT)
        std::vector<Type*> types;

        while (true) {
            next_token();

            if (_current_token.type == TokenType::_EOF) {
                PARSER_ERROR(Error::UNEXPECTED_EOF, "Found EOF while parsing generic expression")
            } else if (_current_token.type == TokenType::IDENTIFIER) {
                types.push_back(_parse_type());

                if (_current_token.type == TokenType::OP_GT) {
                    next_token();
                    break;
                } else if (_current_token.type == TokenType::SYM_COMMA && peek(0, true).type == TokenType::IDENTIFIER) {
                    continue;
                }

                UNEXPECTED_TOK2("A comma or a >", "a generic expression")
            } else if (_current_token.type == TokenType::OP_GT) {
                next_token();
                break;
            } else {
                UNEXPECTED_TOK("a vaid generic expression")
            }
        }

        return types;
    }
}
