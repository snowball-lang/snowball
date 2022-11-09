
#include <vector>

#include "nodes.h"
#include "scopes.h"
#include "source_info.h"

#ifndef __SNOWBALL_ENVIROMENT_H_
#define __SNOWBALL_ENVIROMENT_H_

#define SN_GLOBAL_TYPES "$sn_global_types"
#define SN_GLOBAL_SCOPE "$sn_global_scope"

namespace snowball {

    class Enviroment {
        public: // structs
            struct FunctionStore {
                FunctionNode* node;

                ScopeValue* current_module = nullptr;
                ScopeValue* current_namespace = nullptr;
                ClassNode* current_class = nullptr;
            };

        public:
            Enviroment(SourceInfo* p_source_info);

            Scope* global_scope();
            Scope* global_types();
            Scope* current_scope();

            void delete_scope();

            Scope* create_scope(Scope* p_scope);
            Scope* create_scope(std::string p_name);

            ScopeValue* get(std::string name, Node* p_node, std::string p_o_name = "");
            bool item_exists(std::string name);

            // When a function call, we generate a function.
            // This creates problem since the new function inherits
            // from the old function. This functions are used to remove
            // all scopes (except global) then, execute the new function
            // and restore the last scope.
            // note: save state will also remove all scopes (except global)
            std::vector<Scope*> save_state(bool save_global = true);
            void restore_state(std::vector<Scope*> p_scopes, bool with_global = true);

            // Make sure to call function_exists() first!
            Enviroment::FunctionStore* find_function_if(std::string name, std::function<std::pair<bool, bool>(const Enviroment::FunctionStore)> cb, Node* p_node);
            void set_function(std::string name, FunctionStore* store);

            #if _SNOWBALL_SYMTABLE_DEBUG
            void debug(Scope* current_scope = nullptr, int depth = 0);
            #endif

            ~Enviroment() {};

        private:
            SourceInfo* _source_info;
            std::vector<Scope*> _scopes;
            std::map<std::string, std::vector<FunctionStore*>> _functions;

    };

}

#endif // __SNOWBALL_ENVIROMENT_H_
