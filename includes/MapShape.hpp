#ifndef MAP_SHAPE_HPP
#define MAP_SHAPE_HPP

class MapShape {
 public:
  int x_span;
  int y_span;
 
 protected:
  bool reachable_;

 public:
  virtual void Draw() = 0;
  bool IsReachable();
};

#endif