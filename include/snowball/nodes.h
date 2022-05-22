
#include <memory>
#include <string>
#include <stdint.h>

#include "token.h"

#ifndef __SNOWBALL_NODE_H_
#define __SNOWBALL_NODE_H_

namespace snowball {
    struct Node {
        enum class Type {
			UNKNOWN = -1,

			IMPORT,
			FILE,
			CLASS,
			ENUM,
			FUNCTION,
			BLOCK,
			IDENTIFIER,
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
			CONTROL_FLOW,
            SN_NODES_H,
		};

        Type type = Type::UNKNOWN;
        uint32_t width = 1; // width of the node ^^^^ (dbg).

        // Node* parent_node; // TODO

		Node() {};
		~Node() {};
    };

	struct FunctionNode : public Node {
		std::string name;

		FunctionNode() {
			type = Type::FUNCTION;
		};

		~FunctionNode() {};
	};

	struct VarNode : public Node {
		std::string name;
		Node expr;

		VarNode() {
			type = Type::VAR;
		};
		~VarNode() {};
	};

	struct ConstantValue : public Node {
		std::string value;
		TokenType const_type;

		ConstantValue(TokenType _const_type, std::string _value) : const_type(_const_type), value(_value) {
			type = Type::CONST_VALUE;
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
		};

		static bool is_assignment(OpType p_op_type) {
			return
				p_op_type == BinaryOp::OpType::OP_EQ 	   	    ||
				p_op_type == BinaryOp::OpType::OP_PLUSEQ   	    ||
				p_op_type == BinaryOp::OpType::OP_MINUSEQ  	    ||
				p_op_type == BinaryOp::OpType::OP_MULEQ    	    ||
				p_op_type == BinaryOp::OpType::OP_DIVEQ         ||
				p_op_type == BinaryOp::OpType::OP_MOD_EQ        ||
				p_op_type == BinaryOp::OpType::OP_BIT_LSHIFT_EQ ||
				p_op_type == BinaryOp::OpType::OP_BIT_RSHIFT_EQ ||
				p_op_type == BinaryOp::OpType::OP_BIT_OR_EQ     ||
				p_op_type == BinaryOp::OpType::OP_BIT_AND_EQ    ||
				p_op_type == BinaryOp::OpType::OP_BIT_XOR_EQ;
		}

		OpType op_type;

		std::unique_ptr<Node> lhs;
		std::unique_ptr<Node> rhs;

		BinaryOp(OpType _op_type) : op_type(_op_type) {
			type = Type::OPERATOR;
		};

		BinaryOp(OpType _op_type, std::unique_ptr<Node> _lhs, std::unique_ptr<Node> _rhs) : op_type(_op_type), lhs(std::move(_lhs)), rhs(std::move(_rhs)) {
			type = Type::OPERATOR;
		};

		~BinaryOp() {};
	};
}

#endif // __SNOWBALL_NODE_H_
