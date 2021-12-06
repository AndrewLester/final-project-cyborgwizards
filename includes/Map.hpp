#ifndef MAP_HPP
#define MAP_HPP

#include <libtcod/fov.hpp>
#include <map>
#include <ostream>
#include <vector>

#include "Item.hpp"
#include "MapCorridor.hpp"
#include "MapRoom.hpp"
#include "MapShape.hpp"

typedef std::map<MapRoom*, std::map<MapRoom*, std::pair<MapCorridor*, MapCorridor*>>> AdjacentList;
class Map {
 private:
  int width_;
  int height_;
  std::vector<MapShape*> shapes_;
  AdjacentList relations_;
  std::vector<Item*> items_;
  TCODMap* map_;

 public:
  Map(int width, int height);
  ~Map();

  void Render(LevelPos center, ScreenPos screen_center, tcod::Console& console);
  bool IsReachable(LevelPos position);
  void AddItem(Item* item);
  void SetShapes(std::vector<MapShape*> shapes);
  void SetRelations(AdjacentList relations);

  int GetWidth() const;
  int GetHeight() const;
  Item* GetItem(LevelPos position);
  MapShape* GetMapShape(LevelPos position);
  TCODMap* GetMap();
  MapRoom* GetRoom(LevelPos position);
  std::vector<MapCorridor*> GetCorridors() const;
  std::vector<MapRoom*> GetRooms() const;
  std::vector<MapRoom*> GetRoomsInRadius(LevelPos position, int radius);
  const AdjacentList& GetRelations();
};

std::ostream& operator<<(std::ostream& os, const Map& map);

#endif
