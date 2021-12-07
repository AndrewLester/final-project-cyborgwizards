#ifndef MAP_ROOM_HPP
#define MAP_ROOM_HPP

#include <iostream>

#include "Event.hpp"
#include "MapShape.hpp"

class MapRoom : public MapShape {
 private:
  int room_num_;
 public:
  MapRoom(LevelPos position, int width, int height, int room_num) : MapShape(position, width, height), room_num_(room_num){};
  void Draw(ScreenPos top_left) override;
  void OnNotify(Event event) override;
  std::vector<LevelPos> GetPositions() override;
  int GetRoomNumber() const;
};

#endif
