
#include <vector>
#include "scopes.h"

#ifndef __SNOWBALL_ENVIROMENT_H_
#define __SNOWBALL_ENVIROMENT_H_

namespace snowball {

    class Enviroment {

        public:
            Enviroment();
            ~Enviroment() {};

        private:
            std::vector<Scope> _scopes;

    };

}

#endif // __SNOWBALL_ENVIROMENT_H_
