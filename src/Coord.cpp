#include "Coord.hpp"

bool operator==(const Coord& c1, const Coord& c2) { return c1.level == c2.level && c1.x == c2.x && c1.y == c2.y; }
