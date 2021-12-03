#include "Map.hpp"
#include <math.h>

Map::Map(int width, int height) : items_(std::vector<Item*>()), width_(width), height_(height) {
  map_ = new TCODMap(width, height);
}

Map::~Map() {
  for (MapShape* shape : shapes_) {
    delete shape;
  }
  delete map_;
}

TCODMap* Map::GetMap() { return map_; }

void Map::SetShapes(std::vector<MapShape*> shapes) {
  shapes_ = shapes;
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

MapRoom* Map::GetRoom(LevelPos position) {
  for (MapShape* shape : shapes_) {
    if(MapRoom* room = dynamic_cast<MapRoom*>(shape)) {
      if (room->ContainsLevelPos(position)) {
        return room;
      }
    }
  }
  return nullptr;
}

std::vector<MapCorridor*> Map::GetCorridors() {
  std::vector<MapCorridor*> corridors;

  for (auto* shape : shapes_) {
    if (MapCorridor* corridor = dynamic_cast<MapCorridor*>(shape)) {
      corridors.push_back(corridor);
    }
  }

  return corridors;
}

std::vector<MapRoom*> Map::GetRooms() {
  std::vector<MapRoom*> corridors;

  for (auto* shape : shapes_) {
    if (MapRoom* corridor = dynamic_cast<MapRoom*>(shape)) {
      corridors.push_back(corridor);
    }
  }

  return corridors;
}

bool Map::IsReachable(LevelPos position) {
  return position.x >= 0 && position.x < width_ && position.y > 0 && position.y < height_;
}


std::vector<double> GetRingAngles(int radius) {
  std::vector<double> angles;
  if (radius <= 1) {
    return angles;
  }

  for (int i = radius; i > 1; i--) {
    double initital_angle = M_PI_2 / i;
    angles.push_back(initital_angle);
    angles.push_back(M_PI_2 - initital_angle);
  }

  return angles;
}

void GetRingPositions(LevelPos center, int radius, std::vector<LevelPos>& positions) {
  if (radius == 1) {
    positions.push_back(center);
    return;
  }

  std::vector<double> angles = GetRingAngles(radius);

  std::vector<double> angles_copy = angles;
  for (double angle : angles_copy) {
    angles.push_back(M_PI_2 + angle);
    angles.push_back(M_PI + angle);
    angles.push_back(((3 / 2) * M_PI) + angle);
  }

  for (double angle : angles) {
    double x = cos(angle) * radius;
    double y = sin(angle) * radius;
    positions.push_back({ static_cast<int>(round(x)), static_cast<int>(round(y)), center.level });
  }

  GetRingPositions(center, radius - 1, positions);
}

std::vector<LevelPos> GetCirclePositions(LevelPos center, int radius) {
  std::vector<LevelPos> positions;
  GetRingPositions(center, radius, positions);
  return positions;
}

std::vector<MapRoom*> Map::GetRoomsInRadius(LevelPos position, int radius) {
  std::vector<MapRoom*> rooms;
  for (LevelPos pos : GetCirclePositions(position, radius)) {
    for (MapRoom* room : GetRooms()) {
      if (room->ContainsLevelPos(pos)) {
        rooms.push_back(room);
      }
    }
  }
  return rooms;
}
