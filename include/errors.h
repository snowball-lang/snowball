
#include <string>
#include <exception>

#ifndef __SNOWBALL_ERRORS_H_
#define __SNOWBALL_ERRORS_H_

namespace snowball {
    enum Error {

        BUG,
        TODO
    };

    const char* get_error(Error code);

    class SNError : public std::exception {
        SNError(Error code, std::string err);
        SNError(Error code, const char* err);

        std::string get_error();
        std::string get_message();

        void print_error();

        ~SNError() {};
    };
}

#endif // __SNOWBALL_ERRORS_H_

