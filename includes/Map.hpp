#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "Item.hpp"
#include "MapShape.hpp"

class Map {
 private:
  std::vector<MapShape*> shapes_;
  std::vector<Item*> items_;

 public:
  Map();
  ~Map();

  void Render(LevelPos center);
  bool IsReachable(LevelPos position);
  Item* GetItem(LevelPos position);
  MapShape* GetMapShape(LevelPos position);
};

#endif
