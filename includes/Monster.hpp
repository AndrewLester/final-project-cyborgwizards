#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <queue>

#include "Entity.hpp"
#include "MapRoom.hpp"

enum MonsterState { Roam, Chase, Search };

class Monster : public Entity {
 protected:
  MonsterState state_ = MonsterState::Roam;
  int roam_speed_ = 5;
  int chase_speed_ = 3;
  std::queue<LevelPos> path_;

 private:
  int timer_ = 0;

 public:
  virtual void Update();
  void ChangeDestination(MapRoom* room);
  virtual void OnNotify(Event event) = 0;
};

#endif
