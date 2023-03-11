
#include "logger.h"

#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#define _SN_LOGGER_BAR_WIDTH 70

namespace snowball {
void Logger::log(std::string message) {
    printf("%s\n", message.c_str());
    fflush(stdout);
}
void Logger::rlog(std::string message) {
    printf("%s", message.c_str());
    fflush(stdout);
}
void Logger::elog(std::string message) {
    fprintf(stderr, "%s\n", message.c_str());
    fflush(stderr);
}

void Logger::info(std::string message) {
    printf("%sinfo%s: %s\n", BGRN, RESET, message.c_str());
}
void Logger::help(std::string message) {
    printf("%shelp%s: %s\n", BGRN, RESET, message.c_str());
}
void Logger::error(std::string message) {
    printf("\n%serror%s: %s\n", BRED, RESET, message.c_str());
}
void Logger::warning(std::string message) {
    printf("%swarning%s: %s\n", BYEL, RESET, message.c_str());
}
void Logger::verbose(std::string message) {
    printf("%sverbose%s: %s\n", BMAG, RESET, message.c_str());
}
void Logger::success(std::string message) {
    printf("%ssuccess%s: %s\n", BGRN, RESET, message.c_str());
}

void Logger::message(std::string topic, std::string message) {
    std::cout << BGRN << std::setw(15) << std::fixed << topic << RESET << ' '
              << message << std::endl;
}

// status
void Logger::reset_status() {
    printf("\33[2K\r");
    fflush(stdout);
};
void Logger::compiling(std::string message) {
    printf("\33[2K\r%s      Compiling%s %s", BGRN, RESET, message.c_str());
    fflush(stdout);
};

std::string Logger::progress(float progress) {
    std::stringstream output;

    output << "[";
    int pos = _SN_LOGGER_BAR_WIDTH * progress;
    for (int i = 0; i < _SN_LOGGER_BAR_WIDTH; ++i) {
        if (i < pos)
            output << "=";
        else if (i == pos)
            output << ">";
        else
            output << " ";
    }
    output << "] " << int(progress * 100.0) << " %\r";
    output.flush();

    return output.str();
}

std::string FMT(const char *p_format, ...) {
    va_list argp;

    va_start(argp, p_format);

    static const unsigned int BUFFER_SIZE = VSNPRINTF_BUFF_SIZE;
    char buffer[BUFFER_SIZE + 1]; // +1 for the terminating character
    int len = vsnprintf(buffer, BUFFER_SIZE, p_format, argp);

    va_end(argp);

    if (len == 0) return std::string();

    return std::string(buffer);
}
} // namespace snowball
