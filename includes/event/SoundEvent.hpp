#ifndef SOUND_EVENT_HPP
#define SOUND_EVENT_HPP

#include "Event.hpp"
#include "Coord.hpp"

enum Direction {
  North,
  South,
  East,
  West
};

class SoundEvent : public Event {
 public:
  Coord source;
  int intensity;

 public:
  SoundEvent(Entity* emitter, Coord source, int intensity);
  
  int RelativeIntensity(Coord position);
  Direction RelativeDirection(Coord position);
};

#endif