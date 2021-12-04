#ifndef HAZMAT_SUIT_HPP
#define HAZMAT_SUIT_HPP

#include "Entity.hpp"
#include "Item.hpp"

class HazmatSuit : public Item {
 private:
  int inventory_idx_ = 3;
 
 public:
  virtual void Draw() = 0;
  virtual void Use() = 0;
  void Interact();
  void OnNotify(Event e);
};

#endif