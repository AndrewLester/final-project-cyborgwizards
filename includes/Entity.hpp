#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "Coord.hpp"
#include "Event.hpp"
#include "EventListener.hpp"

class Entity {
 protected:
  Coord position_;

 public:
  Entity(Coord init_pos);
  virtual ~Entity();

  void UploadEvent(Event event);
  void RegisterListen(std::string event_type);
  virtual void OnNotify(Event event) = 0;

  Coord GetPosition();

  virtual void Draw(Coord center) = 0;
};

#endif
