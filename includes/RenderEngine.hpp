#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include "ScreenPos.hpp"
#include "libtcod.hpp"
#include <string>

class RenderEngine {
 public:
  RenderEngine();

  RenderEngine& Instance() {
    static RenderEngine* instance = new RenderEngine();
    return *instance;
  }

  void SetChar(ScreenPos pos, char c); // TODO: maybe change this to UTF-8
  void SetCharCol(ScreenPos pos, char c, TCODColor col);
  void RoomFill(ScreenPos upleft, ScreenPos lowright, char c_floor, char c_wall);
  void RoomFillCol(ScreenPos upleft, ScreenPos lowright, char c_floor, char c_wall, TCODColor col);
  void Print(ScreenPos pos, std::string str);
  void Print(ScreenPos pos, std::string str, TCODColor col);
};

#endif