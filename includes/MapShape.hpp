#ifndef MAP_SHAPE_HPP
#define MAP_SHAPE_HPP

#include "Coord.hpp"

class MapShape {
 public:
  MapShape(int x_span, int y_span, Coord top_left);
  /**
   * @brief The distance in x coordinate that the shape extends.
   * A value of 1 corresponds to one cell in the x direction.
   * x_span_ and y_span_ of 1 represent a single cell.
   */
  int x_span_;
  /**
   * @brief The distance in y coordinate that the shape extends.
   * A value of 1 corresponds to one cell in the y direction.
   * x_span_ and y_span_ of 1 represent a single cell.
   */
  int y_span_;
  Coord top_left_;

 protected:
  bool reachable_ = false;

 public:
  virtual void Draw(Coord center) = 0;
  bool IsReachable();
  bool ContainsCoord(Coord position);
};

#endif
