
#include <vector>
#include "scopes.h"

#ifndef __SNOWBALL_ENVIROMENT_H_
#define __SNOWBALL_ENVIROMENT_H_

#define SN_GLOBAL_SCOPE "__sn_global_scope"

namespace snowball {

    class Enviroment {

        public:
            Enviroment();

            Scope global_scope();

            ~Enviroment() {};

        private:
            std::vector<Scope> _scopes;

    };

}

#endif // __SNOWBALL_ENVIROMENT_H_
