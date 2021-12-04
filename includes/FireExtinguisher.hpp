#ifndef FIRE_EXTINGUISHER_HPP
#define FIRE_EXTINGUISHER_HPP

#include "Entity.hpp"
#include "Item.hpp"

class FireExtinguisher : public Item {
 private:
  int inventory_idx_ = 0;
 
 public:
  virtual void Draw() = 0;
  virtual void Use() = 0;
  void Interact();
  void OnNotify(Event e);
};

#endif