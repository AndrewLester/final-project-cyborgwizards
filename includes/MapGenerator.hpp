#include "Map.hpp"
#include <memory>
#include <libtcod.h>

class MapGenerator {
private:
  static const int ROOM_MAX_SIZE = 12;
  static const int ROOM_MIN_SIZE = 6;
  std::unique_ptr<TCODRandom> random_;
  bool default_random_;

  MapShape* CreateShape(int x1, int y1, int x2, int y2, int level, ShapeType type);
  void RunBspSplit(int width, int height, int level, std::vector<MapShape*>* shapes);

  class BspListener : public ITCODBspCallback {
  private:
    MapGenerator* generator_;
    int level_;
    int room_num_;
    int last_room_center_x_;
    int last_room_center_y_;
  public:
    BspListener(MapGenerator* generator, int level) : generator_(generator), level_(level), room_num_(0), last_room_center_x_(0), last_room_center_y_(0) {};
    bool visitNode(TCODBsp *node, void *userData);
  };
public:
  MapGenerator();
  MapGenerator(std::unique_ptr<TCODRandom> random);
  Map* Generate(int width, int height, int level);
  const std::unique_ptr<TCODRandom>& GetRandom() const;
};
