#ifndef SOUND_EVENT_HPP
#define SOUND_EVENT_HPP

#include "Event.hpp"
#include "LevelPos.hpp"

enum Direction {
  North,
  South,
  East,
  West
};

class SoundEvent : public Event {
 public:
  LevelPos source;
  int intensity;

 public:
  SoundEvent(Entity* emitter, LevelPos source, int intensity);
  
  int RelativeIntensity(LevelPos position);
  Direction RelativeDirection(LevelPos position);
};

#endif