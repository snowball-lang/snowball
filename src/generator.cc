
#include "snowball/errors.h"
#include "snowball/generator.h"

namespace snowball {
    void Generator::generate() {
        std::vector<Node> nodes = _parser->nodes();

        for (auto node : nodes) {
            switch (node.type)
            {
                // case Node::Type::VAR:
                //     printf("HELLO\n");
                //     break;

                default:
                    DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, node.pos, node.width);
                    Warning warn = Warning(Logger::format("Node with type %s%i%s%s is not yet supported", BCYN, node.type, RESET, BOLD), dbg_info);
                    warn.print_error();
                    break;
            }
        }
    }
}
