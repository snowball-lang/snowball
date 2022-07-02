
#include "snowball/snowball.h"
#include "snowball/constants.h"


#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include <iostream>
#include <exception>
#include <stdexcept>

#define COMPILER ""
#define LICENSE ""

using namespace snowball;

int main(int argc, char** argv) {

    std::string filename;
    std::vector<std::string> arguments;

    for (int arg = 1; arg < argc; arg++) {
        if (strncmp(argv[arg], "-", 1) == 0) {
            arguments.push_back((const char*)(argv[arg]));
            continue;
        }

        filename = (const char*)(argv[arg]);
        break;
    }

    if (!filename.empty()) {
        std::ifstream ifs(filename);
        if(ifs.fail()){
            SNError(Error::IO_ERROR, Logger::format("filename '%s' not found.", filename.c_str())).print_error();
            return EXIT_FAILURE;
        }

        std::string content( (std::istreambuf_iterator<char>(ifs) ),
                            (std::istreambuf_iterator<char>()    ) );

        try {
            Compiler* compiler = new Compiler(content, filename);
            compiler->initialize();

            compiler->compile();
        } catch(const SNError& error) {
            error.print_error();
        }
    } else {
        Logger::log(_SNOWBALL_COMPILER_ENTRY);
        int line_num = 1;
        std::string lines;
        while (true) {
            Logger::rlog(Logger::format(" %i %s|%s%s ", line_num, BBLU, RESET, BOLD));
            std::string line;
            std::getline( std::cin, line );

            line_num += 1;
            lines += lines;

            try {
                Compiler* compiler = new Compiler(Logger::format("func main {\n\t%s\n}", line.c_str()), "<stdin>");
                compiler->initialize();

                compiler->compile();
            } catch(const SNError& error) {
                printf("\n");
                error.print_error();
            }
        }
    }

    return EXIT_SUCCESS;
}
