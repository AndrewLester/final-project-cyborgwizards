#ifndef MAP_ROOM_HPP
#define MAP_ROOM_HPP

#include "MapShape.hpp"
#include "Event.hpp"

class MapRoom : public MapShape {
 public:
  MapRoom(LevelPos position, int width, int height): MapShape(position, width, height) {};
  void Draw(ScreenPos top_left) override;
  void OnNotify(Event event) override;
  std::vector<LevelPos> GetPositions() override;
};

#endif
