#include "UI.hpp"
// maybe use the "Reading the content of the console" to test?

UI::UI() {
    // How should each be initialized? 
    player_ = new Player();
    monster_ = new Monster();
    map_ = new Map();
}

UI::~UI() {
    delete player_; 
    delete monster_;
    delete map_;
}
  
void UI::RenderAll() {
    // draw the player in the middle of the screen, also map, monster, items and additional UI info as needed

    // RenderEngine screen = RenderEngine();
    TCODConsole test = TCODConsole(80, 50); 
    int width = test.getWidth();
    int height = test.getHeight();

    // auto console = tcod::Console{80, 50};  // get console from main? (have width/height be vars in main instead?)
    // int width = TCOD_console_get_width(console);
    // int height = TCOD_console_get_height(console);

    struct ScreenPos center1 = {width / 2, height / 2}; // if even/odd how to define center?
    struct LevelPos center2 = {width / 2, height / 2, 0}; // initial level but change to make abitrary
    map_->Render(center2);
    player_->Draw(center1);
    monster_->Draw(center1);

    // how to draw inv to screen, player health, 
    // tcod::print(console, {0, 0}, "Hello World", TCOD_white, std::nullopt);
    // or TCODConsole::root->print(0, y, "text");
    // pull and merge main branch, see getter for player hp, level #?

    // use gamestate to determine what to render, set up win and lost games too

    // TCOD_console_flush() or TCODConsole::flush() needed after this step
}
  
Player* UI::GetPlayer() {
    return player_;
}

Map* UI::GetMap() {
    return map_;
}

Monster* UI::GetMonster() {
    return monster_;
}