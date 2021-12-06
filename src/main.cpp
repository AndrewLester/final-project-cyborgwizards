#include <SDL.h>
#include <libtcod.hpp>

#include <cstdlib>
#include <iostream>

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
  params.window_title = "Libtcod Template Project";

  auto console = tcod::Console{125, 25};
  params.console = console.get();
  params.renderer_type = TCOD_RENDERER_SDL2;

  auto context = tcod::new_context(params);

  RenderEngine::Instance().SetConsole(&console);
  // UI::Instance().RenderAll();

  // depricated code that works 
  // TCODConsole::initRoot(80, 25, "title", false);

  // Game loop.
  while (true) {
    //   // Rendering.

    // TCOD_console_clear(console.get());
    // tcod::print(console, {0, 0}, "Hello World", std::nullopt, std::nullopt);
    // context->present(console);

    console.clear();
    // tcod::print(console, {0, 0}, "Hello World", TCOD_white, std::nullopt);
    UI::Instance().RenderAll();
    context->present(console);  // TCOD_console_flush();

    // depricated code that works 
    // TCODConsole::root->clear();
    // TCODConsole::root->print(0, 0, "Hello World");
    // TCODConsole::root->flush();

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
