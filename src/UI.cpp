#include "UI.hpp"
// will need tcod included in the hpp file

UI::UI(); {
    // How should each be initialized? 
    player_ = new Player();
    monster_ = new Monster();
    map_ = new Map();
}

UI::~UI(); {
    delete player_; 
    delete monster;
    delete map_;
}

static UI* UI::Instance() {
    return instance_;
}
  
void UI::RenderAll() {
    // Coord position_; has a x and y plus other stuff
    // map has map and items, how to get chars, positions, and colors for things?

    // general precedure: init root (only need to do this once) then 
    // each time need to clear the screen, place new characters (via for x for y loop?), then actually draw the screen

    TCODConsole::initRoot(0,0,"name",false);  // length, width, name, fullscreen mode
    TCODConsole::root->clear(); // accesses pointer to the console
    TCODConsole::root->putChar(0,0,'@'); // draws a character at a positon x, y
    TCODConsole::root->setChar(0,0,'@'); // changes pre-existing characters
    TCODConsole::root->setCharForeground(x,y,col); // gets char at x,y to TCODColor col
    TCODConsole::flush(); // actually draws the screen 

    // above the root is a pointer but these (from the docs directly) are not 
    auto console = tcod::Console{80, 50}; // the root, maybe move into constructor
    console.clear(); // this clear is listen first, unclear how they're different 
    console.TCOD_console_clear(); // this clears to default colors and space char code
    console.TCOD_console_put_char(console, 0, 0, '@') // note this uses an int for characters
    console.TCOD_console_put_char_ex(console, 0, 0, '@', col1, col2); // needs forground and background color, 
    // but possibly can use std::nullopt in its place to ignore requirement 
    console.TCOD_console_set_char(console, 0, 0, '@') // replaces pre-existing chars without changing color
    console.TCOD_console_set_char_foreground(console, 0, 0, col) // changes char at x,y to forground color
    console.TCOD_console_flush();
    tcod::print(console,{0,0},"Hello World",{{255, 255, 255}},{{0, 0, 0}}); // source, {x,y}, text, RGB, alpha
    // TCOD_color_tkey_color is current color, static constexpr auto TEAL = tcod::ColorRGB{0, 255, 255}; example color
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