#include "SoundEvent.hpp"

SoundEvent::SoundEvent(Entity* emitter, LevelPos source, int intensity):
  Event("SoundEvent", emitter), source(source), intensity(intensity) {}

int SoundEvent::RelativeIntensity(LevelPos position) {
  LevelPos diff = position - source;
  double raw_intensity = sqrt(sqr(diff.x) + sqr(diff.y) + sqr(diff.level * kLevelHeight)) / this->intensity;
  if (raw_intensity > kThreshold) return 0;
  return static_cast<int>((kThreshold - raw_intensity) / kThreshold * 100);
}

Direction SoundEvent::RelativeDirection(LevelPos position) {
  LevelPos diff = position - source;
  if (diff.x > 0 && diff.y > 0) { // top left
    return Direction::Northwest;
  }
  if (diff.x > 0 && diff.y < 0) { // top right
    return Direction::Northeast;
  }
  if (diff.x < 0 && diff.y > 0) {
    return Direction::Southwest;
  }
  return Direction::Southeast;
}