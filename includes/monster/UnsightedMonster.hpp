#ifndef UNSIGHTED_MONSTER_HPP
#define UNSIGHTED_MONSTER_HPP

#include "Monster.hpp"

class UnsightedMonster : public Monster {
 private:
  int prev_intensity_ = 0;
 public:
  void OnNotify(Event event);
};

#endif