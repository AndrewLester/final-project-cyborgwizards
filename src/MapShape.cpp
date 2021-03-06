#include "MapShape.hpp"

MapShape::MapShape(LevelPos position, int width, int height) : Entity(position, width, height) {}

bool MapShape::IsReachable() { return reachable_; }

bool MapShape::ContainsLevelPos(LevelPos position) {
  LevelPos difference = position - this->position_;
  return difference.x >= 0 && difference.x < width_ && difference.y >= 0 && difference.y < height_ && difference.level == 0;
}
