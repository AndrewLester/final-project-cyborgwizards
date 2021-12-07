#include "LevelPos.hpp"

bool operator==(const LevelPos& c1, const LevelPos& c2) { return c1.level == c2.level && c1.x == c2.x && c1.y == c2.y; }
bool operator!=(const LevelPos& c1, const LevelPos& c2) { return !(c1 == c2); }

LevelPos operator-(const LevelPos& c1, const LevelPos& c2) { return {c1.x - c2.x, c1.y - c2.y, c1.level - c2.level}; }

LevelPos& LevelPos::operator-=(const LevelPos& other) {
  x -= other.x;
  y -= other.y;
  level -= other.level;

  return *this;
}
