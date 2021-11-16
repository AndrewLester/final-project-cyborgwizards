#ifndef HIDE_EVENT_HPP
#define HIDE_EVENT_HPP

#include "Event.hpp"

enum HideAction {
  Hide,
  Leave
};

class HideEvent : public Event {
 public:
  Entity* hide_entity;
  HideAction action;
 
 public:
  HideEvent(Entity* emitter, Entity* hide_entity, HideAction action);
};

#endif