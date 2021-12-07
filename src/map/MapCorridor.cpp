#include "MapCorridor.hpp"

#include "RenderEngine.hpp"

#include <iostream>

void MapCorridor::Draw(ScreenPos top_left) {
  for (int row = 0; row < width_; row++) {
    for (int col = 0; col < height_; col++) {
      ScreenPos offset = {row, col};
      RenderEngine::Instance().DrawRect(top_left + offset, 1, 1, ' ', TCOD_black, TCOD_black);
    }
  }
}

void MapCorridor::OnNotify(Event* event) {
  std::cout << event->GetType() << std::endl;
  return;
}

std::vector<LevelPos> MapCorridor::GetPositions() {
  std::vector<LevelPos> positions;

  for (int row = 0; row < width_; row++) {
    for (int col = 0; col < height_; col++) {
      positions.push_back({position_.x + row, position_.y + col, position_.level});
    }
  }
  return positions;
}
