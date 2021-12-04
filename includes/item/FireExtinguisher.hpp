#ifndef FIRE_EXTINGUISHER_HPP
#define FIRE_EXTINGUISHER_HPP

#include "Entity.hpp"
#include "Item.hpp"
#include "ScreenPos.hpp"

class FireExtinguisher : public Item {
 private:
  int stun_period = 2;
  int stun_buffer = 15;
  int num_uses = 4;
 
 public:
  void Draw(ScreenPos top_left);
  void Use();
};

#endif