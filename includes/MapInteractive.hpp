#ifndef MAP_INTERACTIVE_HPP
#define MAP_INTERACTIVE_HPP

#include "MapShape.hpp"

class MapInteractive : public MapShape {
 public:
  virtual void Draw() = 0;
  virtual void OnNotify(Event* event) = 0;
};

#endif
