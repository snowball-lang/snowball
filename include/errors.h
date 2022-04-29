
#include "logger.h"
#include "source_info.h"

#include <string>
#include <exception>
#include <stdexcept>

#ifndef __SNOWBALL_ERRORS_H_
#define __SNOWBALL_ERRORS_H_

namespace snowball {
    enum Error {
        UNEXPECTED_EOF,

        BUG,
        TODO
    };

    const char* get_error(Error code);

    class SNError  {
        public:
            SNError(Error code, std::string err) { error = code; message = err; };
            SNError(Error code, const char* err) { error = code; message = std::string(err); };

            virtual void print_error() {
                Logger::error("SN error");
            };

            virtual ~SNError() {};

            Error error;
            std::string message;

    };

    class LexerError : public SNError {
        public:

            LexerError(Error code, std::string err, SourceInfo *&source_info) : SNError(code, err) {  };
            LexerError(Error code, const char* err, SourceInfo *&source_info) : SNError(code, err) {  };

            virtual void print_error() {
                Logger::error(message);
            };

            virtual ~LexerError() {};
    };
}

#endif // __SNOWBALL_ERRORS_H_

