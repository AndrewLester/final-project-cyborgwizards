#ifndef MAP_SHAPE_HPP
#define MAP_SHAPE_HPP

#include "Coord.hpp"

class MapShape {
 public:
  int x_span;
  int y_span;
  Coord top_left;

 protected:
  bool reachable_;

 public:
  virtual void Draw() = 0;
  bool IsReachable();
  bool ContainsCoord(Coord position);
};

#endif
