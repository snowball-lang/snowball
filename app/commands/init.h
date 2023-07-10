
#include "app/cli.h"
#include "logger.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std::chrono;

#ifndef __SNOWBALL_EXEC_INIT_CMD_H_
#define __SNOWBALL_EXEC_INIT_CMD_H_

#define STRINGIFY(...) #__VA_ARGS__

#define LIBRARY_ENTRY "src/lib.sn"
#define LIBRARY_MAIN                                                                               \
    "use Core::Assertion\n\n"                                                                      \
    "pub fn my_export() String {\n"                                                                \
    "    return \"Hello, World\"\n"                                                                \
    "}\n\n" /* TODO: add #[cfg(test)] */                                                           \
    "\nnamespace tests {\n"                                                                        \
    "   #[test]\n"                                                                                 \
    "    fn test_my_lib() {\n" /* TODO: implement this in the actual                               \
                                * language                                                         \
                                */                                                                 \
    "        Assertion::assert(my_export() == \"Hello, World\")\n"                                 \
    "    }\n"                                                                                      \
    "}"

#define EXECUTABLE_ENTRY "src/main.sn"
#define EXECUTABLE_MAIN                                                                            \
    "use Core::System\n"                                                                           \
                                                                                                   \
    "\npub fn main() {\n"                                                                          \
    "   System::println(\"Hello, World\")\n"                                                       \
    "}"

#define CONFIGURATION_FILE "sn.toml"

namespace snowball {
namespace app {
namespace commands {

void init_create_cfg(bool yes, std::string entry) {
    std::ofstream outfile(CONFIGURATION_FILE);

    std::string name = "amazing-snowball-project";
    std::string version = "1.0.0";

    // TODO: ask questions if p_opts.yes is false
    std::string toml_result;
    std::stringstream toml(toml_result);

    toml << "\n[package]";
    toml << FMT("\nname = \"%s\"", name.c_str());
    toml << FMT("\nmain = \"%s\"", entry.c_str());
    toml << FMT("\nversion = \"%s\"", version.c_str());

    outfile << toml.str() << std::endl;
    outfile.close();

    Logger::message("Configuration", FMT("created configuration file (%s)", CONFIGURATION_FILE));
}

// TODO: Output messages
int init(app::Options::InitOptions p_opts) {
    auto start = high_resolution_clock::now();

    if (p_opts.cfg) {
        init_create_cfg(p_opts.yes, EXECUTABLE_ENTRY);
        return 0;
    } else if (p_opts.lib) {
        Logger::message("Initalizing",
                        FMT("creating snowball project [library]", CONFIGURATION_FILE));

        Logger::warning("Library example is not yet supported by "
                        "current snowball!");
        if (!fs::exists("src")) fs::create_directory("src");

        if (!p_opts.skip_cfg) init_create_cfg(p_opts.yes, LIBRARY_ENTRY);

        std::ofstream outfile(LIBRARY_ENTRY);
        outfile << LIBRARY_MAIN << std::endl;
        outfile.close();
    } else {
        Logger::message("Initalizing",
                        FMT("creating snowball project [executable]", CONFIGURATION_FILE));

        if (!fs::exists("src")) fs::create_directory("src");
        if (!p_opts.skip_cfg) init_create_cfg(p_opts.yes, EXECUTABLE_ENTRY);

        std::ofstream outfile(EXECUTABLE_ENTRY);
        outfile << EXECUTABLE_MAIN << std::endl;
        outfile.close();
    }

    auto stop = high_resolution_clock::now();

    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<milliseconds>(stop - start).count();

    Logger::message("Finished", FMT("snowball project in %ims 🐱", duration));

    Logger::rlog("\n");
    Logger::info("Execute `snowball help` to get a manual about "
                 "the project.");

    return 0;
}
} // namespace commands
} // namespace app
} // namespace snowball

#undef LIBRARY_MAIN
#undef LIBRARY_ENTRY

#undef EXECUTABLE_MAIN
#undef EXECUTABLE_ENTRY

#undef CONFIGURATION_FILE

#undef STRINGIFY

#endif // __SNOWBALL_EXEC_INIT_CMD_H_
