#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "Inventory.hpp"
enum class PlayerState { Walk, Run, Hide, Stop };

class Player : public Entity {
 private:
  int walk_speed_ = 5;
  int run_speed_ = 2;
  int timer_ = 0;
  PlayerState state_ = PlayerState::Stop;
  int hp_ = 100;
  Inventory* inventory_;
 public:
  Player(LevelPos init_pos);
  Inventory* GetInventory();
  void Draw(ScreenPos top_left);
  void OnNotify(Event event);
  void Update();
};

#endif
