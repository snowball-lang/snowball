
#include "snowball/types.h"
#include "snowball/nodes.h"
#include "snowball/token.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>

namespace snowball {
    void Generator::generate() {
        std::vector<Node> nodes = _parser->nodes();

        for (auto node : nodes) {
            switch (node.type)
            {
                case Node::Type::CONST_VALUE: {
                    generate_cont_value(node);
                    break;
                }

                default:
                    DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, node.pos, node.width);
                    Warning warn = Warning(Logger::format("Node with type %s%i%s%s is not yet supported", BCYN, node.type, RESET, BOLD), dbg_info);
                    warn.print_error();
                    break;
            }
        }
    }

    llvm::Value* Generator::generate_cont_value(Node p_node) {
        switch (p_node.const_type)
        {
            case TokenType::VALUE_NUMBER: {
                llvm::Type * i64 = get_llvm_type_from_sn_type(BuildinTypes::NUMBER, _builder);

                llvm::Constant * num = llvm::ConstantInt::get(i64, (uint64_t)std::stoi(p_node.value));
                return _builder.CreateCall(_buildin_types.sn_number_class, num);
            }

            default:
                throw SNError(Error::TODO, Logger::format("Const Value with type %s%i%s%s is not yet supported", BCYN, p_node.const_type, RESET, BOLD));
        }
    }
}
