
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
            Enviroment(SourceInfo* p_source_info, SnowballBuildinTypes p_buildin_types);

            Scope* global_scope();
            Scope* current_scope();

            Scope* create_scope(std::string p_name);
            void delete_scope();

            ScopeValue* get(std::string name, Node* p_node);
            bool item_exists(std::string name, Node* p_node);

            ~Enviroment() {};

        private:
            SourceInfo* _source_info;
            std::vector<Scope*> _scopes;
            SnowballBuildinTypes _buildin_types;
    };

}

#endif // __SNOWBALL_ENVIROMENT_H_