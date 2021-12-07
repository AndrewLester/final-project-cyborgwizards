#ifndef MAP_SHAPE_HPP
#define MAP_SHAPE_HPP

#include <libtcod.h>

#include <vector>

#include "Entity.hpp"
#include "LevelPos.hpp"

enum class ShapeType { ROOM, CORRIDOR };

class MapShape : public Entity {
 public:
  MapShape(LevelPos position, int width, int height);

 protected:
  bool reachable_ = false;

 public:
  virtual void Draw(ScreenPos top_left) = 0;
  virtual std::vector<LevelPos> GetPositions() = 0;
  bool IsReachable();
  bool ContainsLevelPos(LevelPos position);
};

#endif
