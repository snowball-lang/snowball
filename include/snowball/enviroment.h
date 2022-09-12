
#include <vector>

#include "nodes.h"
#include "scopes.h"
#include "source_info.h"

#ifndef __SNOWBALL_ENVIRONMENT_H_
#define __SNOWBALL_ENVIRONMENT_H_

#define SN_GLOBAL_SCOPE "$sn_global_scope"

namespace snowball {

    class Enviroment {

        public:
            Enviroment(SourceInfo* p_source_info);

            Scope* global_scope();
            Scope* current_scope();

            void delete_scope();

            Scope* create_scope(Scope* p_scope);
            Scope* create_scope(std::string p_name);

            ScopeValue* get(std::string name, Node* p_node, std::string p_o_name = "");
            bool item_exists(std::string name);

            #if _SNOWBALL_SYMTABLE_DEBUG
            void debug(Scope* current_scope = nullptr, int depth = 0);
            #endif

            ~Enviroment() {};

        private:
            SourceInfo* _source_info;
            std::vector<Scope*> _scopes;
    };

}

#endif // __SNOWBALL_ENVIROMENT_H_
