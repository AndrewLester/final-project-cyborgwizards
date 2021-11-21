#ifndef COORD_HPP
#define COORD_HPP

#include <cmath>
#define sqr(x) ((x) * (x))

class Coord {
 public:
  Coord(int x, int y, int level) : x_(x), y_(y), level_(level){};
  int x_;
  int y_;
  int level_;

  Coord& operator-=(const Coord& other);

 private:
  double Distance(const Coord& c) {
    return sqrt(sqr(c.x_ - this->x_) + sqr(c.y_ - this->y_) + sqr((c.level_ - this->level_) * 5));
  }
};

bool operator==(const Coord& c1, const Coord& c2);
Coord operator-(const Coord& c1, const Coord& c2);

#endif
