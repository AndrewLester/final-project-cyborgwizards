#ifndef PHONE_SYSTEM_HPP
#define PHONE_SYSTEM_HPP

#include "Entity.hpp"
#include "Item.hpp"

class PhoneSystem : public Item {
 private:
  int inventory_idx_ = 1;
 
 public:
  virtual void Draw() = 0;
  virtual void Use() = 0;
  void Interact();
  void OnNotify(Event e);
};

#endif