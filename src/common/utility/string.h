
#include "common/stl.h"

namespace snowball {
namespace utils {

/// @brief Split a string by a delimiter.
/// @param str The string to split.
/// @param delim The delimiter to split by. 
Vector<String> Split(const String& str, char delim);

/// @brief Join a vector of strings by a delimiter.
/// @param vec The vector of strings to join.
/// @param delim The delimiter to join by.
String Join(const Vector<String>& vec, char delim);

} // namespace utils
} // namespace snowball
