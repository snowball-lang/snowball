
#include <vector>

#include "nodes.h"
#include "scopes.h"
#include "source_info.h"

#ifndef __SNOWBALL_ENVIROMENT_H_
#define __SNOWBALL_ENVIROMENT_H_

#define SN_GLOBAL_SCOPE "$sn_global_scope"

namespace snowball {

    class Enviroment {
        public: // structs
            struct FunctionStore {
                FunctionNode* node;

                ScopeValue* current_module = nullptr;
                ClassNode* current_class = nullptr;
            };

        public:
            Enviroment(SourceInfo* p_source_info);

            Scope* global_scope();
            Scope* current_scope();

            void delete_scope();

            Scope* create_scope(Scope* p_scope);
            Scope* create_scope(std::string p_name);

            ScopeValue* get(std::string name, Node* p_node, std::string p_o_name = "");
            bool item_exists(std::string name);


            // Make sure to call function_exists() first!
            FunctionStore get_function(std::string name) { return this->_functions.at(name); }
            bool function_exists(std::string name) {
                return this->_functions.find(name) != this->_functions.end();
            }

            void set_function(std::string name, FunctionStore store) { this->_functions.emplace( name, store ); };

            #if _SNOWBALL_SYMTABLE_DEBUG
            void debug(Scope* current_scope = nullptr, int depth = 0);
            #endif

            ~Enviroment() {};

        private:
            SourceInfo* _source_info;
            std::vector<Scope*> _scopes;
            std::map<std::string /* mangled names */, FunctionStore> _functions;

    };

}

#endif // __SNOWBALL_ENVIROMENT_H_
