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

    struct ScreenPos center = {width / 2, height / 2}; // if even/odd how to define center?
    player_->Draw(center);  // screen.SetChar(center, '@');  instead? 

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