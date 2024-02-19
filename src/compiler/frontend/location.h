
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
  SourceLocation get_location() const { return location; }
};

class NamespacePath {
  std::vector<std::string> path;
public:
  NamespacePath(const std::vector<std::string>& path) : path(path) {}
  std::vector<std::string> get_path() const { return path; }
  std::string get_path_string() const;
  ~NamespacePath() = default;
};

}
}

#endif // __SNOWBALL_FRONTEND_LOCATION_H__