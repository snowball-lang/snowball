
#pragma once

#include "common/stl.h"
#include "common/location.h"
#include "common/castable.h"

#include "frontend/token.h"

namespace snowball {
namespace frontend {

/// @brief A node.
/// A node is a single unit in the abstract syntax tree (AST). We use
/// nodes to represent language elements and organize them into a tree.
class Node final : public NonCopyable, public Castable<Node> {
public:
  /// @brief Delete the default constructor.
  Node() = delete;

  /// @brief Default destructor.
  ~Node() = default;

  /// @brief Construct a new node.
  /// @param type The type of the node.
  /// @param location The location of the node.
  Node(const SourceLocation& location) : mLocation(location) {}

  /// @brief Get the location of the node.
  /// @return The location of the node.
  SNOWBALL_NO_DISCARD inline auto GetLocation() const 
    -> const SourceLocation& { return mLocation; }
  
protected:
  SourceLocation mLocation;
};

}; // namespace frontend
}; // namespace snowball
