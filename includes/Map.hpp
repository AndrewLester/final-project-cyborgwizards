#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "Item.hpp"
#include "MapShape.hpp"
#include <memory>
#include <libtcod.h>

class Map {
 private:
  std::vector<MapShape*> shapes_;
  std::vector<Item*> items_;
  std::unique_ptr<TCODMap> map_;

 public:
  Map(int width, int height, std::vector<MapShape*> shapes_);
  ~Map();

  void Render(Coord center);
  bool IsReachable(Coord position);
  void AddItem(Item* item);
  Item* GetItem(Coord position);
  MapShape* GetMapShape(Coord position);
};

#endif
