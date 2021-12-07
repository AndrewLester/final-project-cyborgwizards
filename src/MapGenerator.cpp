#include "MapGenerator.hpp"

#include <iostream>

#include "MapCorridor.hpp"
#include "MapRoom.hpp"

void AddEdge(AdjacentList* relations, MapShape* s1, MapShape* s2) {
  if (relations->find(s1) == relations->end()) {
    relations->insert({s1, {}});
  }
  relations->at(s1).push_back(s2);
  if (relations->find(s2) == relations->end()) {
    relations->insert({s2, {}});
  }
  relations->at(s2).push_back(s1);
}

bool MapGenerator::BspListener::visitNode(TCODBsp* node, void* user_data) {
  auto* data = static_cast<std::pair<std::vector<MapShape*>*, AdjacentList*>*>(user_data);
  auto* shapes = data->first;
  auto* relations = data->second;

  if (node->isLeaf()) {
    int x, y, w, h;
    TCODRandom* random = TCODRandom::getInstance();
    w = random->getInt(ROOM_MIN_SIZE, node->w - 2);
    h = random->getInt(ROOM_MIN_SIZE, node->h - 2);
    x = random->getInt(node->x + 1, node->x + node->w - w - 1);
    y = random->getInt(node->y + 1, node->y + node->h - h - 1);
    MapRoom* new_room =
        static_cast<MapRoom*>(generator_->CreateShape(x, y, x + w - 1, y + h - 1, level_, room_num_, ShapeType::ROOM));

    shapes->push_back(new_room);

    if (room_num_ != 0) {
      int last_room_center_x = this->last_room_->GetCenterPosition().x;
      int last_room_center_y = this->last_room_->GetCenterPosition().y;
      int new_room_center_x = new_room->GetCenterPosition().x;
      int new_room_center_y = new_room->GetCenterPosition().y;

      MapCorridor* c1 = static_cast<MapCorridor*>(generator_->CreateShape(
          last_room_center_x, last_room_center_y, new_room_center_x, last_room_center_y, level_, room_num_, ShapeType::CORRIDOR));
      MapCorridor* c2 = static_cast<MapCorridor*>(generator_->CreateShape(
          new_room_center_x, last_room_center_y, new_room_center_x, new_room_center_y, level_, room_num_, ShapeType::CORRIDOR));
      shapes->push_back(c1);
      shapes->push_back(c2);

      AddEdge(relations, last_room_, c1);
      AddEdge(relations, c1, c2);
      AddEdge(relations, c2, new_room);

      std::cout << last_room_->GetCenterPosition().ToString() << ", "
                << c1->GetCenterPosition().ToString() << ", "
                << c2->GetCenterPosition().ToString() << ", "
                << new_room->GetCenterPosition().ToString()  << std::endl;
    }
    last_room_ = new_room;
    room_num_++;
  }
  return true;
}

void MapGenerator::RunBspSplit(
    int width, int height, int level, std::pair<std::vector<MapShape*>*, AdjacentList*>* data) {
  TCODBsp bsp(0, 0, width, height);
  bsp.splitRecursive(NULL, 5, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
  BspListener listener(this, level);
  bsp.traverseInvertedLevelOrder(&listener, data);
}

Map* MapGenerator::Generate(int width, int height, int level) {
  std::vector<MapShape*> shapes;
  AdjacentList relations;
  std::pair<std::vector<MapShape*>*, AdjacentList*> data = {&shapes, &relations};
  Map* map = new Map(width, height);

  TCODMap* tcod_map = map->GetMap();

  for (int row = 0; row < width; row++) {
    for (int col = 0; col < height; col++) {
      tcod_map->setProperties(row, col, false, false);
    }
  }
  RunBspSplit(width, height, level, &data);
  map->SetShapes(shapes);
  map->SetRelations(relations);

  for (MapShape* shape : shapes) {
    shape->SetMap(tcod_map);
    for (LevelPos position : shape->GetPositions()) {
      tcod_map->setProperties(position.x, position.y, true, true);
    }
  }

  return map;
}

MapShape* MapGenerator::CreateShape(int x1, int y1, int x2, int y2, int level, int room_num, ShapeType type) {
  if (x2 < x1) {
    int tmp = x2;
    x2 = x1;
    x1 = tmp;
  }
  if (y2 < y1) {
    int tmp = y2;
    y2 = y1;
    y1 = tmp;
  }
  // std::cout << "Creating shape: POS=(" << x1 << ", " << y1 << ")  WIDTH=(" << (x2 - x1 + 1) << ")  HEIGHT=("
  //           << (y2 - y1 + 1) << ")" << std::endl;

  switch (type) {
    case ShapeType::ROOM:
      return new MapRoom({x1, y1, level}, x2 - x1 + 1, y2 - y1 + 1, room_num);
    case ShapeType::CORRIDOR:
      return new MapCorridor({x1, y1, level}, x2 - x1 + 1, y2 - y1 + 1);
    default:
      return nullptr;
  }
}
