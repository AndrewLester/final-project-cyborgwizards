#include "Map.hpp"

Map::Map() : shapes_(std::vector<MapShape*>()), items_(std::vector<Item*>()) {}

void Map::Render(Coord center) {
  for (MapShape* shape : shapes_) {
    shape->Draw();
  }

  for (Item* item : items_) {
    item->Draw();
  }
}

Item* Map::GetItem(Coord position) {
  for (Item* item : items_) {
    if (item->GetPosition() == position) {
      return item;
    }
  }
  return nullptr;
}

MapShape* Map::GetMapShape(Coord position) {
  for (MapShape* shape : shapes_) {
    if (shape->ContainsCoord(position)) {
      return shape;
    }
  }
  return nullptr;
}
