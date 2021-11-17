#include "EventListener.hpp"

EventListener::EventListener() {}

EventListener::~EventListener() {}

void EventListener::HandleInput(SDL_Event event) {
  // TODO: Add handling different input types
}

void EventListener::BroadcastEvent(Event event) {
  std::string event_type = event.GetType();
  for (auto it = this->listeners_.begin(); it != this->listeners_.end(); it++) {
    if (it->second.find(event_type) != it->second.end()) {
      it->first->OnNotify(event);
    }
  }
}

void EventListener::RegisterListener(Entity* listener, std::string event_type) {
  if (this->listeners_.find(listener) != this->listeners_.end()) {
    this->listeners_.at(listener).insert(event_type);
  } else {
    this->listeners_.insert({listener, {event_type}});
  }
}