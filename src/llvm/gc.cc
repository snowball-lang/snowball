
#include <cstdlib>
#include <cstdint>

#include <string>
#include <vector>
#include <utility>

#include "snowball/api.h"
#include "snowball/llvm/gc.h"
#include "snowball/constants.h"
#include "snowball/utils/mangle.h"

void register_gc(snowball::SNAPI* API) {
    snowball::ScopeValue* gc_allocate = API->create_function(
      "gc__alloca",
      API->get_compiler()->get_builder().getInt8PtrTy(),
      std::vector<std::pair<std::string, llvm::Type*>> {
        std::make_pair(
          "i32",
          API->get_compiler()->get_builder().getInt32Ty()
        )
      },
      true
    );

    snowball::ScopeValue* gc_reallocate = API->create_function(
      "gc__realloca",
      API->get_compiler()->get_builder().getInt8PtrTy(),
      std::vector<std::pair<std::string, llvm::Type*>> {
        std::make_pair(
          "i8",
          API->get_compiler()->get_builder().getInt8PtrTy()
        ),
        std::make_pair(
          "i32",
          API->get_compiler()->get_builder().getInt32Ty()
        )
      },
      true
    );

    API->add_to_enviroment(snowball::mangle("gc__alloca", {"i32"}, true), std::make_unique<snowball::ScopeValue*>(gc_allocate));
    API->add_to_enviroment(snowball::mangle("gc__realloca", {"i8", "i32"}, true), std::make_unique<snowball::ScopeValue*>(gc_reallocate));
}

extern "C" DLLEXPORT void* _MN10gc__allocaA3i32P(uint32_t bytes) {
  return malloc(bytes);
}

extern "C" DLLEXPORT void* _MN12gc__reallocaA2i8A3i32P(void* ptr, uint32_t bytes) {
  return realloc(ptr, bytes);
}
