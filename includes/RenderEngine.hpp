#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include "ScreenPos.hpp"

class RenderEngine {
 public:
  RenderEngine();

  RenderEngine& Instance() {
    static RenderEngine* instance = new RenderEngine();
    return *instance;
  }

  void SetChar(ScreenPos pos, char c); // TODO: maybe change this to UTF-8
  // TODO: add one that supports color
};

#endif