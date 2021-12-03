#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "LevelPos.hpp"
#include "ScreenPos.hpp"
#include "Event.hpp"
#include "EventListener.hpp"

class Entity {
 protected:
  LevelPos position_; // top_left
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

  virtual void Draw(ScreenPos top_left) = 0;
};

#endif
