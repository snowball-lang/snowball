
#ifndef __SNOWBALL_COMPILER_H__
#define __SNOWBALL_COMPILER_H__

#include <string>
#include <vector>

#include "compiler/utils/timers.h"
#include "ctx.h"

#include "compiler/sil/binder.h"
#include "compiler/backend/drivers.h"
#include "compiler/backend/llvm/builder.h"
#include "compiler/frontend/ast/lexer.h"
#include "compiler/frontend/ast/module.h"
#include "compiler/frontend/ast/parser.h"
#include "compiler/frontend/location.h"

#include "compiler/frontend/sema/check.h"
#include "compiler/frontend/generic/visitor.h"

#include "compiler/llvm_stl.h"

#define SNOWBALL_DEFAULT_VISITOR_COUNT 4

namespace snowball {
namespace reky {
class RekyManager;
}

class CompilationError final : public std::exception {
public:
  CompilationError() = default;
  ~CompilationError() = default;
};

/**
 * @brief The Compiler class is responsible for compiling the source code into a binary
 * file.
 *
 * The compiler takes care of absolutely everything that is needed to compile the
 *  source core providing a simple interface to the user.
 */
class Compiler {
  Ctx ctx;
  utils::Timer timer;

  std::vector<frontend::Module> modules;
  std::vector<frontend::NamespacePath> module_paths;
  std::vector<std::filesystem::path> object_files;

  std::vector<std::filesystem::path> allowed_paths;

  static float progress_iteration;
  friend class sil::Binder;

public:
  Compiler(Ctx& ctx);
  ~Compiler() = default;

  /**
   * @brief Compiles the source code into a binary file.
   *
   * @return true if the compilation was successful, false otherwise.
   */
  bool compile();
  /**
   * @brief Compiles the source code into a binary file.
   *
   * @param ctx The context of the compiler.
   * @return true if the compilation was successful, false otherwise.
   */
  static bool compile(Ctx& ctx);
  /**
   * @brief It prepares the context for the compilation.
   * @param reky The RekyManager instance (used as out parameter). Default is nullptr.
   * @return A list of allowed paths (uncompleted list).
   */
  static std::vector<std::filesystem::path>
  prepare_context(Ctx& ctx, reky::RekyManager** reky = nullptr);

  struct MiddleEndResult {
    std::vector<std::shared_ptr<sil::Module>> sil_modules;
    llvm::DenseMap<uint64_t, sil::Inst*> sil_insts;
  };

private:
  std::string get_package_type_string();
  static void print_compiling_bar(std::vector<frontend::Module>& modules);

  void run_frontend();
  MiddleEndResult run_middleend();
  int run_backend(const MiddleEndResult& middleend_result);

  void stop_compilation();
  void post_compile();

  void run_visitors();
  llvm::SmallVector<frontend::GenericVisitor*, SNOWBALL_DEFAULT_VISITOR_COUNT> get_visitors();
};

} // namespace snowball

#endif // __SNOWBALL_COMPILER_H__