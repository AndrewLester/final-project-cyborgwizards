#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <libtcod.h>

#include "Event.hpp"
#include "EventListener.hpp"
#include "LevelPos.hpp"
#include "ScreenPos.hpp"

class Entity {
 protected:
  LevelPos position_;  // top_left
  int width_;
  int height_;

 public:
  Entity(LevelPos init_pos, int width, int height);
  virtual ~Entity();

  void UploadEvent(Event event);
  void RegisterListen(std::string event_type);
  virtual void OnNotify(Event event) = 0;

  LevelPos GetPosition();
  LevelPos GetCenterPosition();

  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  virtual void Draw(ScreenPos top_left) = 0;
};

#endif
