#include "Map.hpp"

Map::Map(int width, int height, std::vector<MapShape*> shapes) : shapes_(shapes), items_(std::vector<Item*>()) {
  map_ = std::make_unique<TCODMap>(TCODMap(width, height));
}

Map::~Map() {
  for (MapShape* shape : shapes_) {
    delete shape;
  }
}

void Map::Render(LevelPos center) {
  ScreenPos screen_center = {60, 60}; // TODO: relate this to UI initialization
  for (MapShape* shape : shapes_) {
    LevelPos shape_pos = shape->GetPosition();
    if (shape_pos.level == center.level) {
      LevelPos relative_pos = shape_pos - center;
      shape->Draw({screen_center.x + relative_pos.x, screen_center.y + relative_pos.y});
    }
  }

  for (Item* item : items_) {
    LevelPos item_pos = item->GetPosition();
    if (item_pos.level == center.level) {
      LevelPos relative_pos = item_pos - center;
      item->Draw({screen_center.x + relative_pos.x, screen_center.y + relative_pos.y});
    }
  }
}

Item* Map::GetItem(LevelPos position) {
  for (Item* item : items_) {
    if (item->GetPosition() == position) {
      return item;
    }
  }
  return nullptr;
}

MapShape* Map::GetMapShape(LevelPos position) {
  for (MapShape* shape : shapes_) {
    if (shape->ContainsLevelPos(position)) {
      return shape;
    }
  }
  return nullptr;
}
