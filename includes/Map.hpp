#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <map>

#include "MapShape.hpp"
#include "MapRoom.hpp"
#include "MapCorridor.hpp"
#include "Item.hpp"
#include <libtcod/fov.hpp>

typedef std::map<MapRoom*, std::map<MapRoom*, std::pair<MapCorridor*, MapCorridor*>>> AdjacentList;
class Map {
 private:
  std::vector<MapShape*> shapes_;
  AdjacentList relations_;
  std::vector<Item*> items_;
  TCODMap* map_;
  std::map<MapRoom*, std::map<MapRoom*, std::pair<MapCorridor*, MapCorridor*>>> relations_;

 public:
  Map(int width, int height);
  ~Map();

  void Render(LevelPos center);
  bool IsReachable(LevelPos position);
  void AddItem(Item* item);
  void SetShapes(std::vector<MapShape*> shapes);
  void SetRelations(AdjacentList relations);

  Item* GetItem(LevelPos position);
  MapShape* GetMapShape(LevelPos position);
  TCODMap* GetMap();
  MapRoom* GetRoom(LevelPos position);
  std::vector<MapCorridor*> GetCorridors();
  std::vector<MapRoom*> GetRooms();
  std::vector<MapRoom*> GetRoomsInRadius(LevelPos position, int radius);
  const AdjacentList& GetRelations();
};

#endif
