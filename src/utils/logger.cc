
#include "utils/logger.h"

#include <cstdarg>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#define _SN_LOGGER_BAR_WIDTH 20

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

void Logger::info(std::string message) { printf("%s[info]%s: %s\n", BGRN, RESET, message.c_str()); }
void Logger::help(std::string message) { printf("%s[help]%s: %s\n", BGRN, RESET, message.c_str()); }
void Logger::error(std::string message) { printf("%s[error]%s: %s\n", BRED, RESET, message.c_str()); }
void Logger::warning(std::string message) { printf("%s[warning]%s: %s\n", BYEL, RESET, message.c_str()); }
void Logger::verbose(std::string message) { printf("%s[verbose]%s: %s\n", BMAG, RESET, message.c_str()); }
void Logger::success(std::string message) { printf("%s[success]%s: %s\n", BGRN, RESET, message.c_str()); }

void Logger::message(std::string topic, std::string message) {
  std::cout << BGRN << std::setw(15) << std::fixed << topic << RESET << ' ' << message << std::endl;
}

void Logger::raw_message(std::string topic, std::string message) {
  std::cout << BGRN << std::setw(15) << std::fixed << topic << RESET << ' ' << message;
  fflush(stdout);
}

// status
void Logger::reset_status() {
  printf("\33[2K\r");
  fflush(stdout);
};
void Logger::compiling(std::string message, std::string status) {
  std::cout << BCYN << std::setw(15) << status << RESET << ' ' << message;
  fflush(stdout);
};

std::string Logger::progress(float progress, std::string message) {
  std::stringstream output;
  reset_status();

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
  output << "] " << int(progress * 100.0);
  output << "%";
  if (!message.empty()) output << " " << message;
  output << "\r";
  output.flush();

  return output.str();
}

std::string FMT(const char* p_format, ...) {
  va_list argp;

  va_start(argp, p_format);
  size_t result_size = vsnprintf(NULL, 0, p_format, argp);

  char buffer[result_size + 1]; // +1 for the terminating character
  va_end(argp);
  va_start(argp, p_format);
  int len = vsprintf(buffer, p_format, argp);
  va_end(argp);
  return std::string(buffer, len);
}
} // namespace snowball
