#ifndef EVENT_LISTENER_HPP
#define EVENT_LISTENER_HPP

#include <SDL_events.h>

#include <map>
#include <set>
#include <string>

#include "Entity.hpp"
#include "Event.hpp"
#include "HideEvent.hpp"
#include "KeyboardEvent.hpp"
#include "SoundEvent.hpp"
#include "StairsEvent.hpp"

class EventListener {
 private:
  std::map<Entity*, std::set<std::string>> listeners_;

 public:
  EventListener();
  ~EventListener();

  static EventListener& Instance() {
    static EventListener* instance = new EventListener();
    return *instance;
  }

  void HandleInput(SDL_Event event);

  void BroadcastEvent(Event* event);
  void RegisterListener(Entity* listener, std::string event_type);
};

#endif
