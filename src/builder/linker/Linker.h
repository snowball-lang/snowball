#include "../../compiler.h"
#include <llvm/ADT/Triple.h>

#ifndef __SNOWBALL_CODEGEN_LINKER_H_
#define __SNOWBALL_CODEGEN_LINKER_H_

namespace snowball {
namespace linker {

/**
 * @class Linker
 * @brief The Linker class provides functionality for linking object files and generating executables.
 *
 * The Linker class takes in a list of object files, linker options, and an output file name,
 * and performs the linking process to create an executable file. It utilizes an internal
 * vector to store the linker arguments.
 */
class Linker {
  /// @brief Vector to store the linker arguments.
  std::vector<std::string> linkerArgs;
  /// @brief The path to the linker executable.
  std::string ldPath;
  /// @brief Vector to store the names of linked libraries.
  std::vector<std::string> linkedLibraries;
  /// @brief Pointer to the global context.
  GlobalContext* ctx;
  /// @brief The target triple.
  llvm::Triple target;
  /// @brief A list of rpaths to be added to the executable.
  std::vector<std::string> rpaths = {
          "/usr/local/lib", "/usr/lib", "/usr/lib/x86_64-linux-gnu", "/lib/x86_64-linux-gnu", "/lib"};

public:
  /**
   * @brief Default constructor for the Linker class.
   *
   * This constructor initializes the Linker object with default settings.
   */
  Linker(GlobalContext* ctx, std::string ldPath = LD_PATH);
  /**
   * @brief Default destructor for the Linker class.
   *
   * The destructor is set to default, and it will be automatically called when the
   * Linker object goes out of scope or is explicitly deleted.
   */
  ~Linker() = default;
  /**
   * @brief Links the given object files and generates an executable.
   *
   * This function takes in a vector of object files, an output file name, and
   * a vector of additional linker arguments. It then performs the linking process
   * using the provided arguments and generates an executable with the specified output name.
   *
   * @param[in] files A reference to a vector of strings containing the paths to object files.
   * @param[in] output A reference to a string representing the desired output file name.
   * @param[in] args A reference to a vector of strings containing additional linker arguments.
   */
  int link(std::string& input, std::string& output, std::vector<std::string>& args);
  /**
   * @brief Adds a library to the list of linked libraries.
   *
   * This function takes in a string representing the name of a library and adds it to the
   * list of linked libraries. The library name should not include the "lib" prefix or the
   * file extension.
   *
   * @param[in] library A reference to a string representing the name of the library.
   */
  void addLibrary(std::string& library);
  /**
   * @brief It returns the name for a shared library.
   */
  static std::string getSharedLibraryName(std::string& library);

private:
  /**
   * @brief Constructs the linker arguments based on input, output, and additional arguments.
   *
   * This private function constructs the linker arguments based on the provided input,
   * output file name, and additional arguments. The resulting linker arguments are stored
   * in the internal linkerArgs vector.
   *
   * @param[in] input A reference to a string representing the input file name.
   * @param[in] output A reference to a string representing the output file name.
   * @param[in] args A reference to a vector of strings containing additional linker arguments.
   */
  void constructLinkerArgs(std::string& input, std::string& output, std::vector<std::string>& args);
  /**
   * @brief Transform an llvm triple into a platform triple.
   *
   */
  std::string getPlatformTriple();
};

// check if we are in a supported platform
#if !(defined(__linux__) || defined(__unix__) || defined(__unix) || defined(__APPLE__))
#error "Unsupported platform for linking!"
#endif

} // namespace linker
} // namespace snowball

#endif // __SNOWBALL_CODEGEN_LINKER_H_