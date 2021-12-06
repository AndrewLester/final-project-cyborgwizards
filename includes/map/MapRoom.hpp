#ifndef MAP_ROOM_HPP
#define MAP_ROOM_HPP

#include <iostream>

#include "Event.hpp"
#include "MapShape.hpp"

class MapRoom : public MapShape {
 public:
  MapRoom(LevelPos position, int width, int height) : MapShape(position, width, height){};
  void Draw(ScreenPos top_left, tcod::Console& console) override;
  void OnNotify(Event event) override;
  std::vector<LevelPos> GetPositions() override;
};

#endif
