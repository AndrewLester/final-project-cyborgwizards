#include "MapGenerator.hpp"
#include "MapRoom.hpp"
#include "MapCorridor.hpp"

bool MapGenerator::BspListener::visitNode(TCODBsp* node, void* user_data) {
  std::vector<MapShape*>* shapes = static_cast<std::vector<MapShape*>*>(user_data);
  if (node->isLeaf()) {
    int x, y, w, h;
    TCODRandom* random = TCODRandom::getInstance();
    w = random->getInt(ROOM_MIN_SIZE, node->w-2);
    h = random->getInt(ROOM_MIN_SIZE, node->h-2);
    x = random->getInt(node->x+1, node->x+node->w-w-1);
    y = random->getInt(node->y+1, node->y+node->h-h-1);
    shapes->push_back(generator_->CreateShape(x, y, x + w - 1, y + h - 1, level_, ShapeType::ROOM));

    if (room_num_ != 0 ) {
      shapes->push_back(generator_->CreateShape(last_room_center_x_, last_room_center_y_, x + w / 2, last_room_center_y_, level_, ShapeType::CORRIDOR));
      shapes->push_back(generator_->CreateShape(x + w / 2, last_room_center_y_, x + w / 2, y + h / 2, level_, ShapeType::CORRIDOR));
    }
    last_room_center_x_ = x + w / 2;
    last_room_center_y_ = y + h / 2;
    room_num_++;
  }
  return true;
}

void MapGenerator::RunBspSplit(int width, int height, int level, std::vector<MapShape*>* shapes) {
  TCODBsp bsp(0, 0, width, height);
  bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);
  BspListener listener(this, level);
  bsp.traverseInvertedLevelOrder(&listener, shapes);
}

Map* MapGenerator::Generate(int width, int height, int level) {
  std::vector<MapShape*> shapes;
  Map* map = new Map(width, height);
  TCODMap* tcod_map = map->GetMap();

  for (int row = 0; row < width; row++) {
    for (int col = 0; col < height; col++) {
      tcod_map->setProperties(row, col, false, false);
      // TCODConsole::root->setChar(row, col, '#');
    }
  }

  RunBspSplit(width, height, level, &shapes);

  map->SetShapes(shapes);

  for (MapShape* shape : shapes) {
    for (LevelPos position : shape->GetPositions()) {
      tcod_map->setProperties(position.x, position.y, false, true);
    }
  }

  return map;
}

MapShape* MapGenerator::CreateShape(int x1, int y1, int x2, int y2, int level, ShapeType type) {
  if (x2 < x1) {
       int tmp=x2;
       x2=x1;
       x1=tmp;
   }
   if (y2 < y1) {
       int tmp=y2;
       y2=y1;
       y1=tmp;
   }

  switch (type) {
    case ShapeType::ROOM:
      return new MapRoom({ x1, y1, level }, x2 - x1, y2 - y1);
    case ShapeType::CORRIDOR:
      return new MapCorridor({ x1, y1, level }, x2 - x1, y2 - y1);
    default:
      return nullptr;
  }
}
