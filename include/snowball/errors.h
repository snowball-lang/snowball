
#include "logger.h"
#include "colors.h"
#include "dbg_info.h"

#include <string>
#include <exception>
#include <stdexcept>

#ifndef __SNOWBALL_ERRORS_H_
#define __SNOWBALL_ERRORS_H_

namespace snowball {
    enum Error {
        SYNTAX_ERROR,
        UNEXPECTED_EOF,

        BUG,
        TODO
    };

    const char* get_error(Error code);

    class SNError  {
        public:
            SNError(Error code, std::string err) { error = code; message = err; };

            virtual void print_error() const {
                Logger::error("SN error");
            };

            virtual ~SNError() {};

            Error error;
            std::string message;

    };

    class LexerError : public SNError {
        public:

            LexerError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info)
                : SNError(code, err) {
                    cb_dbg_info = p_cb_dbg_info;
                };

            virtual void print_error() const {
                Logger::error(Logger::format("(%s%s%s) %s%s%s", RED, get_error(error), RESET, BOLD, message.c_str(), RESET));
                Logger::elog(Logger::format("  %s-->%s %s:[%i:%i]", BBLU, RESET,
                    cb_dbg_info->source_info->get_path().c_str(),
                    cb_dbg_info->line,
                    cb_dbg_info->pos.second,
                    WHT));
                Logger::elog(Logger::format("%s   |%s", BBLU, RESET));

                if (cb_dbg_info->line - 1 >= 1) // first line may not be available to log
                Logger::elog(Logger::format("%s%2i | %s%s",           BBLU, cb_dbg_info->line - 1, RESET, cb_dbg_info->line_before.c_str()));
                Logger::elog(Logger::format("%s%2i | %s%s/%s %s\n   %s|%s %s|_%s%s%s%s", BBLU, cb_dbg_info->line, RESET, BRED, RESET, cb_dbg_info->line_str.c_str(), BBLU, RESET, BRED, RESET, BRED, cb_dbg_info->get_pos_str().c_str(), RESET));
                Logger::elog(Logger::format("%s%2i | %s%s",           BBLU, cb_dbg_info->line + 1, RESET,  cb_dbg_info->line_after.c_str()));
            };

            virtual ~LexerError() {};

        private:
            DBGSourceInfo *cb_dbg_info;
    };

    class ParserError : public SNError {
    public:

        ParserError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info)
            : SNError(code, err) {
                cb_dbg_info = p_cb_dbg_info;
            };

        virtual void print_error() const {
            Logger::error(Logger::format("(%s%s%s) %s%s%s", RED, get_error(error), RESET, BOLD, message.c_str(), RESET));
            Logger::elog(Logger::format("  %s-->%s %s:[%i:%i]", BBLU, RESET,
                cb_dbg_info->source_info->get_path().c_str(),
                cb_dbg_info->line,
                cb_dbg_info->pos.second,
                WHT));
            Logger::elog(Logger::format("%s   |%s", BBLU, RESET));

            if (cb_dbg_info->line - 1 >= 1) // first line may not be available to log
            Logger::elog(Logger::format("%s%2i | %s%s",           BBLU, cb_dbg_info->line - 1, RESET, cb_dbg_info->line_before.c_str()));
            Logger::elog(Logger::format("%s%2i | %s%s/%s %s\n   %s|%s %s|_%s%s%s%s", BBLU, cb_dbg_info->line, RESET, BRED, RESET, cb_dbg_info->line_str.c_str(), BBLU, RESET, BRED, RESET, BRED, cb_dbg_info->get_pos_str().c_str(), RESET));
            Logger::elog(Logger::format("%s%2i | %s%s",           BBLU, cb_dbg_info->line + 1, RESET,  cb_dbg_info->line_after.c_str()));
        };

        virtual ~ParserError() {};

    private:
        DBGSourceInfo *cb_dbg_info;
    };
}

#endif // __SNOWBALL_ERRORS_H_

