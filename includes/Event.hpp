#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

#include <SDL_events.h>

class Entity;

class Event {
 public: 
  Entity* emitter;

 protected:
  const std::string type_;

 public:
  Event(std::string type, Entity* emitter): type_(type), emitter(emitter) {}

  std::string GetType() {
    return this->type_;
  }
};

#endif