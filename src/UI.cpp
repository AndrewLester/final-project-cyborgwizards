#include "UI.hpp"
#include "MapGenerator.hpp"
// maybe use the "Reading the content of the console" to test?

#include "UnsightedMonster.hpp"

UI::UI() {
  // How should each be initialized? 
  MapGenerator generator;
  std::cout << "Generating map...";
  std::cout.flush();
  this->map_ = generator.Generate(RenderEngine::Instance().GetWidth(), RenderEngine::Instance().GetHeight(), 1);

  std::cout << " Done." << std::endl;

  player_ = new Player(map_->GetSpawnLocation(0));
  EventListener::Instance().RegisterListener(player_, "KeyboardEvent");
  monster_ = new UnsightedMonster(map_->GetSpawnLocation(-1));
  EventListener::Instance().RegisterListener(monster_, "SoundEvent");
}

UI::~UI() {
  delete player_; 
  delete monster_;
  delete map_;
}

void UI::Update() {
  this->player_->Update();
  this->monster_->Update();
}
  
void UI::RenderAll() {
  // draw the player in the middle of the screen, also map, monster, items and additional UI info as needed

  // notes on potential rendering of sound bar:
  // keep on right? side of screen in fixed pos, allow arrows and level to be drawn in x spaces depending on criteria

  state_ = GameState::InProgress;

  if (state_ == GameState::InProgress) {
    int width = RenderEngine::Instance().GetWidth();
    int height = RenderEngine::Instance().GetHeight();

    ScreenPos center = {width / 2, height / 2}; // if even/odd how to define center?
    LevelPos player_pos = player_->GetPosition();
    map_->Render(player_pos, center);
    player_->Draw(center);

    LevelPos monster_pos = monster_->GetPosition();
    if (monster_pos.level == player_pos.level) {
      LevelPos relative_pos = monster_pos - player_pos;
      ScreenPos offset = {relative_pos.x, relative_pos.y};
      monster_->Draw(center + offset);
    }

    struct ScreenPos bottom1 = {0, height - 3};
    std::string str1 = "Floor: 1"; // TODO: add level display, how to get current floor #?
    RenderEngine::Instance().Print(bottom1, str1);
    ScreenPos bottom2 = {0, height - 2};
    std::string str2 = "Monster Pos: " + monster_->GetCenterPosition().ToString();
    RenderEngine::Instance().Print(bottom2, str2);

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
    struct ScreenPos one = {width/2-108/2, height/2-8/2+0};
    struct ScreenPos two = {width/2-108/2, height/2-8/2+1};
    struct ScreenPos three = {width/2-108/2, height/2-8/2+2};
    struct ScreenPos four = {width/2-108/2, height/2-8/2+3};
    struct ScreenPos five = {width/2-108/2, height/2-8/2+4};
    struct ScreenPos six = {width/2-108/2, height/2-8/2+5};
    struct ScreenPos seven = {width/2-108/2, height/2-8/2+6};
    struct ScreenPos eight = {width/2-108/2, height/2-8/2+7};
    RenderEngine::Instance().Print(one,   "                                      (`-')  _ (`-').->           (`-')  _  _  (`-') (`-')  _ _(`-')   ,---.");
    RenderEngine::Instance().Print(two,   "     .->        .->        .->        ( OO).-/ ( OO)_   _         (OO ).-/  \\-.(OO ) ( OO).-/( (OO ).->|   |");
    RenderEngine::Instance().Print(three, " ,--.'  ,-.(`-')----. ,--.(,--.      (,------.(_)--\\_)  \\-,-----. / ,---.   _.'    \\(,------. \\    .'_ |   |");
    RenderEngine::Instance().Print(four,  "(`-')'.'  /( OO).-.  '|  | |(`-')     |  .---'/    _ /   |  .--./ | \\ /`.\\ (_...--'' |  .---' '`'-..__)|   |");
    RenderEngine::Instance().Print(five,  "(OO \\    / ( _) | |  ||  | |(OO )    (|  '--. \\_..`--.  /_) (`-') '-'|_.' ||  |_.' |(|  '--.  |  |  ' ||  .'");
    RenderEngine::Instance().Print(six,   " |  /   /)  \\|  |)|  ||  | | |  \\     |  .--' .-._)   \\ ||  |OO )(|  .-.  ||  .___.' |  .--'  |  |  / :`--' ");
    RenderEngine::Instance().Print(seven, " `-/   /`    '  '-'  '\\  '-'(_ .'     |  `---.\\       /(_'  '--'\\ |  | |  ||  |      |  `---. |  '-'  /.--. ");
    RenderEngine::Instance().Print(eight, "   `--'       `-----'  `-----'        `------' `-----'    `-----' `--' `--'`--'      `------' `------' `--' ");
  } else { }
}

void UI::RenderWelcome() {
  int width = RenderEngine::Instance().GetWidth();
  int height = RenderEngine::Instance().GetHeight();
  struct ScreenPos one = {width/2-100/2, height/3-20/2+0};
  struct ScreenPos two = {width/2-100/2, height/3-20/2+1};
  struct ScreenPos three = {width/2-100/2, height/3-20/2+2};
  struct ScreenPos four = {width/2-100/2, height/3-20/2+3};
  struct ScreenPos five = {width/2-100/2, height/3-20/2+4};
  struct ScreenPos six = {width/2-100/2, height/3-20/2+5};
  struct ScreenPos seven = {width/2-100/2, height/3-20/2+6};
  struct ScreenPos eight = {width/2-100/2, height/3-20/2+7};
  struct ScreenPos nine = {width/2-100/2, height/3-20/2+8};
  RenderEngine::Instance().Print(one,   "  .-')      ('-.       .-') _   .-')     ('-.     .-') _                            .-') _   .-')   ");
  RenderEngine::Instance().Print(two,   " ( OO ).  _(  OO)     ( OO ) ) ( OO ).  ( OO ).-.(  OO) )                          ( OO ) ) ( OO ). ");
  RenderEngine::Instance().Print(three, "(_)---\\_)(,------.,--./ ,--,' (_)---\\_) / . --. //     '._ ,-.-')  .-'),-----. ,--./ ,--,' (_)---\\_)");
  RenderEngine::Instance().Print(four,  "/    _ |  |  .---'|   \\ |  |\\ /    _ |  | \\-.  \\ |'--...__)|  |OO)( OO'  .-.  '|   \\ |  |\\ /    _ | ");
  RenderEngine::Instance().Print(five,  "\\  :` `.  |  |    |    \\|  | )\\  :` `..-'-'  |  |'--.  .--'|  |  \\/   |  | |  ||    \\|  | )\\  :` `. ");
  RenderEngine::Instance().Print(six,   " '..`''.)(|  '--. |  .     |/  '..`''.)\\| |_.'  |   |  |   |  |(_/\\_) |  |\\|  ||  .     |/  '..`''.)");
  RenderEngine::Instance().Print(seven, ".-._)   \\ |  .--' |  |\\    |  .-._)   \\ |  .-.  |   |  |  ,|  |_.'  \\ |  | |  ||  |\\    |  .-._)   \\");
  RenderEngine::Instance().Print(eight, "\\       / |  `---.|  | \\   |  \\       / |  | |  |   |  | (_|  |      `'  '-'  '|  | \\   |  \\       /");
  RenderEngine::Instance().Print(nine,  " `-----'  `------'`--'  `--'   `-----'  `--' `--'   `--'   `--'        `-----' `--'  `--'   `-----' ");

  struct ScreenPos ten = {width/2-60/2, 2*height/5-20/2+9};
  struct ScreenPos eleven = {width/2-60/2, 2*height/5-20/2+10};
  struct ScreenPos twelve = {width/2-60/2, 2*height/5-20/2+11};
  struct ScreenPos thirteen = {width/2-60/2, 2*height/5-20/2+12};
  struct ScreenPos fourteen = {width/2-60/2, 2*height/5-20/2+13};
  struct ScreenPos fifteen = {width/2-60/2, 2*height/5-20/2+14};
  struct ScreenPos sixteen = {width/2-60/2, 2*height/5-20/2+15};
  struct ScreenPos seventeen = {width/2-60/2, 2*height/5-20/2+16};
  struct ScreenPos eighteen = {width/2-60/2, 2*height/5-20/2+17};
  struct ScreenPos nineteen = {width/2-60/2, 2*height/5-20/2+18};
  struct ScreenPos twenty = {width/2-60/2, 2*height/5-20/2+19};
  struct ScreenPos twentyone = {width/2-60/2, 2*height/5-20/2+20};
  struct ScreenPos twentytwo = {width/2-60/2, 2*height/5-20/2+21};
  struct ScreenPos twentythree = {width/2-60/2, 2*height/5-20/2+22};
  struct ScreenPos twentyfour = {width/2-60/2, 2*height/5-20/2+23};
  struct ScreenPos twentyfive = {width/2-60/2, 2*height/5-20/2+24};
  struct ScreenPos twentysix = {width/2-60/2, 2*height/5-20/2+25};
  struct ScreenPos twentyseven = {width/2-60/2, 2*height/5-20/2+26};
  struct ScreenPos twentyeight = {width/2-60/2, 2*height/5-20/2+27};
  struct ScreenPos twentynine = {width/2-60/2, 2*height/5-20/2+28};
  RenderEngine::Instance().Print(ten,         "                                               /\\      /\\   ");
  RenderEngine::Instance().Print(eleven,      "                                               ||______||   ");
  RenderEngine::Instance().Print(twelve,      "                                               || ^  ^ ||   ");
  RenderEngine::Instance().Print(thirteen,    "                                               \\| |  | |/   ");
  RenderEngine::Instance().Print(fourteen,    "                                                |______|    ");
  RenderEngine::Instance().Print(fifteen,     "              __                                |  __  |    ");
  RenderEngine::Instance().Print(sixteen,     "             /  \\       ________________________|_/  \\_|__  ");
  RenderEngine::Instance().Print(seventeen,   "            / ^^ \\     /=========================/ ^^ \\===| ");
  RenderEngine::Instance().Print(eighteen,    "           /  []  \\   /=========================/  []  \\==| ");
  RenderEngine::Instance().Print(nineteen,    "          /________\\ /=========================/________\\=| ");
  RenderEngine::Instance().Print(twenty,      "       *  |        |/==========================|        |=| ");
  RenderEngine::Instance().Print(twentyone,   "      *** | ^^  ^^ |---------------------------| ^^  ^^ |-- ");
  RenderEngine::Instance().Print(twentytwo,   "     *****| []  [] |           _____           | []  [] | | ");
  RenderEngine::Instance().Print(twentythree, "    *******        |          /_____\\          |      * | | ");
  RenderEngine::Instance().Print(twentyfour,  "   *********^^  ^^ |  ^^  ^^  |  |  |  ^^  ^^  |     ***| | ");
  RenderEngine::Instance().Print(twentyfive,  "  ***********]  [] |  []  []  |  |  |  []  []  | ===***** | ");
  RenderEngine::Instance().Print(twentysix,   " *************     |         @|__|__|@         |/ |*******| ");
  RenderEngine::Instance().Print(twentyseven, "***************   ***********--=====--**********| ********* ");
  RenderEngine::Instance().Print(twentyeight, "***************___*********** |=====| **********|***********");
  RenderEngine::Instance().Print(twentynine,  " *************     ********* /=======\\ ******** | ********* ");

  struct ScreenPos cont = {width/2-25/2, 2*height/5-20/2+30};
  RenderEngine::Instance().Print(cont, "Press any key to continue");
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
