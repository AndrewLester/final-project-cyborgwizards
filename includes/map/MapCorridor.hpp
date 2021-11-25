#ifndef MAP_CORRIDOR_HPP
#define MAP_CORRIDOR_HPP

#include "MapShape.hpp"
#include "Event.hpp"

class MapCorridor : public MapShape {
 public:
  MapCorridor(LevelPos position, int width, int height): MapShape(position, width, height) {};
  void Draw(ScreenPos top_left) override;
  void OnNotify(Event event) override;
  std::vector<LevelPos> GetPositions() override;
};

#endif
