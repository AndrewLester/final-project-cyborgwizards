#include "Coord.hpp"

bool operator==(const Coord& c1, const Coord& c2) { return c1.level_ == c2.level_ && c1.x_ == c2.x_ && c1.y_ == c2.y_; }

Coord operator-(const Coord& c1, const Coord& c2) { return Coord(c1.x_ - c2.x_, c1.y_ - c2.y_, c1.level_ - c2.level_); }

Coord& Coord::operator-=(const Coord& other) {
  x_ -= other.x_;
  y_ -= other.y_;
  level_ -= other.level_;

  return *this;
}
