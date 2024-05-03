
#ifndef __SNOWBALL_FRONTEND_LOCATION_H__
#define __SNOWBALL_FRONTEND_LOCATION_H__

#include <filesystem>
#include <vector>

namespace snowball {
namespace frontend {

struct SourceFile {
  std::filesystem::path path;
public:
  SourceFile(const std::filesystem::path& path) : path(path) {}
  std::string get_path() const { return path.string(); }
  ~SourceFile() = default;
};

struct SourceLocation {
  unsigned int line;
  unsigned int column;
  unsigned int length;
  std::shared_ptr<SourceFile> file;

  SourceLocation(unsigned int line, unsigned int column, unsigned int length, std::shared_ptr<SourceFile> file) 
    : line(line), column(column), length(length), file(file) {}

  static SourceLocation dummy() {
    return SourceLocation(0, 0, 0, std::make_shared<SourceFile>("<invalid>"));
  }
};

class LocationHolder {
  SourceLocation location;
public:
  LocationHolder(const SourceLocation& location) : location(location) {}
  SourceLocation get_location() { return location; }
  SourceLocation get_location() const { return location; }
};

class NamespacePath {
  std::vector<std::string> path;
public:
  explicit NamespacePath(const std::vector<std::string>& path) : path(path) {}
  explicit NamespacePath(const std::string& path) : path({path}) {}
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
  auto operator<(const NamespacePath& other) const { return path < other.path; }
  auto operator+(const NamespacePath& other) const { 
    auto new_path = path;
    new_path.insert(new_path.end(), other.path.begin(), other.path.end());
    return NamespacePath(new_path);
  }

  static NamespacePath dummy() { return NamespacePath(std::vector<std::string>{}); }
};

// for "fmt::format"
static auto format_as(const NamespacePath& path) -> std::string {
  return path.get_path_string();
}

}
}

#endif // __SNOWBALL_FRONTEND_LOCATION_H__