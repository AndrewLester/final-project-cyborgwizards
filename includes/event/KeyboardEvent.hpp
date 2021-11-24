#ifndef KEYBOARD_EVENT_HPP
#define KEYBOARD_EVENT_HPP

#include "Event.hpp"

typedef SDL_Keycode KeyType;

class KeyboardEvent : public Event {
 public:
  KeyType key;

 public:
  KeyboardEvent(SDL_KeyboardEvent keyboard_event);
};

#endif