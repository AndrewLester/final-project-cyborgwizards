#ifndef COORD_HPP
#define COORD_HPP

#include <cmath>
#define sqr(x) ((x)*(x))

class Coord {
 public:
  Coord(int x, int y); //Coord constructor should handle the case where x and y are out of bounds, in this case all fields are set to -1
  int x_;
  int y_;
  int level_;
  int GetX();
  int GetY();
  int GetLevel();

 private:
  double Distance(const Coord& c) {
    return sqrt(sqr(c.x - this->x) + sqr(c.y - this->y) + sqr((c.level - this->level) * 5));
  }
};

#endif