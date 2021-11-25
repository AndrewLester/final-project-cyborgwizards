#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "Item.hpp"
#include "MapShape.hpp"
#include <libtcod/fov.hpp>

class Map {
 private:
  std::vector<MapShape*> shapes_;
  std::vector<Item*> items_;
  TCODMap* map_;

 public:
  Map(int width, int height);
  ~Map();

  void Render(LevelPos center);
  bool IsReachable(LevelPos position);
  void AddItem(Item* item);
  void SetShapes(std::vector<MapShape*> shapes_);
  Item* GetItem(LevelPos position);
  MapShape* GetMapShape(LevelPos position);
  TCODMap* GetMap();
};

#endif
