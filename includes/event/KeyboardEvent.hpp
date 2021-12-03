#ifndef KEYBOARD_EVENT_HPP
#define KEYBOARD_EVENT_HPP

#include "Event.hpp"

typedef SDL_Keycode KeyType;

class KeyboardEvent : public Event {
 public:
  KeyType key;
  bool shift;
  bool ctrl;

 public:
  KeyboardEvent(SDL_KeyboardEvent keyboard_event);
};

#endif