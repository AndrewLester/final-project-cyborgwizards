#ifndef LEVEL_POS_HPP
#define LEVEL_POS_HPP

#include <cmath>
#include <ostream>
#include <string>
#define sqr(x) ((x) * (x))

struct LevelPos {
  int x;
  int y;
  int level;

  // LevelPos(int x_, int y_): x(x_), y(y_){}

  LevelPos& operator-=(const LevelPos& other);

  double Distance(const LevelPos& c) {
    return sqrt(sqr(c.x - this->x) + sqr(c.y - this->y) + sqr((c.level - this->level) * 5));
  }

  std::string ToString() const;
};

bool operator==(const LevelPos& c1, const LevelPos& c2);
bool operator!=(const LevelPos& c1, const LevelPos& c2);
LevelPos operator-(const LevelPos& c1, const LevelPos& c2);
std::ostream& operator<<(std::ostream& os, const LevelPos& pos);
#endif
