#include <catch2/catch_all.hpp>

/////////////////////// Library Includes ///////////////////////

#include <iostream>

/////////////////////// Project Includes ///////////////////////

#include "Entity.hpp"
#include "FireExtinguisher.hpp"
#include "MapGenerator.hpp"
#include "UI.hpp"

/////////////////////// Constants ///////////////////////
constexpr int MAP_GEN_SEED = 1234567;
constexpr int TEST_MAP_ROOMS = 13;
constexpr int TEST_MAP_CORRIDORS = 24;

/////////////////////// EventListener ///////////////////////

TEST_CASE("EventListener", "[event-listener]") {
  class DerivedEntity : public Entity {
   private:
    std::string indicator_;

   public:
    DerivedEntity(std::string indicator) : Entity({0, 0, 1}, 1, 1), indicator_(indicator) {}
    void OnNotify(Event* event) override {
      std::string msg = this->indicator_ + ", " + event->GetType();
      throw std::runtime_error(msg);
    }
    void Draw(ScreenPos top_left) override {}
  };
  class DerivedEvent : public Event {
   public:
    DerivedEvent(Entity* emitter) : Event("DerivedEvent", emitter) {}
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

  delete e1;
  delete e2;
}

/////////////////////// Player ///////////////////////

// Write tests here

/////////////////////// Monster ///////////////////////

// Write tests here

/////////////////////// RenderEngine ///////////////////////

TEST_CASE("RenderEngine & UI", "[render-engine_UI]") {
  auto params = TCOD_ContextParams{};
  params.tcod_version = TCOD_COMPILEDVERSION;
  params.vsync = 1;
  params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
  params.window_title = "Sensations";
  auto console = tcod::Console{120, 40};
  params.console = console.get();
  params.renderer_type = TCOD_RENDERER_SDL2;
  auto context = tcod::new_context(params);
  RenderEngine::Instance().SetConsole(console.get());
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
  SECTION("Render Engine") {
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
  }
  SECTION("UI") {
    console.clear();
    UI::Instance().RenderWelcome();
    context->present(console);
    // a few chars in the first line of the intro screen to verify message in correct place
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 100 / 2 + 2, 40 / 3 - 20 / 2) == '.');
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 100 / 2 + 3, 40 / 3 - 20 / 2) == '-');
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 100 / 2 + 5, 40 / 3 - 20 / 2) == ')');
    console.clear();
    GameState state1 = GameState::Loss;
    UI::Instance().SetState(state1);
    UI::Instance().RenderAll();
    context->present(console);
    // a few chars in the first line of the loss screen to verify message in correct place
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 101 / 2 + 5, 40 / 2 - 8 / 2 + 1) == '.');
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 101 / 2 + 6, 40 / 2 - 8 / 2 + 1) == '-');
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 101 / 2 + 7, 40 / 2 - 8 / 2 + 1) == '>');
    console.clear();
    GameState state2 = GameState::Win;
    UI::Instance().SetState(state2);
    UI::Instance().RenderAll();
    context->present(console);
    // a few chars in the first line of the win screen to verify message in correct place
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 108 / 2, 40 / 2 - 8 / 2 + 4) == '(');
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 108 / 2 + 1, 40 / 2 - 8 / 2 + 4) == 'O');
    REQUIRE(TCOD_console_get_char(console.get(), 120 / 2 - 108 / 2 + 4, 40 / 2 - 8 / 2 + 4) == '\\');
    console.clear();
    GameState state3 = GameState::InProgress;
    UI::Instance().SetState(state3);
    UI::Instance().RenderAll();
    context->present(console);
    // testing various aspects of the main renderall
    // player HP display
    REQUIRE(TCOD_console_get_char(console.get(), 4, 40 - 1) == '1');
    REQUIRE(TCOD_console_get_char(console.get(), 5, 40 - 1) == '0');
    REQUIRE(TCOD_console_get_char(console.get(), 6, 40 - 1) == '0');
    // player inventory display
    Player* player_ = new Player({0, 0, 0});
    Item* item = new FireExtinguisher({0, 0, 0});
    player_->GetInventory()->AddItem(item);
    // code ripped from UI for ease of testing
    struct ScreenPos bottom2 = {0, 40 - 2};
    std::string str2 = "Inventory:";
    if (player_ != nullptr) {
      Inventory* inv = player_->GetInventory();
      if (inv != nullptr) {
        size_t size = inv->GetSize();
        for (size_t i = 0; i < size; i++) {
          Item* item = inv->GetItemAt(i);
          int index = static_cast<int>(i);
          str2 = str2 + " " + std::to_string(index + 1) + "] " + item->GetName();
        }
      }
    }
    RenderEngine::Instance().Print(bottom2, str2);
    REQUIRE(TCOD_console_get_char(console.get(), 11, 40 - 2) == '1');
    REQUIRE(TCOD_console_get_char(console.get(), 14, 40 - 2) == 'F');
    delete player_;
    // floor indicator display
    REQUIRE(TCOD_console_get_char(console.get(), 7, 40 - 3) == '1');
  }
}

/////////////////////// Items ///////////////////////

TEST_CASE("FireExtinguisher", "[fire-extinguisher]") {
  Player* p = new Player({0, 0, 1});
  Item* fe = new FireExtinguisher({0, 0, 1});
  Item* fe2 = new FireExtinguisher({0, 0, 1});
  p->GetInventory()->AddItem(fe);
  REQUIRE(p->GetInventory()->GetSize() == 1);

  delete p;
  delete fe;
  delete fe2;
}

/////////////////////// Map ///////////////////////

Map* GetTestMap() {
  TCODRandom* random = new TCODRandom(MAP_GEN_SEED);

  MapGenerator gen;
  Map* map = gen.Generate(120, 40, 1, random);

  delete random;
  return map;
}

TEST_CASE("Map Generation", "[map-generation]") {
  Map* map = GetTestMap();
  SECTION("Map has correct number of rooms") { REQUIRE(map->GetRooms().size() == TEST_MAP_ROOMS); }

  SECTION("Map has correct number of corridors") { REQUIRE(map->GetCorridors().size() == TEST_MAP_CORRIDORS); }

  SECTION("Map shapes are dug properly") {
    TCODMap* tcod_map = map->GetMap();

    for (MapRoom* room : map->GetRooms()) {
      for (LevelPos pos : room->GetPositions()) {
        REQUIRE(tcod_map->isWalkable(pos.x, pos.y));
        REQUIRE(tcod_map->isTransparent(pos.x, pos.y));
      }
    }

    for (MapCorridor* corridor : map->GetCorridors()) {
      for (LevelPos pos : corridor->GetPositions()) {
        REQUIRE(tcod_map->isWalkable(pos.x, pos.y));
        REQUIRE(tcod_map->isTransparent(pos.x, pos.y));
      }
    }
  }

  SECTION("Map room adjacency") {
    for (MapRoom* room : map->GetRooms()) {
      auto& relations = map->GetRelations();
      for (auto it = relations.begin(); it != relations.end(); it++) {
        auto& cur = *it;
        const MapShape* cur_shape = cur.first;
        if (const MapRoom* cur_room = dynamic_cast<const MapRoom*>(cur_shape)) {
          auto& cur_relationships = cur.second;

          for (MapShape* shape : cur_relationships) {
            if (MapRoom* cur_rel_room = dynamic_cast<MapRoom*>(shape)) {
              bool is_num_valid = cur_rel_room->GetRoomNumber() == cur_room->GetRoomNumber() - 1 ||
                                  cur_rel_room->GetRoomNumber() == cur_room->GetRoomNumber() + 1;
              REQUIRE(is_num_valid);
            }
          }
        }
      }
    }
  }

  delete map;
}

/////////////////////// Add section below ///////////////////////
