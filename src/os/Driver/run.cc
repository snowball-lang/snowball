
#include "../../constants.h"
#include "../../utils/utils.h"
#include "../Driver.h"

namespace snowball {
namespace os {
int Driver::run(std::vector<std::string> args) {
  std::string command = utils::join(args.begin(), args.end(), " ");
  DEBUG_CODEGEN("Running command: %s", command.c_str());
  int status = std::system(command.c_str());
  return status;
}
} // namespace os
} // namespace snowball
