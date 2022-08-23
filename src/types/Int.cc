
#include "snowball/api.h"
#include "snowball/types.h"
#include "snowball/scopes.h"
#include "snowball/snowball.h"
#include "snowball/types/Int.h"

#include "snowball/export.hpp"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "snowball/constants.h"

void register_number(snowball::SNAPI* API) {

    API->create_class("Int", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {});
    API->create_class("i16", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {});
    API->create_class("i32", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {});
    API->create_class("i64", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {});
}