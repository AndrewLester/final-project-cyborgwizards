#include "MapShape.hpp"

MapShape::MapShape(int x_span, int y_span, Coord top_left) : x_span_(x_span), y_span_(y_span), top_left_(top_left) {}

bool MapShape::IsReachable() { return reachable_; }

bool MapShape::ContainsCoord(Coord position) {
  Coord difference = position - top_left_;
  return difference.x_ < x_span_ && difference.y_ < y_span_ && difference.level_ == 0;
}
