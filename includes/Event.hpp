#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

#include <SDL_events.h>

class Entity;

class Event {
 public: 
  Entity* emitter;

 public:
  Event(Entity* emitter): emitter(emitter) {}

  virtual std::string GetType() {
    return "BaseEvent";
  }
};

#endif