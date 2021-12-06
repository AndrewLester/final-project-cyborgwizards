#include "UI.hpp"
#include "MapGenerator.hpp"
// maybe use the "Reading the content of the console" to test?

UI::UI() {
    // How should each be initialized? 
    // MapGenerator generator;
    // Map* map = generator.Generate(100, 100, 1);
    // player_ = new Player();
    // struct LevelPos test = {0, 0, 0};
    // player_ = new Player(test);
    // monster_ = new Monster();
}

UI::~UI() {
    delete player_; 
    delete monster_;
    delete map_;
}
  
void UI::RenderAll() {
    // draw the player in the middle of the screen, also map, monster, items and additional UI info as needed

    int width = RenderEngine::Instance().GetWidth();
    int height = RenderEngine::Instance().GetHeight();

    struct ScreenPos center1 = {width / 2, height / 2}; // if even/odd how to define center?
    struct LevelPos center2 = {width / 2, height / 2, 0}; // instead of 0 get current floor
    
    // map_->Render(center2);
    // player_->Draw(center1);
    // monster_->Draw(center1);
    // items render? 

    struct ScreenPos bottom1 = {0, height - 3};
    std::string str1 = "Floor: 0"; // TODO: add level display, how to get current floor #?
    RenderEngine::Instance().Print(bottom1, str1);

    struct ScreenPos bottom2 = {0, height - 2};
    Inventory* inv = player_->GetInventory();
    size_t size = inv->GetSize();
    std::string str2 = "Inventory:";
    for (size_t i = 0; i < size; i++) {
        Item* item = inv->GetItemAt(i);
        str2 = str2 + " " + std::to_string(i+1) + " " + item->GetName();
    }    
    RenderEngine::Instance().Print(bottom2, str2);  // TODO: add item display

    struct ScreenPos bottom3 = {0, height - 1}; 
    std::string str3 = "HP: " + std::to_string(player_->GetHp()) + "/100"; // works when player properly initialized
    RenderEngine::Instance().Print(bottom3, str3);

    // use gamestate to determine what to render, set up win and lost games too
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
