#include "UI.hpp"
#include "MapGenerator.hpp"

UI::UI() { // maybe take in map with a setter? 
  state_ = GameState::InProgress;
  // MapGenerator generator;
  // Map* map = generator.Generate(120, 40, 1);
  player_ = new Player({0, 0, 0});
  // monster_ = new Monster();
}

UI::~UI() {
  delete player_; 
  delete monster_;
  delete map_;
}
  
void UI::RenderAll() {
  // draw the player in the middle of the screen, also map, monster, items and additional UI info as needed

  if (state_ == GameState::InProgress) {
    int width = RenderEngine::Instance().GetWidth();
    int height = RenderEngine::Instance().GetHeight();

    struct ScreenPos center1 = {width / 2, height / 2}; 
    struct LevelPos center2 = {width / 2, height / 2, player_->GetPosition().level}; 
    
    // map_->Render() handles item rendering?
    // map uses console for drawing a rect, but why does player and monster need it? 
    // map_->Render({40, 18, 1}, {40, 18}, RenderEngine::Instance().GetConsole());  // center2, center 1
    // player_->Draw(center1, RenderEngine::Instance().GetConsole());
    // monster_->Draw(center1, RenderEngine::Instance().GetConsole());

    struct ScreenPos bottom1 = {0, height - 3};
    std::string str1 = "Floor: ";
    if (player_ != nullptr) {
      str1 = str1 + std::to_string(player_->GetPosition().level);
    }
    RenderEngine::Instance().Print(bottom1, str1);

    struct ScreenPos bottom2 = {0, height - 2};
    std::string str2 = "Inventory:";
    if (player_ != nullptr) {
      Inventory* inv = player_->GetInventory();
      if (inv != nullptr) {
        size_t size = inv->GetSize();
        for (size_t i = 0; i < size; i++) {
          Item* item = inv->GetItemAt(i);
          int index = static_cast<int>(i);
          str2 = str2 + " " + std::to_string(index+1) + " " + item->GetName();
        }
      }
    }  
    RenderEngine::Instance().Print(bottom2, str2);  // works with no items, does it work with items?

    struct ScreenPos bottom3 = {0, height - 1}; 
    std::string str3 = "HP: ";
    if (player_ != nullptr) {
      str3 = str3 + std::to_string(player_->GetHp());
    }
    str3 = str3 + "/100";
    RenderEngine::Instance().Print(bottom3, str3);

    // sound bar code, but would need bool indicators for direction arrows and int for total sound intensity value
    // struct ScreenPos sound1 = {width - 10, height/3+0};
    // struct ScreenPos sound2 = {width - 10, height/3+2}; 
    // struct ScreenPos sound3 = {width - 10, height/3+3}; 
    // struct ScreenPos sound4 = {width - 10, height/3+4}; 
    // struct ScreenPos sound5 = {width - 10, height/3+5}; 
    // struct ScreenPos sound6 = {width - 10, height/3+6}; 
    // struct ScreenPos sound7 = {width - 10, height/3+7}; 
    // RenderEngine::Instance().Print(sound1, "Sound");
    // RenderEngine::Instance().Print(sound2, "|---|");
    // RenderEngine::Instance().Print(sound3, "|   |");
    // RenderEngine::Instance().Print(sound4, "|   |");
    // RenderEngine::Instance().Print(sound5, "|   |");
    // RenderEngine::Instance().Print(sound6, "|   |");
    // RenderEngine::Instance().Print(sound7, "|---|");
    // bool up_, down_, left_, right_;
    // up_ = false;
    // down_ = false;
    // left_ = false;
    // right_ = false;
    // if (up_) {
    //   struct ScreenPos up = {width - 8, height/3+1};
    //   RenderEngine::Instance().Print(up, "v");
    // }
    // if (down_) {
    //   struct ScreenPos down = {width - 8, height/3+8};
    //   RenderEngine::Instance().Print(down, "^");
    // }
    // if (left_) {
    //   struct ScreenPos left = {width - 11, height/3+4};
    //   RenderEngine::Instance().Print(left, ">");
    // } 
    // if (right_) {
    //   struct ScreenPos right = {width - 5, height/3+4};
    //   RenderEngine::Instance().Print(right, "<");
    // }
    // int intensity_num = 0;
    // for (int i = 0; i < intensity_num; i++) {
    //   if (i == 3) {
    //     struct ScreenPos intensity1 = {width - 9, height/3+3};
    //     RenderEngine::Instance().Print(intensity1, "***");
    //   } else if (i == 2) {
    //     struct ScreenPos intensity2 = {width - 9, height/3+4};
    //     RenderEngine::Instance().Print(intensity2, "***");
    //   } else if (i == 1) {
    //     struct ScreenPos intensity3 = {width - 9, height/3+5};
    //     RenderEngine::Instance().Print(intensity3, "***");
    //   } else if (i == 0) {
    //     struct ScreenPos intensity4 = {width - 9, height/3+6};
    //     RenderEngine::Instance().Print(intensity4, "***");
    //   }
    // }
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

void UI::SetState(GameState state) {
  state_ = state;
}