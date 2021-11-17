#ifndef COORD_HPP
#define COORD_HPP

#include <cmath>
#define sqr(x) ((x) * (x))

class Coord {
 public:
  int x;
  int y;
  int level;

 private:
  double Distance(const Coord& c) {
    return sqrt(sqr(c.x - this->x) + sqr(c.y - this->y) + sqr((c.level - this->level) * 5));
  }
};

bool operator==(const Coord& c1, const Coord& c2);

#endif
