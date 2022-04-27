
#include "logger.h"
#include <string>

namespace snowball {
    void Logger::log(std::string message)     { printf("%s\n", message.c_str());                           }
    void Logger::rlog(std::string message)    { printf("%s\n", message.c_str());                           }
    void Logger::elog(std::string message)    { fprintf( stderr, "%s\n", message.c_str());                 }

    void Logger::info(std::string message)    { printf("%sinfo%s: %s\n", BBLU, RESET, message.c_str());    }
    void Logger::help(std::string message)    { printf("%shelp%s: %s\n", BGRN, RESET, message.c_str());    }
    void Logger::error(std::string message)   { printf("%serror%s: %s\n", BRED, RESET, message.c_str());   }
    void Logger::warning(std::string message) { printf("%swarning%s: %s\n", BYEL, RESET, message.c_str()); }
    void Logger::verbose(std::string message) { printf("%sverbose%s: %s\n", BMAG, RESET, message.c_str()); }
    void Logger::success(std::string message) { printf("%ssuccess%s: %s\n", BGRN, RESET, message.c_str()); }
}
