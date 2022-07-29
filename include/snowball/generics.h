
#include "snowball.h"
#include "compiler.h"

#include <map>
#include <vector>

#ifndef __SNOWBALL_GENERICS_H_
#define __SNOWBALL_GENERICS_H_

namespace snowball {
    class Generics {
        public:

            struct GenericValue {
                std::string name;
                std::vector<std::string> args;
                std::string return_ty;
                FunctionNode* node;
            };

            struct GenericStore : public GenericValue {
                std::vector<std::string> generics;
            };

            Generics(Compiler* p_compiler) : _compiler(p_compiler) {};

            std::pair<GenericValue, bool> get_generic(std::string p_name, std::vector<std::string> p_args, std::vector<std::string> p_generics, Node* p_node);
            void add_generic(std::string p_name, std::vector<std::string> p_args, std::string ret, std::vector<std::string> p_generics, Node* p_node);

            ~Generics() {};

        private:
            Compiler* _compiler;
            std::vector<GenericStore*> _stores;
    };
}

#endif // __SNOWBALL_GENERICS_H_
