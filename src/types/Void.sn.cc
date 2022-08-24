
#include "snowball/api.h"
#include "snowball/types.h"
#include "snowball/scopes.h"
#include "snowball/snowball.h"
#include "snowball/types/Void.h"

#include "snowball/export.hpp"

#include <vector>
#include <utility>

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "snowball/constants.h"

void register_void(snowball::SNAPI* API) {

    API->create_class("Void", std::map<std::string, llvm::Type*> {}, [API](snowball::ScopeValue* CLASS) {});
}