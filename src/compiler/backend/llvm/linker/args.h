

#ifndef __SNOWBALL_BACKEND_LLVM_LINKER_ARGS_H__
#define __SNOWBALL_BACKEND_LLVM_LINKER_ARGS_H__

#include <vector>
#include <string>
#include <filesystem>

#include "compiler/utils/args.h"
#include "compiler/backend/llvm/llvm.h"

namespace snowball {
namespace backend {

class LldArgsBuilder : public utils::ArgsBuilder {
  llvm::TargetMachine* target_machine;
  std::string output_file;
  std::string obj_file;
public:
  LldArgsBuilder(llvm::TargetMachine* target_machine, 
    std::string output_file, std::string obj_file)
    : target_machine(target_machine), output_file(output_file), 
      obj_file(obj_file) {}

  std::vector<std::string> build() override;

  void add_default_args();
  void add_user_switches();
  void add_object_files();
  void add_platform_args();
};

} // namespace backend
} // namespace snowball

#endif // __SNOWBALL_BACKEND_LLVM_LINKER_ARGS_H__

