#ifndef SOUND_EVENT_HPP
#define SOUND_EVENT_HPP

#include "Event.hpp"
#include "Coord.hpp"

enum Direction {
  N,
  S,
  E,
  W,
  NW,
  NE,
  SW,
  SE
};

class SoundEvent : public Event {
 public:
  Coord source;
  int intensity;

 public:
  SoundEvent(Entity* emitter, Coord source, int intensity);
  std::string GetType() {
    return "SoundEvent";
  }
  
  int RelativeIntensity(Coord position);
  Direction RelativeDirection(Coord position);
};

#endif