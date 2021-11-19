#include "UI.hpp"

UI::UI(); {

}

UI::~UI(); {

}

static UI* UI::Instance() {
    return this;
}
  
void UI::RenderAll() {

}
  
Player* UI::GetPlayer() {
    return player_
}

Map* UI::GetMap() {
    return map_
}

Monster* UI::GetMonster() {
    return monster_;
}