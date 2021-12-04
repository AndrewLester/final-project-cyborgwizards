#include "KeyboardEvent.hpp"

KeyboardEvent::KeyboardEvent(SDL_KeyboardEvent event):
  Event("KeyboardEvent", nullptr), key(event.keysym.sym) {
  this->shift = event.keysym.mod | 1;
  this->ctrl = event.keysym.mod | 64;
  this->keyup = event.type == SDL_KEYUP; // guaranteed only KEYUP and KEYDOWN
}