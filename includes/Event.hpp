#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

#include <SDL_events.h>

class Entity;

class Event {
 public: 
  Entity* emitter;
  const std::string kType = "BaseEvent";

 public:
  Event(Entity* emitter): emitter(emitter) {}
};

#endif