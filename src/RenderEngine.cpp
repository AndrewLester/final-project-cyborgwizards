#include "RenderEngine.hpp"

void RenderEngine::SetChar(ScreenPos pos, char c) {
    TCODConsole::root->putChar(pos.x,pos.y,c);
    // console.TCOD_console_set_char(console,pos.x,pos.y,c);
}

void RenderEngine::SetCharCol(ScreenPos pos, char c, TCODColor col) {
  TCODConsole::root->putChar(pos.x,pos.y,c);
  TCODConsole::root->setCharForeground(pos.x,pos.y,col);
  // console.TCOD_console_set_char(console,pos.x,pos.y,c);
  // console.TCOD_console_set_char_foreground(console,pos.x,pos.y,c);
  // static constexpr auto TEAL = tcod::ColorRGB{0, 255, 255}; // color
}

void RenderEngine::RoomFill(ScreenPos upleft, ScreenPos lowright, char c) {
    for (int x = upleft.x; x <= lowright.x; x++) {
        for (int y = upleft.y; y <= lowright.y; y++) {
            TCODConsole::root->putChar(x,y,c);
            // console.TCOD_console_set_char(console,x,y,c);
        }
    }
}

void RenderEngine::RoomFillCol(ScreenPos upleft, ScreenPos lowright, char c, TCODColor col) {
    for (int x = upleft.x; x <= lowright.x; x++) {
        for (int y = upleft.y; y <= lowright.y; y++) {
            TCODConsole::root->putChar(x,y,c);
            TCODConsole::root->setCharForeground(x,y,col);
            // console.TCOD_console_set_char(console,x,y,c);
        }
    }
}