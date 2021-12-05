#include <SDL.h>
#include <libtcod.hpp>

#include <cstdlib>
#include <iostream>

#include "EventListener.hpp"
#include "MapGenerator.hpp"
#include "UI.hpp"

int main(int argc, char** argv) {
  // std::cout << "HI" << std::endl;
  auto params = TCOD_ContextParams{};
  params.tcod_version = TCOD_COMPILEDVERSION;
  params.argc = argc;
  params.argv = argv;
  params.vsync = 1;
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.window_title = "Libtcod Template Project";

  auto console = tcod::Console{80, 25};
  params.console = console.get();
  // RenderEngine::Instance().SetConsole(&console);

  auto context = tcod::new_context(params);
  // UI::Instance().RenderAll();

  // Game loop.
  while (true) {
    //   // Rendering.
    console.clear();
    // tcod::print(console, {0, 0}, "Hello World", TCOD_white, std::nullopt);
    TCOD_console_flush();
    context->present(console);

    // Handle input.
    SDL_Event event;
    SDL_WaitEvent(nullptr);
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          std::exit(EXIT_SUCCESS);
          break;
        default:
          EventListener::Instance().HandleInput(event);
      }
    }
  }

  // delete map;
  return 0;
}
