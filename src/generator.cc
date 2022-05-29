
#include "snowball/nodes.h"
#include "snowball/errors.h"
#include "snowball/generator.h"

#include "llvm/IR/Type.h"

namespace snowball {
    void Generator::generate() {
        std::vector<Node> nodes = _parser->nodes();

        for (auto node : nodes) {
            switch (node.type)
            {
                case Node::Type::VAR: {
                    generate_variable(node);
                    break;
                };

                default:
                    DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, node.pos, node.width);
                    Warning warn = Warning(Logger::format("Node with type %s%i%s%s is not yet supported", BCYN, node.type, RESET, BOLD), dbg_info);
                    warn.print_error();
                    break;
            }
        }
    }

    void Generator::generate_variable(Node p_node) {
        Node expr = p_node.exprs.at(0);

        // TODO: reference -> https://github.com/lijiansong/clang-llvm-tutorial/blob/master/kaleidoscope/functional_programming_language/functional.cpp#L975
        // const alloca = _builder.CreateAlloca(
        //     getLLVMType(type, this.generator),
        //     nullptr,
        //     p_node.name
        // );

        // _builder.createStore(
        //     initializer,
        //     alloca as llvm.Value,
        //     undefined
        // );
    }
}
