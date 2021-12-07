#include <libtcod.h>

#include <memory>

#include "Map.hpp"

class MapGenerator {
 private:
  static const int ROOM_MAX_SIZE = 12;
  static const int ROOM_MIN_SIZE = 6;

  MapShape* CreateShape(int x1, int y1, int x2, int y2, int level, int number, ShapeType type);
  void RunBspSplit(
      int width, int height, int level, std::pair<std::vector<MapShape*>*, AdjacentList*>* shapes, TCODRandom* random);

  class BspListener : public ITCODBspCallback {
   private:
    MapGenerator* generator_;
    int level_;
    int room_num_;
    MapRoom* last_room_;
    TCODRandom* random_;

   public:
    BspListener(MapGenerator* generator, int level, TCODRandom* random)
        : generator_(generator), level_(level), random_(random), room_num_(0), last_room_(nullptr) {
      if (random_ == NULL) {
        random_ = TCODRandom::getInstance();
      }
    };
    bool visitNode(TCODBsp* node, void* userData);
  };

 public:
  Map* Generate(int width, int height, int level, TCODRandom* seed = NULL);
};
