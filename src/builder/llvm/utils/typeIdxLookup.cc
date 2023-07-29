#include "../LLVMBuilder.h"

namespace snowball {
namespace codegen {
namespace llvm_utils {
int typeIdxLookup(const std::string& name) {
  static std::unordered_map<std::string, int> cache;
  static int next = 1000;
  if (name.empty()) return 0;
  auto it = cache.find(name);
  if (it != cache.end()) {
    return it->second;
  } else {
    const int myID = next++;
    cache[name] = myID;
    return myID;
  }
}
} // namespace llvm_utils
} // namespace codegen
} // namespace snowball
