#include <catch2/catch_all.hpp>

/////////////////////// Library Includes ///////////////////////

#include <iostream>

/////////////////////// Project Includes ///////////////////////

#include "Entity.hpp"
#include "UI.hpp"

/////////////////////// EventListener ///////////////////////

TEST_CASE("EventListener", "[event-listener]") {
  class DerivedEntity : public Entity {
   private:
    std::string indicator_;
   public:
    DerivedEntity(std::string indicator): Entity({0, 0, 1}, 1, 1), indicator_(indicator) {}
    void OnNotify(Event event) override {
      std::string msg = this->indicator_ + ", " + event.GetType();
      throw std::runtime_error(msg);
    }
    void Draw(ScreenPos top_left) override {}
  };
  class DerivedEvent : public Event {
   public:
    DerivedEvent(Entity* emitter): Event("DerivedEvent", emitter) {}
  };

  Entity* e1 = new DerivedEntity("e1");
  Entity* e2 = new DerivedEntity("e2");

  Event event("BaseEvent", e1);
  DerivedEvent devent(e2);
  REQUIRE(event.GetType() == "BaseEvent");
  REQUIRE(devent.GetType() == "DerivedEvent");

  EventListener::Instance().RegisterListener(e1, "BaseEvent");
  REQUIRE_THROWS_WITH(e1->UploadEvent(event), "e1, BaseEvent");
  REQUIRE_NOTHROW(e2->UploadEvent(devent));
  EventListener::Instance().RegisterListener(e2, "DerivedEvent");
  REQUIRE_THROWS_WITH(e1->UploadEvent(devent), "e2, DerivedEvent");

  delete e1; delete e2;
}

/////////////////////// Player ///////////////////////

// Write tests here

/////////////////////// Monster ///////////////////////

// Write tests here

/////////////////////// RenderEngine ///////////////////////

TEST_CASE("RenderEngine", "[render-engine]") {
  auto params = TCOD_ContextParams{};
  params.tcod_version = TCOD_COMPILEDVERSION;
  params.vsync = 1;
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.window_title = "Sensations";
  auto console = tcod::Console{120, 40};
  params.console = console.get();
  params.renderer_type = TCOD_RENDERER_SDL2;
  auto context = tcod::new_context(params);
  RenderEngine::Instance().SetConsole(&console);
  console.clear();
  struct ScreenPos test = {0, 0};
  RenderEngine::Instance().SetChar(test, '@');
  test = {0, 1};
  RenderEngine::Instance().SetCharCol(test, '@', {255, 255, 0});
  struct ScreenPos test1 = {-1, 10};
  struct ScreenPos test2 = {10, 20};
  RenderEngine::Instance().RoomFill(test1, test2, '.', '#');
  test1 = {20, 30};
  test2 = {30, 39};
  RenderEngine::Instance().RoomFillCol(test1, test2, '.', '#', {255, 255, 0}, {255, 0, 0});
  struct ScreenPos test3 = {50, 10};
  RenderEngine::Instance().Print(test3, "test3");
  struct ScreenPos test4 = {50, 11};
  RenderEngine::Instance().Print(test4, "test4", {255, 0, 0});
  struct ScreenPos test5 = {-1, -1};
  RenderEngine::Instance().SetChar(test5, '1');
  context->present(console);
  // basic console dimensions
  REQUIRE(TCOD_console_get_width(console.get()) == 120);
  REQUIRE(TCOD_console_get_height(console.get()) == 40);
  // check set char with and without color including invalid inputs
  REQUIRE(TCOD_console_get_char(console.get(), 0, 0) == '@');
  REQUIRE(TCOD_console_get_char_foreground(console.get(), 0, 0) == TCOD_white);
  REQUIRE_FALSE(TCOD_console_get_char(console.get(), -1, -1) == '1');
  REQUIRE(TCOD_console_get_char_foreground(console.get(), 0, 1) == TCOD_yellow);
  // check fill room without color including valid and invalid points
  REQUIRE(TCOD_console_get_char(console.get(), 0, 10) == '#');
  REQUIRE(TCOD_console_get_char(console.get(), 1, 11) == '.');
  REQUIRE_FALSE(TCOD_console_get_char(console.get(), -1, 10) == '#');
  // check fill room with color that chars of certain colors are correct
  REQUIRE(TCOD_console_get_char(console.get(), 20, 30) == '#');
  REQUIRE(TCOD_console_get_char(console.get(), 21, 31) == '.');
  REQUIRE(TCOD_console_get_char_foreground(console.get(), 20, 30) == TCOD_red);
  REQUIRE(TCOD_console_get_char_foreground(console.get(), 21, 31) == TCOD_yellow);
  // check print statements including colors
  REQUIRE(TCOD_console_get_char(console.get(), 50, 10) == 't');
  REQUIRE(TCOD_console_get_char_foreground(console.get(), 50, 10) == TCOD_white);
  REQUIRE(TCOD_console_get_char(console.get(), 50, 11) == 't');
  REQUIRE(TCOD_console_get_char_foreground(console.get(), 50, 11) == TCOD_red);

  // test UI
}

/////////////////////// Items ///////////////////////

// Write tests here

/////////////////////// Add section below ///////////////////////
