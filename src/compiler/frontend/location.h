
#ifndef __SNOWBALL_FRONTEND_LOCATION_H__
#define __SNOWBALL_FRONTEND_LOCATION_H__

#include <filesystem>
#include <vector>

namespace snowball {
namespace frontend {

struct SourceFile {
  std::filesystem::path path;

public:
  SourceFile(const std::filesystem::path& path)
    : path(path) {}
  SourceFile() = default;
  std::string get_path() const { return path.string(); }
  ~SourceFile() = default;
};

struct SourceLocation {
  unsigned int line;
  unsigned int column;
  unsigned int length;
  std::shared_ptr<SourceFile> file;

  SourceLocation(
    unsigned int line, unsigned int column, unsigned int length,
    std::shared_ptr<SourceFile> file
  ) : line(line), column(column), length(length), file(file) {}

  static SourceLocation dummy() {
    return SourceLocation(0, 0, 0, std::make_shared<SourceFile>("<invalid>"));
  }
};

class LocationHolder {
  SourceLocation location;

public:
  LocationHolder(const SourceLocation& location)
    : location(location) {}
  SourceLocation& get_location() { return location; }
  SourceLocation get_location() const { return location; }
};

class NamespacePath {
  std::vector<std::string> path;

public:
  explicit NamespacePath(const std::vector<std::string>& path)
    : path(path) {}
  explicit NamespacePath(const std::string& path)
    : path({path}) {}
  std::vector<std::string> get_path() const { return path; }
  std::string get_path_string() const;
  std::string get_last() const { return path.back(); }
  bool is_empty() const { return path.empty(); }
  auto size() const { return path.size(); }
  ~NamespacePath() = default;

  void push(const std::string& part) { path.push_back(part); }
  static NamespacePath from_file(const std::filesystem::path& file);

  auto operator[](size_t i) const { return path[i]; }
  auto operator==(const NamespacePath& other) const { return path == other.path; }
  auto operator!=(const NamespacePath& other) const { return path != other.path; }
  auto operator<(const NamespacePath& other) const { return path < other.path; }
  auto operator+(const NamespacePath& other) const {
    auto new_path = path;
    if (path[0].empty()) // if this is empty, return the other
      return other;
    new_path.insert(new_path.end(), other.path.begin(), other.path.end());
    return NamespacePath(new_path);
  }

  static NamespacePath dummy() { return NamespacePath(std::vector<std::string>{}); }

  class const_iterator {
    std::vector<std::string>::const_iterator it;

  public:
    const_iterator(std::vector<std::string>::const_iterator it)
      : it(it) {}
    auto operator*() const { return *it; }
    auto operator++() {
      ++it;
      return *this;
    }
    auto operator++(int) {
      auto tmp = *this;
      ++it;
      return tmp;
    }
    auto operator==(const const_iterator& other) const { return it == other.it; }
    auto operator!=(const const_iterator& other) const { return it != other.it; }
  };

  class iterator {
    std::vector<std::string>::iterator it;

  public:
    iterator(std::vector<std::string>::iterator it)
      : it(it) {}
    auto operator*() { return *it; }
    auto operator++() {
      ++it;
      return *this;
    }
    auto operator++(int) {
      auto tmp = *this;
      ++it;
      return tmp;
    }
    auto operator==(const iterator& other) const { return it == other.it; }
    auto operator!=(const iterator& other) const { return it != other.it; }
  };

  auto begin() const { return const_iterator(path.begin()); }
  auto end() const { return const_iterator(path.end()); }

  auto begin() { return iterator(path.begin()); }
  auto end() { return iterator(path.end()); }
};

// for "fmt::format"
static auto format_as(const NamespacePath& path) -> std::string {
  return path.get_path_string();
}

} // namespace frontend
} // namespace snowball

#endif // __SNOWBALL_FRONTEND_LOCATION_H__