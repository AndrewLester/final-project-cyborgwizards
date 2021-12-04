#ifndef SOUND_EVENT_HPP
#define SOUND_EVENT_HPP

#include "Event.hpp"
#include "LevelPos.hpp"

enum Direction {
  Northwest,
  Southwest,
  Northeast,
  Southeast
};

class SoundEvent : public Event {
 public:
  static const int kThreshold = 200;
  static const int kLevelHeight = 10;

  LevelPos source;
  int intensity;

 public:
  SoundEvent(Entity* emitter, LevelPos source, int intensity);
  
  int RelativeIntensity(LevelPos position);
  Direction RelativeDirection(LevelPos position);
};

#endif