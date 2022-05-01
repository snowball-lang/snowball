
#include "snowball.h"
#include <string>
#include <exception>
#include <stdexcept>
using namespace snowball;

int main(int argc, char** argv) {

    // TODO: get code from FILE or REPL
    std::string code = "/*\nhe";

    try {
        Compiler* compiler = new Compiler(code, "<stdin>");
        compiler->initialize();

        compiler->compile();
    } catch(const SNError& error) {
        error.print_error();
    }

    return EXIT_SUCCESS;
}
