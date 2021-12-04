#include "RenderEngine.hpp"

void RenderEngine::SetChar(ScreenPos pos, char c) {
    TCODConsole test = TCODConsole(80, 25); 
    if ((pos.x >= 0 && pos.y >= 0) && (pos.x < test.getWidth() && pos.y < test.getHeight())) {
        TCODConsole::root->putChar(pos.x,pos.y,c);
        // TCOD_console_set_char(console,pos.x,pos.y,c);
    }
}

void RenderEngine::SetCharCol(ScreenPos pos, char c, TCODColor col) {
    TCODConsole test = TCODConsole(80, 25); 
    if ((pos.x >= 0 && pos.y >= 0) && (pos.x < test.getWidth() && pos.y < test.getHeight())) {
        TCODConsole::root->putChar(pos.x,pos.y,c);
        TCODConsole::root->setCharForeground(pos.x,pos.y,col);
        // TCOD_console_set_char(console,pos.x,pos.y,c);
        // TCOD_console_set_char_foreground(console,pos.x,pos.y,c);
        // static constexpr auto TEAL = tcod::ColorRGB{0, 255, 255}; // color
    }
}

void RenderEngine::RoomFill(ScreenPos upleft, ScreenPos lowright, char c_floor, char c_wall) {
    TCODConsole test = TCODConsole(80, 25); 
    int width = test.getWidth();
    int height = test.getHeight();
    for (int x = upleft.x; x <= lowright.x; x++) {
        for (int y = upleft.y; y <= lowright.y; y++) {
            if ((upleft.x >= 0 && lowright.x >= 0) && (upleft.x < width && lowright.y < height)) { // just check x, y?
                if (x == upleft.x || x == lowright.x || y == upleft.y || y == lowright.y) { // assumes valid edges gvn
                    TCODConsole::root->putChar(x,y,c_wall);
                } else {
                    TCODConsole::root->putChar(x,y,c_floor);
                }
                // TCOD_console_set_char(console,x,y,c);
            }
        }
    }
}

void RenderEngine::RoomFillCol(ScreenPos upleft, ScreenPos lowright, char c_floor, char c_wall, TCODColor col) {
    TCODConsole test = TCODConsole(80, 25); 
    int width = test.getWidth();
    int height = test.getHeight();
    for (int x = upleft.x; x <= lowright.x; x++) {
        for (int y = upleft.y; y <= lowright.y; y++) {
            if ((upleft.x >= 0 && lowright.x >= 0) && (upleft.x < width && lowright.y < height)) { // just check x, y?
                if (x == upleft.x || x == lowright.x || y == upleft.y || y == lowright.y) { // assumes valid edges gvn
                    TCODConsole::root->putChar(x,y,c_wall);
                } else {
                    TCODConsole::root->putChar(x,y,c_floor);
                }
                TCODConsole::root->setCharForeground(x,y,col);
                // TCOD_console_set_char(console,x,y,c);
                // TCOD_console_set_char_foreground(console,pos.x,pos.y,c);
            }
        }
    }
}

void RenderEngine::Print(ScreenPos pos, std::string str) {
    TCODConsole test = TCODConsole(80, 25); 
    int width = test.getWidth();
    int height = test.getHeight();
    if ((pos.x >= 0 && pos.x < width) && (pos.y >= 0 && pos.y < height)) {
        TCODConsole::root->print(pos.x, pos.y, str);
        // tcod::print(console, {0, 0}, "Hello World", TCOD_white, std::nullopt);
    }
}

void RenderEngine::Print(ScreenPos pos, std::string str, TCODColor col) {
    TCODConsole test = TCODConsole(80, 25); 
    int width = test.getWidth();
    int height = test.getHeight();
    if ((pos.x >= 0 && pos.x < width) && (pos.y >= 0 && pos.y < height)) {
        TCODConsole::root->print(pos.x, pos.y, str);
        for (int z = pos.x; z < pos.y; z++) {
            TCODConsole::root->setCharForeground(pos.x,pos.y,col);
            // TCOD_console_set_char(console,x,y,c);
            // TCOD_console_set_char_foreground(console,pos.x,pos.y,c);
        }
        // tcod::print(console, {0, 0}, "Hello World", TCOD_white, std::nullopt);
    }
}

// need to get valid console info from main? 