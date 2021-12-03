#ifndef LEVEL_POS_HPP
#define LEVEL_POS_HPP

#include <cmath>
#define sqr(x) ((x) * (x))

struct LevelPos {
 public:
  int x;
  int y;
  int level;

  LevelPos& operator-=(const LevelPos& other);

 private:
  double Distance(const LevelPos& c) {
    return sqrt(sqr(c.x - this->x) + sqr(c.y - this->y) + sqr((c.level - this->level) * 5));
  }
};

bool operator==(const LevelPos& c1, const LevelPos& c2);
LevelPos operator-(const LevelPos& c1, const LevelPos& c2);

#endif
