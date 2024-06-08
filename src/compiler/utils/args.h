
#ifndef __SNOWBALL_COMPILER_UTILS_ARGS_H__
#define __SNOWBALL_COMPILER_UTILS_ARGS_H__

#include <string>
#include <vector>
#include <cstring>

namespace snowball {
namespace utils {

class ArgsBuilder {
  std::vector<std::string> args;
public:
  ArgsBuilder() = default;
  ArgsBuilder(const ArgsBuilder&) = default;
  ArgsBuilder(ArgsBuilder&&) = default;
  ArgsBuilder& operator=(const ArgsBuilder&) = default;
  ArgsBuilder& operator=(ArgsBuilder&&) = default;
  ~ArgsBuilder() = default;

  void add(const std::string& arg) {
    args.push_back(arg);
  }

  void add(const std::vector<std::string>& arg) {
    args.insert(args.end(), arg.begin(), arg.end());
  }

  void add(const ArgsBuilder& arg) {
    args.insert(args.end(), arg.args.begin(), arg.args.end());
  }

  void add(const std::vector<const char*>& arg) {
    for (const auto& a : arg) {
      args.push_back(a);
    }
  }

  void add(const ArgsBuilder&& arg) {
    args.insert(args.end(), arg.args.begin(), arg.args.end());
  }

  virtual std::vector<std::string> build() {
    return args;
  }

  std::vector<const char*> build_c() {
    auto args = build();
    std::vector<const char*> c_args;
    c_args.reserve(args.size());
    for (const auto& arg : args) {
      c_args.push_back(strdup(arg.c_str()));
    }
    return c_args;
  }
};

} // namespace utils
} // namespace snowball

#endif // __SNOWBALL_COMPILER_UTILS_ARGS_H__
