#ifndef ITEM_HPP
#define ITEM_HPP

#include "LevelPos.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Item : public Entity {
 private:
  LevelPos CheckNearestOpenPos();
  Player* player_ = nullptr;
  // TODO: store a bool in_inventory_ and a public function for render purposes

 public:
  virtual void Draw(ScreenPos top_left) = 0;
  virtual void Use() = 0;
  void Drop();
  void Pick(Player* player);
};

#endif
