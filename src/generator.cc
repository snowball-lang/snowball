
#include "snowball/generator.h"

namespace snowball {
    void Generator::generate() {
        std::vector<Node> nodes = _parser->nodes();

        for (auto node : nodes) {
            switch (node.type)
            {
            case Node::Type::VAR:
                printf("HELLO\n");
                break;

            default:
                break;
            }
        }
    }
}
