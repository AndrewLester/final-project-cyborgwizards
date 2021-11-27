#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include "ScreenPos.hpp"
#include "libtcod.hpp"

class RenderEngine {
 public:
  RenderEngine();

  RenderEngine& Instance() {
    static RenderEngine* instance = new RenderEngine();
    return *instance;
  }

  void SetChar(ScreenPos pos, char c); // TODO: maybe change this to UTF-8
  void SetCharCol(ScreenPos pos, char c, TCODColor col);
  void RoomFill(ScreenPos upleft, ScreenPos lowright, char c);
  void RoomFillCol(ScreenPos upleft, ScreenPos lowright, char c, TCODColor col);
};

#endif