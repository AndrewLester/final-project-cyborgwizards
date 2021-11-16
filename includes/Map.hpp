#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "MapShape.hpp"
#include "MapInteractive.hpp"
#include "Item.hpp"

class Map {
 private:
  std::vector<MapShape*> shapes_;
  std::vector<Item*> items_;

 public:
  Map();
  ~Map();

  void Render(Coord center);
  bool IsReachable(Coord position);
  Item* GetItem(Coord position);
  MapInteractive* GetMapInteractive(Coord position);
}

#endif