#include "Map.hpp"

Map::Map() : shapes_(std::vector<MapShape*>()), items_(std::vector<Item*>()) {}

void Map::Render(LevelPos center) {
  // for (MapShape* shape : shapes_) {
  //   shape->Draw(center);
  // }

  // for (Item* item : items_) {
  //   item->Draw(center);
  // }
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
