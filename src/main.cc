
#include "snowball.h"
#include <string>

using namespace snowball;

int main(int argc, char** argv) {

    // TODO: get code from FILE or REPL
    std::string code = "";

    Compiler* compiler = new Compiler(code, "<stdin>");
    compiler->initialize();

    compiler->compile();

    return EXIT_SUCCESS;
}
