#include "Map.hpp"

Map::Map(int width, int height, std::vector<MapShape*> shapes) : shapes_(shapes), items_(std::vector<Item*>()) {
  map_ = std::make_unique<TCODMap>(TCODMap(width, height));
}

Map::~Map() {
  for (MapShape* shape : shapes_) {
    delete shape;
  }
}

void Map::Render(Coord center) {
  for (MapShape* shape : shapes_) {
    shape->Draw(center);
  }

  for (Item* item : items_) {
    item->Draw(center);
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
