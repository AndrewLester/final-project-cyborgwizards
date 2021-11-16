#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include <map>
#include <string>
#include <set>

#include <SDL_events.h>

#include "Event.hpp"

#include "event/HideEvent.hpp"
#include "event/KeyboardEvent.hpp"
#include "event/SoundEvent.hpp"
#include "event/StairsEvent.hpp"


class Entity;

class EventListener {
 private:
  static EventListener* instance_;
  std::map<Entity*, std::set<std::string>> listeners_;

 public:
  EventListener();
  ~EventListener();
  
  void HandleInput(SDL_Event event);

  void BroadcastEvent(Event event);
  void RegisterListener(Entity* listener, std::string event_type);
};

#endif