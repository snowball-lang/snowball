
#ifndef __SNOWBALL_FRONTEND_LOCATION_H__
#define __SNOWBALL_FRONTEND_LOCATION_H__

namespace snowball {
namespace frontend {

struct SourceLocation {
  unsigned int line;
  unsigned int column;
  unsigned int length;
  std::string file;                       
};

class LocationHolder {
  SourceLocation location;
public:
  LocationHolder(const SourceLocation& location) : location(location) {}
  SourceLocation get_location() const { return location; }
};

}
}

#endif // __SNOWBALL_FRONTEND_LOCATION_H__