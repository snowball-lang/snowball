

#ifndef __SNOWBALL_COMPILER_DID_YOU_MEAN_H__
#define __SNOWBALL_COMPILER_DID_YOU_MEAN_H__

#include <cstdint>

namespace snowball {
namespace utils {

static std::optional<std::string> did_you_mean(const std::string& input, const std::vector<std::string>& possibilities, uint64_t max_distance = 5) {
  std::optional<std::string> result;
  uint64_t min_distance = max_distance;
  for (const auto& possibility : possibilities) {
    uint64_t distance = 0;
    uint64_t input_length = input.length();
    uint64_t possibility_length = possibility.length();
    if (input_length == 0 || possibility_length == 0) {
      distance = input_length + possibility_length;
    } else {
      uint64_t* previous = new uint64_t[possibility_length + 1];
      uint64_t* current = new uint64_t[possibility_length + 1];
      for (uint64_t i = 0; i <= possibility_length; i++) {
        previous[i] = i;
      }
      for (uint64_t i = 0; i < input_length; i++) {
        current[0] = i + 1;
        for (uint64_t j = 0; j < possibility_length; j++) {
          uint64_t cost = (input[i] == possibility[j]) ? 0 : 1;
          current[j + 1] = std::min(std::min(current[j] + 1, previous[j + 1] + 1), previous[j] + cost);
        }
        for (uint64_t j = 0; j <= possibility_length; j++) {
          previous[j] = current[j];
        }
      }
      distance = current[possibility_length];
      delete[] previous;
      delete[] current;
    }
    if (distance < min_distance) {
      min_distance = distance;
      result = possibility;
    }
  }
  return result;
}

}
}

#endif // __SNOWBALL_COMPILER_DID_YOU_MEAN_H__

