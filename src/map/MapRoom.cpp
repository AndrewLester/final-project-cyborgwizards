#include "MapRoom.hpp"

#include <iostream>

#include "RenderEngine.hpp"

int MapRoom::GetRoomNumber() const { return room_num_; }

void MapRoom::Draw(ScreenPos top_left) {
  for (int row = 0; row < width_; row++) {
    for (int col = 0; col < height_; col++) {
      ScreenPos offset = {row, col};
      RenderEngine::Instance().DrawRect(top_left + offset, 1, 1, ' ', TCOD_black, TCOD_black);
    }
  }
}

void MapRoom::OnNotify(Event* event) {
  std::cout << event->GetType() << std::endl;
  return;
}

std::vector<LevelPos> MapRoom::GetPositions() {
  std::vector<LevelPos> positions;

  for (int row = 0; row < width_; row++) {
    for (int col = 0; col < height_; col++) {
      positions.push_back({position_.x + row, position_.y + col, position_.level});
    }
  }
  return positions;
}
