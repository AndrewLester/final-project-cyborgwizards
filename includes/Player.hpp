#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <libtcod.h>

#include "Entity.hpp"
#include "Inventory.hpp"
enum class PlayerState { Walk, Run, Hide, Stop };
enum class Facing { N, W, E, S };

class Player : public Entity {
 private:
  int walk_speed_ = 5;
  int run_speed_ = 2;
  int timer_ = 0;
  int hp_ = 100;
  Inventory* inventory_ = nullptr;
  PlayerState state_ = PlayerState::Stop;
  Facing facing_ = Facing::N;

  const int kWalkSound = 1;
  const int kRunSound = 2;

 public:
  Player(LevelPos init_pos);

  void Draw(ScreenPos top_left);
  void OnNotify(Event* event);
  void Update();

  Inventory* GetInventory();
  Facing GetFacingDir();
  int GetHp();
};

#endif
