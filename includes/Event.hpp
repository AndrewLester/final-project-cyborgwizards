#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL_events.h>

#include <string>

class Entity;

class Event {
 public:
  Entity* emitter_;

 protected:
  const std::string type_;

 public:
  Event(std::string type, Entity* emitter) : emitter_(emitter), type_(type) {}

  std::string GetType() { return this->type_; }
};

#endif
