
#include "exec/cli.h"
#include "snowball/logger.h"

#include <iostream>
#include <fstream>
#include <sstream>


#ifndef __SNOWBALL_EXEC_INIT_CMD_H_
#define __SNOWBALL_EXEC_INIT_CMD_H_

#define STRINGIFY(...) #__VA_ARGS__

#define LIBRARY_ENTRY "src/lib.sn"
#define LIBRARY_MAIN  \
    "import Assertion\n\n" \
    "pub fn my_export() String {\n" \
    "    return \"Hello, World\"\n" \
    "}\n\n"\
    /* TODO: add #[cfg(test)] */ \
    "\nmod tests {\n" \
    "   #[test]\n" \
    "    fn test_my_lib() {\n" \
            /* TODO: implement this in the actual language */ \
    "        Assertion::assert(supper::my_export() == \"Hello, World\")\n" \
    "    }\n" \
    "}"


#define EXECUTABLE_ENTRY "src/main.sn"
#define EXECUTABLE_MAIN  \
    "import System\n" \
    \
    "\nfn main() Void {\n" \
    "   System.println(\"Hello, World\")\n" \
    "}"


#define CONFIGURATION_FILE "sn.toml"

namespace snowball {
    namespace exec {
        namespace commands {

            void init_create_cfg(bool yes) {
                std::ofstream outfile (CONFIGURATION_FILE);

                std::string name = "amazing-snowball-project";
                std::string main = "src/main.sn";
                std::string version = "1.0.0";

                // TODO: ask questions if p_opts.yes is false
                std::string toml_result;
                std::stringstream toml(toml_result);

                toml << "\n[package]";
                toml << Logger::format("\nname = \"%s\"", name.c_str());
                toml << Logger::format("\nmain = \"%s\"", main.c_str());
                toml << Logger::format("\nversion = \"%s\"", version.c_str());

                outfile << toml.str() << std::endl;
                outfile.close();
            }

            // TODO: Output messages
            int init(exec::Options::InitOptions p_opts) {

                if (p_opts.cfg) {
                    init_create_cfg(p_opts.yes);
                    return 0;
                } else if (p_opts.lib) {

                    Logger::warning("Library example is not yet supported by current snowball!");
                    if (!fs::exists("src")) fs::create_directory("src");

                    if (!p_opts.skip_cfg)
                        init_create_cfg(p_opts.yes);

                    std::ofstream outfile (LIBRARY_ENTRY);
                    outfile << LIBRARY_MAIN << std::endl;
                    outfile.close();
                } else {

                    if (!fs::exists("src")) fs::create_directory("src");
                    if (!p_opts.skip_cfg)
                        init_create_cfg(p_opts.yes);

                    std::ofstream outfile (EXECUTABLE_ENTRY);
                    outfile << EXECUTABLE_MAIN << std::endl;
                    outfile.close();
                }
            }
        }
    }
}

#undef LIBRARY_MAIN
#undef LIBRARY_ENTRY

#undef EXECUTABLE_MAIN
#undef EXECUTABLE_ENTRY

#undef CONFIGURATION_FILE

#undef STRINGIFY

#endif // __SNOWBALL_EXEC_INIT_CMD_H_
