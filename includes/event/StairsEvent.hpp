#ifndef STAIRS_EVENT_HPP
#define STAIRS_EVENT_HPP

#include "Event.hpp"

class StairsEvent : public Event {
 public:
  StairsEvent(Entity* entity);
};

#endif