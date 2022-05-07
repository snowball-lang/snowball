
#include <map>
#include <memory>
#include <variant>

#include <llvm/IR/Value.h>

#ifndef __SNOWBALL_PARSER_H_
#define __SNOWBALL_PARSER_H_

namespace snowball {

    class Scope {

        private:
            std::map<std::string, std::variant<llvm::Value, Scope>> _values;

    };

}

#endif // __SNOWBALL_PARSER_H_
