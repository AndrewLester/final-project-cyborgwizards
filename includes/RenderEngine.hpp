#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include "ScreenPos.hpp"
#include <libtcod.h>
#include <string>

class RenderEngine {
 private:
  TCOD_Console* console_;
 public:
  RenderEngine() = default;

  static RenderEngine& Instance() {
    static RenderEngine* instance = new RenderEngine();
    return *instance;
  }

  void SetConsole(TCOD_Console* console);
  int GetWidth();
  int GetHeight();

  void SetChar(ScreenPos pos, char c); // TODO: maybe change this to UTF-8
  void SetCharCol(ScreenPos pos, char c, TCOD_ColorRGB col);
  void RoomFill(ScreenPos upleft, ScreenPos lowright, char c_floor, char c_wall);
  void RoomFillCol(ScreenPos upleft, ScreenPos lowright, char c_floor, char c_wall, TCOD_ColorRGB col_floor, TCOD_ColorRGB col_wall);
  void DrawRect(ScreenPos upleft, int width, int height, char c, TCOD_ColorRGB fore, TCOD_ColorRGB back);
  void Print(ScreenPos pos, std::string str);
  void Print(ScreenPos pos, std::string str, TCOD_ColorRGB col);
  void DrawRect(ScreenPos pos, int width, int height, char c, tcod::ColorRGB col);
};

#endif