#include <SDL.h>
#include <dlfcn.h>
#include <libtcod.h>

#include <cstdlib>
#include <iostream>

int main(int argc, char** argv) {
#if defined(__APPLE__)
  dlopen("./libEGL.dylib", RTLD_FIRST | RTLD_GLOBAL);
  dlopen("./libGLESv2.dylib", RTLD_FIRST | RTLD_GLOBAL);
#endif

  // std::cout << "HI" << std::endl;
  auto params = TCOD_ContextParams{};
  params.tcod_version = TCOD_COMPILEDVERSION;
  params.argc = argc;
  params.argv = argv;
  params.vsync = 1;
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.window_title = "Libtcod Template Project";
  params.sdl_window_flags = 0;

  auto console = tcod::Console{80, 25};
  params.console = console.get();

  auto context = tcod::new_context(params);

  // Game loop.
  while (true) {
    //   // Rendering.
    console.clear();
    // tcod::print(console, {0, 0}, "Hello World", TCOD_white, std::nullopt);
    context->present(console);

    // Handle input.
    SDL_Event event;
    SDL_WaitEvent(nullptr);
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          std::exit(EXIT_SUCCESS);
          break;
      }
    }
  }
  return 0;
}
