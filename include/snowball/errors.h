
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
        IO_ERROR,
        TYPE_ERROR,
        SYNTAX_ERROR,
        UNDEFINED_VARIABLE,
        UNEXPECTED_EOF,
        WARNING,
        VARIABLE_ERROR,
        CONFIGURATION_ERROR,
        ARGUMENT_ERROR,
        FUNCTION_RET_ERR,
        COMPILER_ERROR, // note: not the same as "compile time error"

        LLVM_INTERNAL,

        BUG,
        TODO
    };

    const char* get_error(Error code);

    class SNError  {
        public:
            SNError(Error code, std::string err) { error = code; message = err; };

            virtual void print_error() const {
                Logger::error(Logger::format("(%s%s%s) %s%s%s", RED, get_error(error), RESET, BOLD, message.c_str(), RESET));
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
                Logger::elog(Logger::format("%s     |%s", BBLK, RESET));

                if (cb_dbg_info->line - 1 >= 1) // first line may not be available to log
                Logger::elog(Logger::format("%s  %2i | %s%s",           BBLK, cb_dbg_info->line - 1, RESET, cb_dbg_info->line_before.c_str()));
                Logger::elog(Logger::format(" %s>%s%2i | %s %s\n   %s  |%s  %s%s%s", BRED, BBLK, cb_dbg_info->line, RESET, cb_dbg_info->line_str.c_str(), BBLK, RESET, BRED, cb_dbg_info->get_pos_str().c_str(), RESET));
                Logger::elog(Logger::format("%s  %2i | %s%s",           BBLK, cb_dbg_info->line + 1, RESET,  cb_dbg_info->line_after.c_str()));

                Logger::elog(Logger::format("\n  %sat %s%s%s:%i:%i%s", BBLK, BBLU,
                    cb_dbg_info->source_info->get_path().c_str(),
                    BBLK,
                    cb_dbg_info->line,
                    cb_dbg_info->pos.second,
                RESET));
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
            if (cb_dbg_info->line - 1 >= 1) // first line may not be available to log
            Logger::elog(Logger::format("%s  %2i | %s%s",           BBLK, cb_dbg_info->line - 1, RESET, cb_dbg_info->line_before.c_str()));
            Logger::elog(Logger::format(" %s>%s%2i | %s %s\n   %s  |%s  %s%s%s", BRED, BBLK, cb_dbg_info->line, RESET, cb_dbg_info->line_str.c_str(), BBLK, RESET, BRED, cb_dbg_info->get_pos_str().c_str(), RESET));
            Logger::elog(Logger::format("%s  %2i | %s%s",           BBLK, cb_dbg_info->line + 1, RESET,  cb_dbg_info->line_after.c_str()));

            Logger::elog(Logger::format("\n  %sat %s%s%s:%i:%i%s", BBLK, BBLU,
                cb_dbg_info->source_info->get_path().c_str(),
                BBLK,
                cb_dbg_info->line,
                cb_dbg_info->pos.second,
            RESET));
        };

        virtual ~ParserError() {};

    private:
        DBGSourceInfo *cb_dbg_info;
    };

    class Warning : public SNError {
    public:

        Warning(std::string warn, DBGSourceInfo* p_cb_dbg_info)
            : SNError(Error::WARNING, warn) {
                cb_dbg_info = p_cb_dbg_info;
            };

        virtual void print_error() const {
            Logger::warning(Logger::format("%s%s%s", BOLD, message.c_str(), RESET));
            Logger::elog(Logger::format("  %s-->%s %s:[%i:%i]", BBLU, RESET,
                cb_dbg_info->source_info->get_path().c_str(),
                cb_dbg_info->line,
                cb_dbg_info->pos.second,
                WHT));
            Logger::elog(Logger::format("%s   |%s", BBLU, RESET));

            if (cb_dbg_info->line - 1 >= 1) // first line may not be available to log
            Logger::elog(Logger::format("%s%2i | %s%s",           BBLU, cb_dbg_info->line - 1, RESET, cb_dbg_info->line_before.c_str()));
            Logger::elog(Logger::format("%s%2i | %s%s/%s %s\n   %s|%s %s|_%s%s%s%s", BBLU, cb_dbg_info->line, RESET, BYEL, RESET, cb_dbg_info->line_str.c_str(), BBLU, RESET, BYEL, RESET, BYEL, cb_dbg_info->get_pos_str().c_str(), RESET));
            Logger::elog(Logger::format("%s%2i | %s%s\n",           BBLU, cb_dbg_info->line + 1, RESET,  cb_dbg_info->line_after.c_str()));
        };

        virtual ~Warning() {};

    private:
        DBGSourceInfo *cb_dbg_info;
    };

    class CompilerError : public SNError {
    public:

        CompilerError(Error code, std::string err, DBGSourceInfo* p_cb_dbg_info)
            : SNError(code, err) {
                cb_dbg_info = p_cb_dbg_info;
            };

        virtual void print_error() const {
            Logger::error(Logger::format("(%s%s%s) %s%s%s", RED, get_error(error), RESET, BOLD, message.c_str(), RESET));

            if (cb_dbg_info->line - 1 >= 1) // first line may not be available to log
            Logger::elog(Logger::format("%s  %2i | %s%s",           BBLK, cb_dbg_info->line - 1, RESET, cb_dbg_info->line_before.c_str()));
            Logger::elog(Logger::format(" %s>%s%2i | %s %s\n   %s  |%s  %s%s%s", BRED, BBLK, cb_dbg_info->line, RESET, cb_dbg_info->line_str.c_str(), BBLK, RESET, BRED, cb_dbg_info->get_pos_str().c_str(), RESET));
            Logger::elog(Logger::format("%s  %2i | %s%s",           BBLK, cb_dbg_info->line + 1, RESET,  cb_dbg_info->line_after.c_str()));

            Logger::elog(Logger::format("\n  %sat %s%s%s:%i:%i%s", BBLK, BBLU,
                cb_dbg_info->source_info->get_path().c_str(),
                BBLK,
                cb_dbg_info->line,
                cb_dbg_info->pos.second,
            RESET));


        };

        virtual ~CompilerError() {};

    private:
        DBGSourceInfo *cb_dbg_info;
    };
}

#endif // __SNOWBALL_ERRORS_H_

