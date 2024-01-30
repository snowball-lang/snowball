
#include "../../../ast/types/DefinedType.h"
#include "../../../ast/types/TypeAlias.h"
#include "../../Transformer.h"

using namespace snowball::utils;
using namespace snowball::Syntax::transform;

namespace snowball {
namespace Syntax {

std::vector<LLVMIRChunk>
Transformer::getLLVMBody(std::string block, std::vector<Syntax::Expression::TypeRef*> getTypesUsed) {
  // we iterate each character of the block.
  // if we find "{=[type]}" we replace it with the type
  std::vector<LLVMIRChunk> chunks;
  int typeIndex = 0;
  for (size_t i = 0; i < block.size();) {
    if (block[i] == '{' && block[i + 1] == '=') {
      // we found a type
      // we need to find the end of the type
      int end = i + 2;
      while (block[end] != '}') { end++; }
      // we found the end of the type
      // we need to get the type
      auto type = transformType(getTypesUsed[typeIndex]);
      // we need to add the type to the chunks
      chunks.push_back(LLVMIRChunk{.type = LLVMIRChunk::TypeAccess, .ty = type});
      // we need to increment the type index
      typeIndex++;
      // we need to set i to the end of the type
      i = end + 1;
    } else {
      int start = i;
      while (!((block[i] == '{') && (block[i + 1] == '=')) && (i < block.size())) i++;
      auto code = block.substr(start, i - start);
      chunks.push_back(LLVMIRChunk{.type = LLVMIRChunk::LLCode, .code = code});
    }
  }
  return chunks;
}

} // namespace Syntax
} // namespace snowball
