
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

                case TokenType::KWORD_TEST: {
                    TestingNode* unit_test = _parse_unittest();
                    _nodes.push_back(unit_test);
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

                // case TokenType::VALUE_BOOL:
                // case TokenType::VALUE_NULL:
                // case TokenType::VALUE_FLOAT:
                // case TokenType::VALUE_NUMBER:
                // case TokenType::VALUE_STRING:
                // case TokenType::VALUE_UNDEFINED: {

                //     int _width = _current_token.col;
                //     std::pair<int, int> _pos = std::make_pair(_current_token.line, _current_token.col);

                //     ConstantValue* value = static_cast<ConstantValue *>(_parse_expression()); // Type: ConstantValue
                //     _width = _width - _current_token.col;

                //     value->pos = _pos;
                //     value->width = (uint32_t)_width;

                //     _nodes.push_back(value);
                //     break;
                // }

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
			}

			PRINT_LINE(LINE_SEPARATOR)

        #endif
    }

    // Parse methods

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

    TestingNode* Parser::_parse_unittest() {
        ASSERT(_current_token.type == TokenType::KWORD_TEST);
        next_token();

        TestingNode* test = new TestingNode();

        // TODO: parse for unit testing options (skip, allow_output, ...)
        ASSERT_TOKEN_EOF(_current_token, TokenType::VALUE_STRING, "an unit test description", "a test declaration")
        std::string description = _current_token.to_string(); next_token();

        BlockNode* block = _parse_block({ TokenType::BRACKET_RCURLY }, true);

        test->block = block;
        test->description = description;

        return test;
    }

    ClassNode* Parser::_parse_class() {
        ASSERT(_current_token.type == TokenType::KWORD_CLASS);
        next_token();

        ClassNode* cls = new ClassNode();

        // TODO: inheritance
        ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "an identifier", "a class declaration")
        cls->name = _current_token.to_string();
        next_token();

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

        if (_context.current_class != nullptr || peek(0, true).type == TokenType::SYM_COLLON) {
            CONSUME(":", SYM_COLLON, "a variable declaration")
            ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "an identifier", "a variable declaration")

            var->vtype = _current_token.to_string();
            next_token();
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
        if (pk.type == TokenType::KWORD_STATIC) {
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
            std::vector<std::string> generics = _parse_generic_expr();
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

                    std::string name = _current_token.to_string();
                    std::string type_name;

                    next_token(); // consume name

                    CONSUME(":", SYM_COLLON, "argument statement")

                    ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "<type>", "argument type declaration")
                    type_name = _current_token.to_string();
                    next_token(); // consume :

                    ArgumentNode* argument = new ArgumentNode(name, type_name);

                    if (std::any_of(arguments.begin(), arguments.end(), compareArgs(argument))) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("duplicate argument '%s' in function definition", argument->name.c_str()))
                    }

                    arguments.push_back(argument);

                    // cleanup
                    if (_current_token.type == TokenType::SYM_COMMA) {
                        next_token();
                        if (_current_token.type == TokenType::BRACKET_RPARENT) {
                            next_token();
                            break;
                        } else if (_current_token.type == TokenType::IDENTIFIER) {
                            continue;
                        }

                        UNEXPECTED_TOK("An indentifier or a ')'")

                    } else if (_current_token.type == TokenType::BRACKET_RPARENT) {
                        next_token();
                        break;
                    }
                } else if (_current_token.type == TokenType::BRACKET_RPARENT) {
                    next_token();
                    break;
                } else {
                    UNEXPECTED_TOK("An identifier or a ')'")
                }
            }
        }

        std::string return_type;

        // Consume an arrow
        // TODO: if there is no arrow, return type is Void
        // TODO: if it is a constructor, return type is the parent Class
        if (!(_context.current_class != nullptr && func->name == "__init")) {
            CONSUME("->", OP_MINUS, "Function return type")
            CONSUME("->", OP_GT, "Function return type")

            ASSERT_TOKEN_EOF(_current_token, TokenType::IDENTIFIER, "Identifier", "Function return type")
            return_type = _current_token.to_string();
            next_token();
        } else {
            return_type = _context.current_class->name;
        }


        func->arguments = arguments;
        func->return_type = return_type;

        _context.current_function = func;
        BlockNode* body = _parse_block();
        func->body = body;

        _context.current_function = nullptr;
        return func;
    }



    BlockNode* Parser::_parse_block(std::vector<TokenType> p_termination, bool is_test) {
        std::vector<Node *> stmts;
        BlockNode* b_node = new BlockNode();

        while (true) {

            next_token();
            Token tk = _current_token;

            switch (tk.type)
            {
                case TokenType::_EOF: {
                    PARSER_ERROR(Error::UNEXPECTED_EOF, "Found an unexpected EOF while parsing a block");
                    break;
                }

                case TokenType::KWORD_VAR: {
                    int _width = _current_token.col;
                    std::pair<int, int> _pos = std::make_pair(_current_token.line, _current_token.col);

                    VarNode* var = _parse_variable();
                    _width = _width - _current_token.col;

                    var->pos = _pos;
                    var->width = (uint32_t)_width;

                    stmts.push_back(var);
                    break;
                }

                case TokenType::KWORD_ASSERT: {
                    if (is_test) {
                        int _width = _current_token.col;
                        std::pair<int, int> _pos = std::make_pair(_current_token.line, _current_token.col);

                        AssertNode* node = new AssertNode();
                        Node* expr = _parse_expression();
                        _width = _width - _current_token.col;

                        node->pos = _pos;
                        node->expr = expr;
                        node->width = (uint32_t)_width;

                        stmts.push_back(node);
                        break;
                    } // fall through
                }

                case TokenType::KWORD_RETURN: {
                    if (_context.current_function == nullptr) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "Return statements can only be used inside functions")
                    } else if (is_test) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "Return statements can't be used inside unit tests!")
                    }

                    int _width = _current_token.col;
                    std::pair<int, int> _pos = std::make_pair(_current_token.line, _current_token.col);

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
                            b_node->exprs = stmts;
                            return b_node;
                        }
                    }

                    Node* expr = _parse_expression();
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
    void Parser::next_token(int p_offset) {
        try {
            __token_possition++;
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

        std::vector<std::string> generics;
        if (peek(0, true).type == TokenType::OP_LT) {
            next_token();
            generics = _parse_generic_expr();
        }

        if (peek(0, true).type == TokenType::BRACKET_LPARENT || _current_token.type == TokenType::BRACKET_LPARENT) {

            if (peek(0, true).type == TokenType::BRACKET_LPARENT)
                next_token();

            std::vector<Node*> arguments;
            while (true) {
                if (_current_token.type == TokenType::BRACKET_RPARENT) {
                    break;
                }

                Node* expr = _parse_expression();
                next_token();

                arguments.push_back(expr);
                if (_current_token.type == TokenType::SYM_COMMA) {
                    next_token();
                } else if (_current_token.type == TokenType::BRACKET_RPARENT) {
                    break;
                } else {
                    PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Unexpected symbol found ('%s') while parsing function call", _current_token.to_string().c_str()))
                }
            }

            callNode->arguments = arguments;
            if (generics.size() > 0) callNode->generics = generics;
            return callNode;
        }

        next_token();
        UNEXPECTED_TOK("A left parenthesis")
    }

    Node* Parser::_parse_expression() {
        std::vector<Node *> expressions;

        while (true) {
            Node* expression;
            next_token();

            Token tk = _current_token;

            switch (tk.type)
            {
                case TokenType::VALUE_BOOL:
                case TokenType::VALUE_NULL:
                case TokenType::VALUE_FLOAT:
                case TokenType::VALUE_NUMBER:
                case TokenType::VALUE_STRING:
                case TokenType::VALUE_UNDEFINED: {
                    expression = new ConstantValue(tk.type, tk.to_string());
                    break;
                }

                case TokenType::KWORD_NEW: {
                    next_token();
                    expression = new NewNode(_parse_function_call());
                    break;
                }

                case TokenType::OP_NOT:
                case TokenType::OP_PLUS:
                case TokenType::OP_MINUS:
                case TokenType::OP_BIT_NOT: {

                    if (tk.type == TokenType::OP_NOT)          expressions.push_back(new BinaryOp(OpType::OP_NOT))      ;
                    else if (tk.type == TokenType::OP_PLUS)    expressions.push_back(new BinaryOp(OpType::OP_POSITIVE)) ;
                    else if (tk.type == TokenType::OP_MINUS)   expressions.push_back(new BinaryOp(OpType::OP_NEGATIVE)) ;
                    else if (tk.type == TokenType::OP_BIT_NOT) expressions.push_back(new BinaryOp(OpType::OP_BIT_NOT))  ;

                    continue;
                }

                case TokenType::IDENTIFIER: {
                    if (peek(0, true).type == TokenType::BRACKET_LPARENT || peek(0, true).type == TokenType::OP_LT) {
                        expression = _parse_function_call();
                    } else {
                        expression = new IdentifierNode(tk);
                    }
                    break;
                }

                default:
                    UNEXPECTED_TOK("a valid expression")
            }

            // Indexing
            while (true) {
                Token token = peek(0, true);
                if (token.type == TokenType::SYM_DOT) {
                    next_token(); next_token();
                    ASSERT_TOKEN_EOF(tk, TokenType::IDENTIFIER, "an identifier", "function index/call")

                    if (peek(0, true).type == TokenType::BRACKET_LPARENT)  {
                        Node* base = expression;
                        CallNode* call = _parse_function_call();
                        call->base = base;

                        expression = call;
                    } else {
                        // just indexing
                    }
                } if (token.type == TokenType::SYM_COLCOL) { // same thing but calling static function
                    next_token(); next_token();
                    ASSERT_TOKEN_EOF(tk, TokenType::IDENTIFIER, "an identifier", "static function index/call")

                    if (peek(0, true).type == TokenType::BRACKET_LPARENT)  {
                        Node* base = expression;
                        CallNode* call = _parse_function_call();
                        call->base = base;
                        call->is_static_call = true;

                        expression = call;
                    } else {
                        // just indexing
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
                break;
            }

        }

        Node* op_tree = _build_op_tree(expressions);
        return op_tree;
    }

    Node* Parser::_build_op_tree(std::vector<Node*> &expressions) {
        ASSERT(expressions.size() > 0)

        while (expressions.size() > 1) {

            int next_op = -1;
            int min_precedence = 0xFFFFF;
            bool unary = false;

            for (int i = 0; i < (int)expressions.size(); i++) {
                BinaryOp* expression = static_cast<BinaryOp*>(expressions[i]);
                if (expression->type != Node::Type::OPERATOR) {
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
                        // TODO: throw error with possition of the expression, not the current token
                        // TODO: possible solution, go back a token?
                        PARSER_ERROR(Error::SYNTAX_ERROR, Logger::format("Operator '%s' not allowed in expressions", expression->to_string().c_str()))
                    }
                        // precedence = 11;
                        // break;

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
                while (expressions[next_expr]->type == Node::Type::OPERATOR) {
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
                ASSERT((!(expressions[(size_t)next_op - 1]->type == Node::Type::OPERATOR)) && (!(expressions[(size_t)next_op + 1]->type == Node::Type::OPERATOR)));

                BinaryOp* op_node = new BinaryOp(((BinaryOp*)expressions[(size_t)next_op])->op_type);

                if (expressions[(size_t)next_op - 1]->type == Node::Type::OPERATOR) {
                    if (BinaryOp::is_assignment((BinaryOp*)expressions[(size_t)next_op - 1])) {
                        PARSER_ERROR(Error::SYNTAX_ERROR, "unexpected assignment.")
                    }
                }

                if (expressions[(size_t)next_op + 1]->type == Node::Type::OPERATOR) {
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

    std::vector<std::string> Parser::_parse_generic_expr() {
        ASSERT(_current_token.type == TokenType::OP_LT)
        std::vector<std::string> types;

        while (true) {
            next_token();

            if (_current_token.type == TokenType::_EOF) {
                PARSER_ERROR(Error::UNEXPECTED_EOF, "Found EOF while parsing generic expression")
            } else if (_current_token.type == TokenType::IDENTIFIER) {
                types.push_back(_current_token.to_string());
                next_token();

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
