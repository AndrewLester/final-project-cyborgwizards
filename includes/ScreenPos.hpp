#ifndef SCREEN_POS_HPP
#define SCREEN_POS_HPP

struct ScreenPos {
  int x;
  int y;

  ScreenPos operator+(const ScreenPos& other) const {
    return {x + other.x, y + other.y};
  }
};

#endif