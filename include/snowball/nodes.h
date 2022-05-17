
#include <string>
#include <stdint.h>

#ifndef __SNOWBALL_NODE_H_
#define __SNOWBALL_NODE_H_

namespace snowball {
    struct Node {
        enum class Type {
			UNKNOWN,

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

            _NODE_MAX_,
		};
        Type type = Type::UNKNOWN;
        uint32_t width = 1; // width of the node ^^^^ (dbg).
        // Node* parent_node; // TODO
    };

	struct FunctionNode : public Node {
		std::string name;
		Type type = Type::FUNCTION;

		FunctionNode() {};
		~FunctionNode() {};
	};

	struct VarNode : public Node {
		std::string name;
		Type type = Type::VAR;

		Node expr;

		VarNode() {};
		~VarNode() {};
	};
}

#endif // __SNOWBALL_NODE_H_
