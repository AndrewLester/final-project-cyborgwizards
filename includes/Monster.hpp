#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <deque>

#include "Entity.hpp"
#include "MapRoom.hpp"
#include "Map.hpp"

enum MonsterState { Roam, Chase, Search };

class Monster : public Entity {
 protected:
  MonsterState state_ = MonsterState::Roam;
  int roam_speed_ = 5;
  int chase_speed_ = 3;
  LevelPos destination_ = {-1, -1, -1};
  std::deque<LevelPos> path_;

 private:
  int timer_ = 0;
  void FindPath(const AdjacentList& map, std::set<MapRoom*>& visited, MapRoom* curr, MapRoom* dest, bool& found);

 public:
  virtual void Update();
  void ChangeDestination(LevelPos destination);
  virtual void OnNotify(Event event) = 0;
};

#endif
