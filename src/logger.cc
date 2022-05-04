
#include "snowball/logger.h"

#include <string>
#include <cstdarg>

#define VSNPRINTF_BUFF_SIZE 8192

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

    std::string Logger::format(const char* p_format, ...) {
        va_list argp;

        va_start(argp, p_format);

        static const unsigned int BUFFER_SIZE = VSNPRINTF_BUFF_SIZE;
        char buffer[BUFFER_SIZE + 1]; // +1 for the terminating character
        int len = vsnprintf(buffer, BUFFER_SIZE, p_format, argp);

        va_end(argp);

        if (len == 0) return std::string();

        return std::string(buffer);
    }
}
