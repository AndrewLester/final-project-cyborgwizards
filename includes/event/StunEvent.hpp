#ifndef STUN_EVENT_HPP
#define STUN_EVENT_HPP

#include "Event.hpp"
#include "LevelPos.hpp"

class StunEvent : public Event {
 public:
  StunEvent(Entity* emitter, LevelPos start, LevelPos end, int stun_period);

 public:
  LevelPos start;
  LevelPos end;
  int stun_period_;
};

#endif