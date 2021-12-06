#ifndef FIRE_EXTINGUISHER_HPP
#define FIRE_EXTINGUISHER_HPP

#include "Entity.hpp"
#include "Item.hpp"
#include "ScreenPos.hpp"
#include "RenderEngine.hpp"

class FireExtinguisher : public Item {
 private:
  int stun_period_ = 2;
  int stun_buffer_ = 15;
  int num_uses_ = 4;
 
 public:
  FireExtinguisher(LevelPos pos);
  void Draw(ScreenPos top_left);
  void Use();
};

#endif