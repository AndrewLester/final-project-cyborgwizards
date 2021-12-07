#include <SDL.h>

#include <cstdlib>
#include <iostream>
#include <libtcod.hpp>

#include "EventListener.hpp"
#include "MapGenerator.hpp"
#include "UI.hpp"

int main(int argc, char** argv) {
  auto params = TCOD_ContextParams{};
  params.tcod_version = TCOD_COMPILEDVERSION;
  params.argc = argc;
  params.argv = argv;
  params.vsync = 1;
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.window_title = "Sensations";
  params.renderer_type = TCOD_RENDERER_SDL2;

  auto console = tcod::Console{120, 40};
  params.console = console.get();

  auto context = tcod::new_context(params);
  RenderEngine::Instance().SetConsole(console.get());

  // Main Menu
  bool run = true;
  while (run) {
    console.clear();
    UI::Instance().RenderWelcome();
    context->present(console);
    TCOD_console_wait_for_keypress(true);
    run = false;
  }

  // Game loop.
  while (true) {
    // Rendering.

    console.clear();  // or can do TCOD_console_clear(console.get());
    UI::Instance().Update();
    UI::Instance().RenderAll();
    context->present(console);  // or can do TCOD_console_flush();

    // Handle input.
    SDL_Event event;
    // SDL_WaitEvent(nullptr);
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          std::exit(EXIT_SUCCESS);
          break;
        case SDL_KEYDOWN: 
          std::cout << event.key.keysym.sym << ' ' << event.key.keysym.mod << std::endl;
          EventListener::Instance().HandleInput(event);
          break;
        case SDL_KEYUP:
          std::cout << event.key.keysym.sym << ' ' << event.key.keysym.mod << "RELEASE" << std::endl;
          EventListener::Instance().HandleInput(event);
      }
    }
  }

  return 0;
}
