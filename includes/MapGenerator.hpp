#include "Map.hpp"
#include <memory>
#include <libtcod.h>

class MapGenerator {
private:
  static const int ROOM_MAX_SIZE = 12;
  static const int ROOM_MIN_SIZE = 6;

  MapShape* CreateShape(int x1, int y1, int x2, int y2, int level, ShapeType type);
  void RunBspSplit(int width, int height, int level, std::pair<std::vector<MapShape*>*, AdjacentList*>* shapes);

  class BspListener : public ITCODBspCallback {
  private:
    MapGenerator* generator_;
    int level_;
    int room_num_;
    MapRoom* last_room_;
  public:
    BspListener(MapGenerator* generator, int level) : generator_(generator), level_(level), room_num_(0), last_room_(nullptr) {};
    bool visitNode(TCODBsp *node, void *userData);
  };
public:
  Map* Generate(int width, int height, int level);
};
