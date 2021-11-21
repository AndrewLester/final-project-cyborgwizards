#ifndef MAP_ROOM_HPP
#define MAP_ROOM_HPP

#include "MapShape.hpp"

class MapRoom : public MapShape {
 public:
  void Draw(ScreenPos top_left) override;
};

#endif
