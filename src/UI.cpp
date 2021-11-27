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
    // draw the player in the middle of the screen, also map, monster, items and additional UI info
    
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