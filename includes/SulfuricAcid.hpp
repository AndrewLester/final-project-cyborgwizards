#ifndef SULFURIC_ACID_HPP
#define SULFURIC_ACID_HPP

#include "Entity.hpp"
#include "Item.hpp"

class SulfuricAcid : public Item {
 private:
  int inventory_idx_ = 2;
 
 public:
  virtual void Draw() = 0;
  virtual void Use() = 0;
  void Interact();
  void OnNotify(Event e);
};

#endif