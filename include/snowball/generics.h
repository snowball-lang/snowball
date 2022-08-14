
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
                std::vector<Type*> args;
                Type* return_ty;
                FunctionNode* node;
            };

            struct GenericStore : public GenericValue {
                std::vector<Type*> generics;
            };

            Generics(Compiler* p_compiler) : _compiler(p_compiler) {};

            std::pair<GenericValue, bool> get_generic(std::string p_name, std::vector<Type*> p_args, std::vector<Type*> p_generics, Node* p_node);
            void add_generic(std::string p_name, std::vector<Type*> p_args, Type* ret, std::vector<Type*> p_generics, Node* p_node);

            ~Generics() {};

        private:
            Compiler* _compiler;
            std::vector<GenericStore*> _stores;
    };
}

#endif // __SNOWBALL_GENERICS_H_
