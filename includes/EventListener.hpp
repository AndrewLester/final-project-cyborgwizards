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

class Entity {
 public:
  virtual void OnNotify(Event event);
};

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

  void BroadcastEvent(Event event);
  void RegisterListener(Entity* listener, std::string event_type);
};

#endif