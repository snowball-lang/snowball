
#include <memory>
#include <string>
#include <stdint.h>

#include "token.h"
#include "llvm/IR/Value.h"

#ifndef __SNOWBALL_NODE_H_
#define __SNOWBALL_NODE_H_

namespace snowball {

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

    typedef struct Node {
        enum class Type {
			UNKNOWN = -1,

			IMPORT,
			FILE,
			CLASS,
			ENUM,
			FUNCTION,
			BLOCK,
			IDENTIFIER,
			ARGUMENT,
			VAR,
			CONST,
			CONST_VALUE, // evaluvated to compile time constants ex: "str", 3.14, Array(1, 2), ...
			ARRAY,       // literal array ex: [1, 2, [3]]
			MAP,         // literal map   ex: { "key":"value", 1:[2, 3] }
			THIS,
			SUPER,
			CALL,
			INDEX,
			MAPPED_INDEX,
			OPERATOR,

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

        Type type = Type::UNKNOWN;

		std::pair<int, int> pos;
        uint32_t width = 1; // width of the node ^^^^ (dbg).

		virtual ~Node() = default;
    } Node;

	struct BlockNode : public Node {
		std::vector<Node*> exprs;

		BlockNode() {
			type = Type::BLOCK;
		};

		~BlockNode() {};
	};

	struct ArgumentNode : public Node {
		std::string name;
		std::string type_name;

		ArgumentNode(std::string p_name, std::string p_type) {
			// todo: default values, infinite args, etc...
			name = p_name;
			type_name = p_type;
			type = Type::ARGUMENT;
		};

		~ArgumentNode() {};
	};

	struct FunctionNode : public Node {
		BlockNode* body;

		std::string name;
		std::string return_type;
		std::vector<ArgumentNode *> arguments;

		bool hasReturn = false;
		bool isTopLevel = false;

		FunctionNode() {
			type = Type::FUNCTION;
		};

		~FunctionNode() {};
	};

	struct ReturnNode : public Node {
		Node* value;
		FunctionNode* parent;

		ReturnNode() {
			type = Type::RETURN;
		};

		~ReturnNode() {};
	};

	struct IdentifierNode : public Node {
		std::string name;

		IdentifierNode(Token p_identifier_tk) {
			name = p_identifier_tk.to_string();
			type = Type::IDENTIFIER;
			pos = std::pair<int, int>(p_identifier_tk.line, p_identifier_tk.col);
		}

		~IdentifierNode() {};
	};

	struct CallNode : public Node {
		std::vector<Node*> arguments;
		std::string method;
		Node* base = nullptr;

		CallNode() {
			type = Type::CALL;
		};

		~CallNode() {};
	};

	struct TestingNode : public Node {

	};

	struct VarNode : public Node {
		Node* value;
		std::string name;
		bool isGlobal = false;

		VarNode() {
			type = Type::VAR;
		};

		~VarNode() {};
	};

	struct ConstantValue : public Node {
		std::string value;
		TokenType const_type; // Const values' type

		ConstantValue(TokenType _const_type, std::string _value) {
			const_type = _const_type;
			value = _value;
			type = Type::CONST_VALUE;
		};

		~ConstantValue() {};
	};

	struct BinaryOp : public Node {

		Node* left;
		Node* right;
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

		BinaryOp(OpType _op_type) {
			type = Type::OPERATOR;
			op_type = _op_type;
		};

		~BinaryOp() {};
	};
}

#endif // __SNOWBALL_NODE_H_
