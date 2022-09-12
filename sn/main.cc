
#include "snowball/snowball.h"
#include "snowball/constants.h"
#include "snowball/utils/utils.h"
#include "snowball/utils/mangle.h"

#include <string>
#include <vector>
#include <stdio.h>

#include <fstream>
#include <string.h>
#include <dirent.h>

#include <iostream>
#include <exception>
#include <stdexcept>

#include <filesystem>
#include <llvm/Support/FormattedStream.h>

using namespace snowball;
using namespace std::chrono;
using namespace snowball_utils;
namespace fs = std::filesystem;

int compile(std::string content, std::string filename, std::vector<std::string> arguments) {

    int result;
    bool test = std::find(arguments.begin(), arguments.end(), "-t") != arguments.end();
    bool JIT = std::find(arguments.begin(), arguments.end(), "-j") != arguments.end();
    bool object = std::find(arguments.begin(), arguments.end(), "-b") != arguments.end();
    auto output_param = std::find(arguments.begin(), arguments.end(), "-o");
    std::string output = _SNOWBALL_OUT_DEFAULT;
    if (output_param != arguments.end()) {
        output = *(++output_param);
    }

    Compiler* compiler = new Compiler(content, filename);
    try {
        compiler->initialize();

        if (test) {
            compiler->enable_tests();
        }

        compiler->compile(!test);

        if ((JIT || test) && !object) {
            result = compiler->execute();
        } else if (!JIT && !test && object) {
            compiler->emit_object(output, false);
        } else {
            compiler->emit_binary(output);
        }
    } catch(const SNError& error) {
        error.print_error();
    }

    // compiler->get_module()->print(llvm::outs(), nullptr);
    compiler->cleanup();
    return result;
}

int main(int argc, char** argv) {

    std::string filename;
    std::vector<std::string> arguments;

    for (int arg = 1; arg < argc; arg++) {
        if (strncmp(argv[arg], "-", 1) == 0) {
            arguments.push_back((const char*)(argv[arg]));
            continue;
        }

        if (filename.empty()) {
            filename = (const char*)(argv[arg]);
        } else {
            arguments.push_back((const char*)(argv[arg]));
        }
    }

    if (!filename.empty()) {

        if( std::filesystem::is_directory(filename) && std::find(arguments.begin(), arguments.end(), "-t") != arguments.end()) {
            struct dirent *entry;
            DIR *dp;

            dp = opendir(filename.c_str()); // We know it will exist

            int amount_of_errors = 0;
            auto start = high_resolution_clock::now();

            while ((entry = readdir(dp))) {
                if (endsWith(entry->d_name, ".test.sn")) {
                    std::string path = ((fs::path)filename) / entry->d_name;
                    std::ifstream file_content(path);
                    std::string content( (std::istreambuf_iterator<char>(file_content) ),
                        (std::istreambuf_iterator<char>()    ) );

                    int success = compile(content, path, arguments);
                    if (!success) {
                        amount_of_errors++;
                    }
                }
            }

            auto stop = high_resolution_clock::now();

            // Subtract stop and start time stamps and
            // cast it to required unit. Predefined units
            // are nanoseconds, microseconds, milliseconds,
            // seconds, minutes, hours. Use duration_cast()
            // function.
            auto duration = duration_cast<milliseconds>(stop - start);

            if (amount_of_errors > 0) {
                Logger::info(Logger::format("%s%i%s unit test(s) failed (executed in %s%ims%s)", BRED, amount_of_errors, RESET, BBLU, duration.count(), RESET));
            } else {
                Logger::info(Logger::format("\tUnit tests successfully executed in %s%ims%s", BBLU, duration.count(), RESET));
            }

            closedir(dp);
        } else {
            std::ifstream ifs(filename);
            if(ifs.fail()){
                SNError(Error::IO_ERROR, Logger::format("filename '%s' not found.", filename.c_str())).print_error();
                return EXIT_FAILURE;
            }

            std::string content( (std::istreambuf_iterator<char>(ifs) ),
                (std::istreambuf_iterator<char>()    ) );

            return compile(content, filename, arguments);
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

            Compiler* compiler = new Compiler(Logger::format("pub fn %s() -> Int {\n    %s\n    return 0\n}", _SNOWBALL_FUNCTION_ENTRY, line.c_str()), "<stdin>");
            try {
                compiler->initialize();

                compiler->compile();
                compiler->execute();
            } catch(const SNError& error) {
                printf("\n");
                error.print_error();
            }

            compiler->cleanup();
            free(compiler);
        }
    }

    return EXIT_SUCCESS;
}
