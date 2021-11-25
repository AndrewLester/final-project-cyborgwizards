#include "MapRoom.hpp"
#include <iostream>

void MapRoom::Draw(ScreenPos top_left) {
  for (int row = top_left.x; row < width_; row++) {
    for (int col = top_left.y; col < height_; col++) {
      // TCODConsole::root->setChar(row, col, ' ');
    }
  }
}

void MapRoom::OnNotify(Event event) {
  std::cout << event.GetType() << std::endl;
  return;
}

std::vector<LevelPos> MapRoom::GetPositions() {
  std::vector<LevelPos> positions;

  for (int row = position_.x; row < width_; row++) {
    for (int col = position_.y; col < height_; col++) {
      positions.push_back({ row, col, position_.level });
    }
  }
  return positions;
}
