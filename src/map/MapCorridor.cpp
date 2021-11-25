#include "MapCorridor.hpp"
#include <libtcod.h>
#include <iostream>

void MapCorridor::Draw(ScreenPos top_left) {
  for (int row = top_left.x; row < width_; row++) {
    for (int col = top_left.y; col < height_; col++) {
      // TCODConsole::root->putChar(row, col, ' ');
    }
  }
}

void MapCorridor::OnNotify(Event event) {
  std::cout << event.GetType() << std::endl;
  return;
}

std::vector<LevelPos> MapCorridor::GetPositions() {
  std::vector<LevelPos> positions;

  for (int row = position_.x; row < width_; row++) {
    for (int col = position_.y; col < height_; col++) {
      positions.push_back({ row, col, position_.level });
    }
  }
  return positions;
}
