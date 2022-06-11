
#include <vector>

#include "nodes.h"
#include "scopes.h"
#include "source_info.h"

#ifndef __SNOWBALL_ENVIROMENT_H_
#define __SNOWBALL_ENVIROMENT_H_

#define SN_GLOBAL_SCOPE "__sn_global_scope"

namespace snowball {

    class Enviroment {

        public:
            Enviroment(SourceInfo* p_source_info);

            Scope* global_scope();
            Scope* current_scope();

            Scope* create_scope(std::string p_name);
            void delete_scope();

            ~Enviroment() {};

        private:
            SourceInfo* _source_info;
            std::vector<Scope*> _scopes;
            ScopeValue get(std::string name, Node p_node);
    };

}

#endif // __SNOWBALL_ENVIROMENT_H_
