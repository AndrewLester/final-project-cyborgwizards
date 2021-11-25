#ifndef MAP_SHAPE_HPP
#define MAP_SHAPE_HPP

#include "Entity.hpp"

enum class ShapeType { ROOM, CORRIDOR };

class MapShape : public Entity {
 public:
  MapShape(LevelPos position, int width, int height);

 protected:
  /**
   * @brief The distance in x coordinate that the shape extends.
   * A value of 1 corresponds to one cell in the x direction.
   * width and height of 1 represent a single cell.
   */
  int width_;
  /**
   * @brief The distance in y coordinate that the shape extends.
   * A value of 1 corresponds to one cell in the y direction.
   * width and height of 1 represent a single cell.
   */
  int height_;
  bool reachable_ = false;

 public:
  virtual void Draw(ScreenPos top_left) = 0;
  virtual std::vector<LevelPos> GetPositions() = 0;
  bool IsReachable();
  bool ContainsLevelPos(LevelPos position);
};

#endif
