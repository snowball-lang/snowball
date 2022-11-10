
#include <map>
#include <memory>
#include <string>
#include <stdint.h>

#include "token.h"
#include "types.h"
#include "operators.h"
#include "llvm/IR/Value.h"

#ifndef __SNOWBALL_NODE_H_
#define __SNOWBALL_NODE_H_

namespace snowball {

    typedef struct Node {
        enum class Ty {
			UNKNOWN = -1,

			IMPORT,
			CAST,
			CLASS,
			TERNARY,
			ENUM,
			FUNCTION,
			BLOCK,
			IDENTIFIER,
			ATTRIBUTE,
			ARGUMENT,
			VAR,
			CONST,
			CONST_VALUE, // evaluvated to compile time constants ex: "str", 3.14, Array(1, 2), ...
			ARRAY,       // literal array ex: [1, 2, [3]]
			MAP,         // literal map   ex: { "key":"value", 1:[2, 3] }
			SUPER,
			CALL,
			NEW_CALL,
			MODULE,
			INDEX,
			MAPPED_INDEX,
			OPERATOR,
			OPERATOR_OVERRIDE,

			// control flow
			RETURN,
			IF_STMT,

			SWITCH,
			WHILE,
			FOR_LOOP,
			BREAK,
			CONTINUE,

            SN_NODES_H,
		};

        Ty type = Ty::UNKNOWN;

		std::pair<int, int> pos;
        uint32_t width = 1; // width of the node ^^^^ (dbg).

		bool is_op = false;

		virtual ~Node() = default;
    } Node;

	struct ModuleNode : public Node {
		std::string name;
		std::vector<Node*> nodes;

		bool isPublic = false;

		ModuleNode() {
			type = Ty::MODULE;
		};

		~ModuleNode() {};
	};

	struct BlockNode : public Node {
		std::vector<Node*> exprs;

		BlockNode() {
			type = Ty::BLOCK;
		};

		~BlockNode() {};
	};

	struct IfStatementNode : public Node {
		Node* stmt;

		BlockNode* body;
		BlockNode* else_stmt = NULL;

		IfStatementNode() {
			type = Ty::IF_STMT;
		};

		~IfStatementNode() {};
	};

	struct ArgumentNode : public Node {
		std::string name;
		Type* arg_type;

		ArgumentNode(std::string p_name, Type* p_type) {
			// todo: default values
			name = p_name;
			arg_type = p_type;
			type = Ty::ARGUMENT;
		};

		~ArgumentNode() {};
	};

	struct CastNode : public Node {
		Node* expr;
		Type* cast_type;

		CastNode() {
			type = Ty::CAST;
		};

		~CastNode() {};
	};


	struct FunctionNode : public Node {
		BlockNode* body;

		std::string name;
		std::string extern_name; // only used for extern functions

		Type* return_type;
		std::vector<ArgumentNode *> arguments;

		std::vector<Type*> generics;

		bool is_static = false;
		bool has_vargs = false;
		bool is_foward = false;
		bool is_extern = false;
		bool is_public = false;
		bool is_virtual = false;
		bool is_lop_level = false;

		FunctionNode() {
			type = Ty::FUNCTION;
		};

		~FunctionNode() {};
	};

	struct OperatorNode : public FunctionNode {
		OperatorType op_type;

		OperatorNode() {
			type = Ty::OPERATOR_OVERRIDE;
		};

		~OperatorNode() {};
	};

	// this gets it's own node.
	struct TernaryOperator : public Node {
		Node* expr = nullptr;

		Node* btrue = nullptr;
		Node* bfalse = nullptr;

		TernaryOperator() {
			type = Ty::TERNARY;
		};

		~TernaryOperator() {};
	};

	struct AttributeNode : public Node {
		Node* node;

		struct AttributeArgument {
			std::string name;
			std::map<std::string, std::string> arguments;
		};

		std::vector<AttributeArgument> attributes;

		AttributeNode() {
			type = Ty::ATTRIBUTE;
		};

		~AttributeNode() {};
	};

	struct ReturnNode : public Node {
		Node* value;
		FunctionNode* parent;

		ReturnNode() {
			type = Ty::RETURN;
		};

		~ReturnNode() {};
	};

	struct IdentifierNode : public Node {
		std::string name;

		IdentifierNode(std::string p_name) {
			name = p_name;
			type = Ty::IDENTIFIER;
		}

		IdentifierNode(Token p_identifier_tk) {
			name = p_identifier_tk.to_string();
			type = Ty::IDENTIFIER;
			pos = std::pair<int, int>(p_identifier_tk.line, p_identifier_tk.col);
		}

		~IdentifierNode() {};
	};

	struct IndexNode : public Node {
		Node* base;
		IdentifierNode* member;

		IndexNode() {
			type = Ty::INDEX;
		};

		~IndexNode() {};
	};

	struct CallNode : public Node {
		std::vector<Node*> arguments;
		std::string method;

		std::vector<Type*> generics;

		Node* base = nullptr;
		bool is_static_call = false;

		CallNode() {
			type = Ty::CALL;
		};

		~CallNode() {};
	};

	struct NewNode : public Node {
		std::vector<Node*> arguments;
		std::string method;

		NewNode() {
			type = Ty::NEW_CALL;
		};

		NewNode(CallNode* p_node) {
			type = Ty::NEW_CALL;
			arguments = p_node->arguments;
			method = p_node->method;
		};

	};

	struct ImportNode : public Node {
		std::string path;

		ImportNode() {
			type = Ty::IMPORT;
		};

		~ImportNode() {};
	};

	struct VarNode : public Node {
		Node* value;

		std::string name;
		Type* vtype;

		bool isPublic = false;
		bool isGlobal = false;

		VarNode() {
			type = Ty::VAR;
		};

		~VarNode() {};
	};

	struct ClassNode : public Node {
		std::string name;

		std::vector<VarNode*> vars;
		std::vector<FunctionNode*> functions;
		std::vector<OperatorNode*> operators;

		// TODO: generics
		std::vector<Type*> generics;
		std::vector<Type*> parents;

		// note: only used as context on the generator
		llvm::StructType* _llvm_struct = nullptr;

		ClassNode() {
			type = Ty::CLASS;
		};

		~ClassNode() {};
	};

	struct ConstantValue : public Node {
		std::string value;
		TokenType const_type; // Const values' type

		ConstantValue(TokenType _const_type, std::string _value) {
			const_type = _const_type;
			value = _value;
			type = Ty::CONST_VALUE;
		};

		~ConstantValue() {};
	};

	struct BinaryOp : public Node {

		enum OpType {
			OP_EQ,
			OP_EQEQ,
			OP_PLUS,
			OP_PLUSEQ,
			OP_MINUS,
			OP_MINUSEQ,
			OP_MUL,
			OP_MULEQ,
			OP_DIV,
			OP_DIVEQ,
			OP_MOD,
			OP_MOD_EQ,
			OP_LT,
			OP_LTEQ,
			OP_GT,
			OP_GTEQ,
			OP_AND,
			OP_OR,
			OP_NOT,
			OP_NOTEQ,

			OP_BIT_NOT,
			OP_BIT_LSHIFT,
			OP_BIT_LSHIFT_EQ,
			OP_BIT_RSHIFT,
			OP_BIT_RSHIFT_EQ,
			OP_BIT_OR,
			OP_BIT_OR_EQ,
			OP_BIT_AND,
			OP_BIT_AND_EQ,
			OP_BIT_XOR,
			OP_BIT_XOR_EQ,

			OP_POSITIVE,
			OP_NEGATIVE,

			NONE,
		};

		Node* left;
		Node* right;

		bool unary = false;
		OpType op_type = OpType::NONE;

		static bool is_assignment(BinaryOp* p_node) {
			OpType p_op_type = p_node->op_type;

			return
				p_op_type == OpType::OP_EQ 	   	      ||
				p_op_type == OpType::OP_PLUSEQ        ||
				p_op_type == OpType::OP_MINUSEQ       ||
				p_op_type == OpType::OP_MULEQ    	  ||
				p_op_type == OpType::OP_DIVEQ         ||
				p_op_type == OpType::OP_MOD_EQ        ||
				p_op_type == OpType::OP_BIT_LSHIFT_EQ ||
				p_op_type == OpType::OP_BIT_RSHIFT_EQ ||
				p_op_type == OpType::OP_BIT_OR_EQ     ||
				p_op_type == OpType::OP_BIT_AND_EQ    ||
				p_op_type == OpType::OP_BIT_XOR_EQ;
		}

		std::string to_string() {
			switch (op_type)
			{

                case OpType::OP_GT:              return ">";
                case OpType::OP_LT:              return "<";
                case OpType::OP_GTEQ:            return ">=";
                case OpType::OP_EQEQ:            return "==";
                case OpType::OP_LTEQ:            return "<=";
                case OpType::OP_NOTEQ:           return "!=";

                // Mathematical symbols
                case OpType::OP_MOD:             return "%";
                case OpType::OP_DIV:             return "/";
                case OpType::OP_MUL:             return "*";
				case OpType::OP_POSITIVE:
                case OpType::OP_PLUS:            return "+";
                case OpType::OP_MINUS:           return "-";
                case OpType::OP_NEGATIVE:
                case OpType::OP_MULEQ:           return "*=";
                case OpType::OP_DIVEQ:           return "/=";
                case OpType::OP_PLUSEQ:          return "+=";
                case OpType::OP_MOD_EQ:          return "%=";
                case OpType::OP_MINUSEQ:         return "-=";

                // Asignment
                case OpType::OP_EQ:              return "=";
                case OpType::OP_OR:              return "||";
                case OpType::OP_AND:             return "&&";
                case OpType::OP_NOT:             return "!";

                // Bitwise operations
                case OpType::OP_BIT_OR:          return "|";
                case OpType::OP_BIT_NOT:         return "~";
                case OpType::OP_BIT_AND:         return "&";
                case OpType::OP_BIT_XOR:         return "^";
                case OpType::OP_BIT_OR_EQ:       return "|=";
                case OpType::OP_BIT_LSHIFT:      return "<<";
                case OpType::OP_BIT_RSHIFT:      return ">>";
                case OpType::OP_BIT_AND_EQ:      return "&=";
                case OpType::OP_BIT_XOR_EQ:      return "^=";
                case OpType::OP_BIT_LSHIFT_EQ:   return "<<=";
                case OpType::OP_BIT_RSHIFT_EQ:   return ">>=";

				case OpType::NONE:
					return "<NONE>";
			}

			return "<BUG>";
		}

		BinaryOp(OpType _op_type) {
			type = Ty::OPERATOR;
			op_type = _op_type;
			unary = (
				op_type == OpType::OP_NOT      ||
				op_type == OpType::OP_BIT_NOT  ||
				op_type == OpType::OP_POSITIVE ||
				op_type == OpType::OP_NEGATIVE );
		};

		~BinaryOp() {};
	};
}

#endif // __SNOWBALL_NODE_H_
