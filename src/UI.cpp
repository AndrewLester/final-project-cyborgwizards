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

  state_ = GameState::Loss;

  if (state_ == GameState::InProgress) {
    int width = RenderEngine::Instance().GetWidth();
    int height = RenderEngine::Instance().GetHeight();

    struct ScreenPos center1 = {width / 2, height / 2}; // if even/odd how to define center?
    struct LevelPos center2 = {width / 2, height / 2, 0}; // instead of 0 get current floor
    
    // map_->Render(center2); // handles item rendering
    // player_->Draw(center1);
    // monster_->Draw(center1);

    struct ScreenPos bottom1 = {0, height - 3};
    std::string str1 = "Floor: 0"; // TODO: add level display, how to get current floor #?
    RenderEngine::Instance().Print(bottom1, str1);

    // struct ScreenPos bottom2 = {0, height - 2};
    // Inventory* inv = player_->GetInventory();
    // std::string str2 = "Inventory:";
    // if (inv != nullptr) {
    //   size_t size = inv->GetSize();
    //   for (size_t i = 0; i < size; i++) {
    //     Item* item = inv->GetItemAt(i);
    //     str2 = str2 + " " + std::to_string(i+1) + " " + item->GetName();  // might need to conv i to int
    //   }
    // }  
    // RenderEngine::Instance().Print(bottom2, str2);  // works with no items, does it work with items?

    // struct ScreenPos bottom3 = {0, height - 1}; 
    // std::string str3 = "HP: " + std::to_string(player_->GetHp()) + "/100"; // works when player properly initialized
    // RenderEngine::Instance().Print(bottom3, str3);
  } else if (state_ == GameState::Loss) {
    int width = RenderEngine::Instance().GetWidth();
    int height = RenderEngine::Instance().GetHeight();
    struct ScreenPos one = {width/2-101/2, height/2-8/2+0};
    struct ScreenPos two = {width/2-101/2, height/2-8/2+1};
    struct ScreenPos three = {width/2-101/2, height/2-8/2+2};
    struct ScreenPos four = {width/2-101/2, height/2-8/2+3};
    struct ScreenPos five = {width/2-101/2, height/2-8/2+4};
    struct ScreenPos six = {width/2-101/2, height/2-8/2+5};
    struct ScreenPos seven = {width/2-101/2, height/2-8/2+6};
    struct ScreenPos eight = {width/2-101/2, height/2-8/2+7};
    RenderEngine::Instance().Print(one,   "                                                (`-')  _   _              (`-')  _ _(`-')            ");
    RenderEngine::Instance().Print(two,   "     .->        .->        .->          <-.     (OO ).-/  (_)      <-.    ( OO).-/( (OO ).->         ");
    RenderEngine::Instance().Print(three, " ,--.'  ,-.(`-')----. ,--.(,--.      (`-')-----./ ,---.   ,-(`-'),--. )  (,------. \\    .'_          ");
    RenderEngine::Instance().Print(four,  "(`-')'.'  /( OO).-.  '|  | |(`-')    (OO|(_\\---'| \\ /`.\\  | ( OO)|  (`-') |  .---' '`'-..__)         ");
    RenderEngine::Instance().Print(five,  "(OO \\    / ( _) | |  ||  | |(OO )     / |  '--. '-'|_.' | |  |  )|  |OO )(|  '--.  |  |  ' |         ");
    RenderEngine::Instance().Print(six,   " |  /   /)  \\|  |)|  ||  | | |  \\     \\_)  .--'(|  .-.  |(|  |_/(|  '__ | |  .--'  |  |  / :         ");
    RenderEngine::Instance().Print(seven, " `-/   /`    '  '-'  '\\  '-'(_ .'      `|  |_)  |  | |  | |  |'->|     |' |  `---. |  '-'  /,-.,-.,-.");
    RenderEngine::Instance().Print(eight, "   `--'       `-----'  `-----'          `--'    `--' `--' `--'   `-----'  `------' `------' '-''-''-'");
  } else if (state_ == GameState::Win) {
    int width = RenderEngine::Instance().GetWidth();
    int height = RenderEngine::Instance().GetHeight();
    // struct ScreenPos one = {width/2-101/2, height/2-8/2+0};
    // struct ScreenPos two = {width/2-101/2, height/2-8/2+1};
    // struct ScreenPos three = {width/2-101/2, height/2-8/2+2};
    // struct ScreenPos four = {width/2-101/2, height/2-8/2+3};
    // struct ScreenPos five = {width/2-101/2, height/2-8/2+4};
    // struct ScreenPos six = {width/2-101/2, height/2-8/2+5};
    // struct ScreenPos seven = {width/2-101/2, height/2-8/2+6};
    // struct ScreenPos eight = {width/2-101/2, height/2-8/2+7};
    // RenderEngine::Instance().Print(one,  );
    // RenderEngine::Instance().Print(two,  );
    // RenderEngine::Instance().Print(three,
    // RenderEngine::Instance().Print(four, 
    // RenderEngine::Instance().Print(five, 
    // RenderEngine::Instance().Print(six,  
    // RenderEngine::Instance().Print(seven,
    // RenderEngine::Instance().Print(eight,
  } else { }

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
