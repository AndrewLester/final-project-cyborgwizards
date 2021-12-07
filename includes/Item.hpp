#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

#include "Entity.hpp"
#include "LevelPos.hpp"
#include "Player.hpp"

class Item : public Entity {
 private:
  LevelPos CheckNearestOpenPos();
  Player* player_ = nullptr;
  bool in_inventory_;
  std::string name_;

 protected:
  Item(LevelPos pos, std::string name);

 public:
  virtual void Draw(ScreenPos top_left) = 0;
  virtual void Use() = 0;
  void Drop();
  void Pick(Player* player);
  bool InInventory();
  Player* GetPlayer();
  std::string GetName();
};

#endif
