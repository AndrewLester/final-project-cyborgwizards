#ifndef ITEM_HPP
#define ITEM_HPP

#include "LevelPos.hpp"
#include "Entity.hpp"

class Item : public Entity {
 private:
  int inventory_idx_ = -1;

 public:
  virtual void Draw(ScreenPos top_left) = 0;
  virtual void Use() = 0;
  void Drop();
  void Pick();
  int GetInventoryIdx();
};

#endif
