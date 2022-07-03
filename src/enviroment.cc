
#include "snowball/types.h"
#include "snowball/errors.h"
#include "snowball/scopes.h"
#include "snowball/enviroment.h"

#include <llvm-10/llvm/Support/raw_ostream.h>
#include <llvm/IR/Type.h>

#include <memory>
#include <numeric>
#include <sstream>
#include <algorithm>


#define NEW_CLASS_DECLARATION(class) \
    Scope*  class##_class_scope = new Scope(#class, _source_info); \
    ScopeValue* class##_class_scope_val = new ScopeValue(class##_class_scope); \
    std::unique_ptr<ScopeValue*> value_##class##_class = std::make_unique<ScopeValue*>(class##_class_scope_val); \

#define INSERT_CLASS_TO_GLOBAL(class) \
    global_scope->set(#class, std::move(value_##class##_class));

#define NEW_CLASS_PROPERTY(class, name, fname, value) \
    std::shared_ptr<llvm::Function*> fn_##class##_##name##_ptr = std::make_shared<llvm::Function*>(*value);\
    ScopeValue* scopev_##class##_##name = new ScopeValue(fn_##class##_##name##_ptr);\
    std::unique_ptr<ScopeValue*> value_##class##_##name = std::make_unique<ScopeValue*>(scopev_##class##_##name);\
    class##_class_scope->set(fname, std::move(value_##class##_##name));


namespace snowball_utils {
    template <typename Iter>
    std::string join(Iter begin, Iter end, std::string const& separator)
    {
        std::ostringstream result;
        if (begin != end)
            result << *begin++;
        while (begin != end)
            result << separator << *begin++;
        return result.str();
    }
}

namespace snowball {
    Enviroment::Enviroment(SourceInfo* p_source_info, struct SnowballBuildinTypes p_buildin_types) : _source_info(p_source_info) {
        _buildin_types = std::move(p_buildin_types);

        Scope* global_scope = new Scope("__sn__global__", _source_info);
        _scopes.push_back(global_scope);

        NEW_CLASS_DECLARATION(Number)

        NEW_CLASS_PROPERTY(Number, init, "__new", _buildin_types.sn_number__new)
        NEW_CLASS_PROPERTY(Number, sum, "__sum", _buildin_types.sn_number__sum)

        INSERT_CLASS_TO_GLOBAL(Number)
    }

    ScopeValue* Enviroment::get(std::string name, Node* p_node) {
        size_t pos_start = 0, pos_end, delim_len = 1;
        std::string token;
        std::vector<std::string> parts;

        while ((pos_end = name.find (".", pos_start)) != std::string::npos) {
            token = name.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            parts.push_back (token);
        }

        parts.push_back (name.substr (pos_start));
        if (parts.size() > 1) {
            ScopeValue* scope = get(parts[0], p_node);
            if (scope->type == ScopeType::SCOPE) {
                return scope->scope_value->get(snowball_utils::join(++parts.begin(), parts.end(), "."), p_node);

            }
        }

        std::vector<Scope*> reversed_scopes = _scopes;
        std::reverse(reversed_scopes.begin(), reversed_scopes.end());

        for (Scope* scope : reversed_scopes) {
            bool value = scope->item_exists(name);

            if (value) {
                return scope->get(name, p_node);
            }
        }

        if (p_node == nullptr) {
            throw SNError(Error::BUG, Logger::format("'%s' is not defined (p_node has not been passed to Enviroment::get)", name.c_str()));
        }

        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
        throw CompilerError(Error::VARIABLE_ERROR, Logger::format("'%s' is not defined", name.c_str()), dbg_info);
    }

    bool Enviroment::item_exists(std::string name, Node* p_node) {

        DBGSourceInfo* dbg_info = new DBGSourceInfo((SourceInfo*)_source_info, p_node->pos, p_node->width);
        size_t pos_start = 0, pos_end, delim_len = 1;
        std::string token;
        std::vector<std::string> parts;

        while ((pos_end = name.find (".", pos_start)) != std::string::npos) {
            token = name.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            parts.push_back (token);
        }

        parts.push_back (name.substr (pos_start));

        if (parts.size() > 1) {
            return item_exists(parts[0], p_node);
        }

        std::vector<Scope*> reversed_scopes = _scopes;
        std::reverse(reversed_scopes.begin(), reversed_scopes.end());

        for (Scope* scope : reversed_scopes) {
            bool value = scope->item_exists(name);

            if (value) {
                return true;
            }
        }

        return false;
    }

    Scope* Enviroment::global_scope() {
        return _scopes.at(0);
    }

    Scope* Enviroment::current_scope() {
        return _scopes.at(_scopes.size()-1);
    }

    Scope* Enviroment::create_scope(std::string p_name) {
        _scopes.push_back(new Scope(p_name, _source_info));
        return current_scope();
    }

    void Enviroment::delete_scope() {
        _scopes.pop_back();
    }
}
