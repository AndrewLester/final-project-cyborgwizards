#include "RenderEngine.hpp"

void RenderEngine::SetChar(ScreenPos pos, char c) {
    TCODConsole test = TCODConsole(80, 50); 
    if ((pos.x >= 0 && pos.y >= 0) && (pos.x < test.getWidth() && pos.y < test.getHeight())) {
        TCODConsole::root->putChar(pos.x,pos.y,c);
        // TCOD_console_set_char(console,pos.x,pos.y,c);
    }
}

void RenderEngine::SetCharCol(ScreenPos pos, char c, TCODColor col) {
    TCODConsole test = TCODConsole(80, 50); 
    if ((pos.x >= 0 && pos.y >= 0) && (pos.x < test.getWidth() && pos.y < test.getHeight())) {
        TCODConsole::root->putChar(pos.x,pos.y,c);
        TCODConsole::root->setCharForeground(pos.x,pos.y,col);
        // TCOD_console_set_char(console,pos.x,pos.y,c);
        // TCOD_console_set_char_foreground(console,pos.x,pos.y,c);
        // static constexpr auto TEAL = tcod::ColorRGB{0, 255, 255}; // color
    }
}

// only fill avilable parts 
// add print stuff here
// need to get valid console info from main? 

void RenderEngine::RoomFill(ScreenPos upleft, ScreenPos lowright, char c) {
    TCODConsole test = TCODConsole(80, 50); 
    int width = test.getWidth();
    int height = test.getHeight();
    for (int x = upleft.x; x <= lowright.x; x++) {
        for (int y = upleft.y; y <= lowright.y; y++) {
            if ((upleft.x >= 0 && lowright.x >= 0) && (upleft.x < width && lowright.y < height)) {
                TCODConsole::root->putChar(x,y,c);
                // TCOD_console_set_char(console,x,y,c);
            }
        }
    }
}

void RenderEngine::RoomFillCol(ScreenPos upleft, ScreenPos lowright, char c, TCODColor col) {
    TCODConsole test = TCODConsole(80, 50); 
    int width = test.getWidth();
    int height = test.getHeight();
    for (int x = upleft.x; x <= lowright.x; x++) {
        for (int y = upleft.y; y <= lowright.y; y++) {
            if ((upleft.x >= 0 && lowright.x >= 0) && (upleft.x < width && lowright.y < height)) {
                TCODConsole::root->putChar(x,y,c);
                TCODConsole::root->setCharForeground(x,y,col);
                // TCOD_console_set_char(console,x,y,c);
            }
        }
    }
}