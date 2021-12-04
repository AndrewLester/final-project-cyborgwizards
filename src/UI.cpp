#include "UI.hpp"
// maybe use the "Reading the content of the console" to test?

#include "MapGenerator.hpp"

UI::UI() {
    // How should each be initialized? 
    MapGenerator generator;
    Map* map = generator.Generate(100, 100, 1);
    // player_ = new Player();
    // monster_ = new Monster();
}

UI::~UI() {
    delete player_; 
    delete monster_;
    delete map_;
}
  
void UI::RenderAll() {
    // draw the player in the middle of the screen, also map, monster, items and additional UI info as needed

    RenderEngine screen = RenderEngine();
    int width = con_.getWidth();
    int height = con_.getHeight();

    // auto console = tcod::Console{80, 50};  // get console from main? (have width/height be vars in main instead?)
    // int width = TCOD_console_get_width(console);
    // int height = TCOD_console_get_height(console);

    struct ScreenPos center1 = {width / 2, height / 2}; // if even/odd how to define center?
    struct LevelPos center2 = {width / 2, height / 2, 0}; // initial level but change to make abitrary
    map_->Render(center2);
    player_->Draw(center1);
    monster_->Draw(center1);

    // items render? 

    struct ScreenPos bottom1 = {0, height - 2}; // does it go from 0 to height - 1 instead?
    std::string str1 = "Floor: " + "x";
    screen.Print(bottom1, str1);

    struct ScreenPos bottom2 = {0, height - 1}; // does it go from 0 to height - 1 instead?

    std::string str2 = "Inventory: 1] " + "xxx" +  " 2] " + "xxx" + " 3] " + "xxx";
    screen.Print(bottom2, str1);

    struct ScreenPos bottom3 = {0, height}; // does it go from 0 to height - 1 instead?
    std::string str3 = "HP: " + std::to_string(player_->Gethp()); + "/100";
    screen.Print(bottom3, str3);
    // how to draw inv to screen, player health, see getter for player hp, level #?

    // use gamestate to determine what to render, set up win and lost games too
    // TCOD_console_flush() or TCODConsole::flush() needed after this step
    // notes on potential rendering of sound bar:
    // keep on right? side of screen in fixed pos, allow arrows and level to be drawn in x spaces depending on criteria
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

void SetConsole(TCODConsole* console) {
  this->con_ = console;
}