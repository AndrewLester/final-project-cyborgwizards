#include "MapShape.hpp"

MapShape::MapShape(int width, int height, LevelPos top_left) : Entity(top_left), width_(width), height_(height) {}

bool MapShape::IsReachable() { return reachable_; }

bool MapShape::ContainsLevelPos(LevelPos position) {
  LevelPos difference = position - this->position_;
  return difference.x < width_ && difference.y < height_ && difference.level == 0;
}
