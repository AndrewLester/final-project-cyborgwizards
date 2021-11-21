#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL_events.h>

#include <string>

class Entity;

class Event {
 public:
  Entity* emitter;

 protected:
  const std::string type_;

 public:
  Event(std::string type, Entity* emitter) : type_(type), emitter(emitter) {}

  std::string GetType() { return this->type_; }
};

#endif
