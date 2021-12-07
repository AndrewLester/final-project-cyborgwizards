#include "Map.hpp"
#define _USE_MATH_DEFINES
#include <libtcod.h>
#include <math.h>

#include <iostream>
#include <stdexcept>

#include "RenderEngine.hpp"

Map::Map(int width, int height) : items_(std::vector<Item*>()), width_(width), height_(height) {
  map_ = new TCODMap(width, height);
}

Map::~Map() {
  for (MapShape* shape : shapes_) {
    delete shape;
  }
  for (Item* item : items_) {
    delete item;
  }
  delete map_;
}

TCODMap* Map::GetMap() { return map_; }

int Map::GetWidth() const { return width_; }
int Map::GetHeight() const { return height_; }

LevelPos Map::GetSpawnLocation(int idx) const {
  std::vector<MapRoom*> rooms = GetRooms();
  int room_num = (idx < 0) ? rooms.size() + idx : idx;
  for (MapRoom* room : rooms) {
    if (room->GetRoomNumber() == room_num) {
      return room->GetCenterPosition();
    }
  }
  return {0, 0, 1};
}

LevelPos Map::GetRandomLocation() const {
  LevelPos ret = this->GetSpawnLocation(rand() % this->GetRooms().size());
  return ret;
}

void Map::AddItem(Item* item) { items_.push_back(item); }

void Map::SetShapes(std::vector<MapShape*> shapes) { shapes_ = shapes; }

void Map::SetRelations(AdjacentList relations) { this->relations_ = relations; }

void Map::Render(LevelPos center, ScreenPos screen_center) {
  map_->computeFov(center.x, center.y, 20, true);
  for (int row = 0; row < width_; row++) {
    for (int col = 0; col < height_; col++) {
      LevelPos map_pos = {row, col};
      LevelPos relative_pos = map_pos - center;
      ScreenPos relative_pos_screen = {relative_pos.x, relative_pos.y};
      if (map_->isInFov(row, col))
        RenderEngine::Instance().DrawRect(screen_center + relative_pos_screen, 1, 1, '#', TCOD_gray, TCOD_gray);
      // tcod::draw_rect(
      //     console,
      //     {screen_center.x + relative_pos.x, screen_center.y + relative_pos.y, 1, 1},
      //     '#',
      //     TCOD_gray,
      //     TCOD_gray);
    }
  }

  for (MapShape* shape : shapes_) {
    LevelPos shape_pos = shape->GetPosition();
    if (shape_pos.level == center.level) {
      LevelPos relative_pos = shape_pos - center;
      shape->Draw({screen_center.x + relative_pos.x, screen_center.y + relative_pos.y});
    }
  }

  // for (Item* item : items_) {
  //   LevelPos item_pos = item->GetPosition();
  //   if (item_pos.level == center.level) {
  //     LevelPos relative_pos = item_pos - center;
  //     item->Draw({screen_center.x + relative_pos.x, screen_center.y + relative_pos.y}, console);
  //   }
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

MapRoom* Map::GetRoom(LevelPos position) {
  for (MapShape* shape : shapes_) {
    if (MapRoom* room = dynamic_cast<MapRoom*>(shape)) {
      if (room->ContainsLevelPos(position)) {
        return room;
      }
    }
  }
  return nullptr;
}

std::vector<MapCorridor*> Map::GetCorridors() const {
  std::vector<MapCorridor*> corridors;

  for (auto* shape : shapes_) {
    if (MapCorridor* corridor = dynamic_cast<MapCorridor*>(shape)) {
      corridors.push_back(corridor);
    }
  }

  return corridors;
}

std::vector<MapRoom*> Map::GetRooms() const {
  std::vector<MapRoom*> corridors;

  for (auto* shape : shapes_) {
    if (MapRoom* corridor = dynamic_cast<MapRoom*>(shape)) {
      corridors.push_back(corridor);
    }
  }

  return corridors;
}

bool Map::IsReachable(LevelPos position) {
  // return position.x >= 0 && position.x < width_ && position.y > 0 && position.y < height_;
  return this->map_->isWalkable(position.x, position.y);
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
    positions.push_back({static_cast<int>(round(x)), static_cast<int>(round(y)), center.level});
  }

  GetRingPositions(center, radius - 1, positions);
}

std::vector<LevelPos> GetCirclePositions(LevelPos center, int radius) {
  std::vector<LevelPos> positions;
  GetRingPositions(center, radius, positions);
  return positions;
}

std::vector<MapRoom*> Map::GetRoomsInRadius(LevelPos position, int radius) {
  if (position.x < 0 || position.x > width_ - 1 || position.y < 0 || position.y > height_ - 1) {
    throw std::invalid_argument("Invalid position");
  }

  if (radius < 0) {
    throw std::invalid_argument("Invalid radius");
  }

  std::vector<MapRoom*> rooms;
  for (LevelPos pos : GetCirclePositions(position, radius)) {
    for (MapRoom* room : GetRooms()) {
      if (room->ContainsLevelPos(pos) && std::find(rooms.begin(), rooms.end(), room) != rooms.end()) {
        rooms.push_back(room);
      }
    }
  }
  return rooms;
}

AdjacentList& Map::GetRelations() { return this->relations_; }

std::ostream& operator<<(std::ostream& os, const Map& map) {
  char** grid = new char*[map.GetWidth()];
  for (int i = 0; i < map.GetWidth(); i++) {
    grid[i] = new char[map.GetHeight()];
  }

  for (int i = 0; i < map.GetWidth(); i++) {
    for (int j = 0; j < map.GetHeight(); j++) {
      grid[i][j] = '#';
    }
  }

  for (auto* room : map.GetRooms()) {
    for (auto pos : room->GetPositions()) {
      grid[pos.x][pos.y] = 'R';
    }
  }

  for (auto* corridor : map.GetCorridors()) {
    for (auto pos : corridor->GetPositions()) {
      grid[pos.x][pos.y] = 'C';
    }
  }

  for (int i = 0; i < map.GetWidth(); i++) {
    for (int j = 0; j < map.GetHeight(); j++) {
      os << grid[i][j];
    }
    os << std::endl;
  }

  for (int i = 0; i < map.GetWidth(); i++) {
    delete[] grid[i];
  }
  delete[] grid;
  return os;
}
