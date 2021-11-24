#include "KeyboardEvent.hpp"

KeyboardEvent::KeyboardEvent(SDL_KeyboardEvent event):
  Event("KeyboardEvent"), key(event.keysym.sym) {}