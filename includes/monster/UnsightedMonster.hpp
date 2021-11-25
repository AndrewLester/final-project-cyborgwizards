#ifndef UNSIGHTED_MONSTER_HPP
#define UNSIGHTED_MONSTER_HPP

#include "Monster.hpp"

class UnsightedMonster : public Monster {
 public:
  void OnNotify(Event event);
}

#endif