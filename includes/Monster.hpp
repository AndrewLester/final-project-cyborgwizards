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
  int roam_speed_ = 16;
  int chase_speed_ = 9;
  LevelPos destination_ = {-1, -1, -1};
  std::deque<LevelPos> path_;
  std::vector<std::deque<LevelPos>> paths_;

  const int kRoamSound;
  const int kChaseSound;
  const int kStunCooldown = 1500;
  int stun_cooldown_ = 0;
  int timer_ = 0;
  Monster(LevelPos pos, int roam_sound, int chase_sound);

 private:
  void FindPath(const AdjacentList& map, std::set<MapShape*>& visited, MapShape* curr, MapShape* dest);

 public:
  void Update();
  void ChangeDestination(LevelPos destination);
  virtual void OnNotify(Event* event) = 0;
};

#endif
