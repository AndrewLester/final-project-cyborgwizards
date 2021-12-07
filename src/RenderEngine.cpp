#include "RenderEngine.hpp"

void RenderEngine::SetConsole(TCOD_Console* console) {
  this->console_ = console;
}

int RenderEngine::GetWidth() { return TCOD_console_get_width(this->console_); }
int RenderEngine::GetHeight() { return TCOD_console_get_height(this->console_); }

void RenderEngine::SetChar(ScreenPos pos, char c) {
  if ((pos.x >= 0 && pos.y >= 0) && (pos.x < this->GetWidth() && pos.y < this->GetHeight())) {
    TCOD_console_put_char(console_,pos.x,pos.y,c, TCOD_BKGND_DEFAULT);
  }
}

void RenderEngine::SetCharCol(ScreenPos pos, char c, TCOD_ColorRGB col) {
  if ((pos.x >= 0 && pos.y >= 0) && (pos.x < this->GetWidth() && pos.y < this->GetHeight())) {
    TCOD_console_put_char(console_,pos.x,pos.y,c, TCOD_BKGND_DEFAULT);
    TCOD_console_set_char_foreground(console_, pos.x,pos.y, col);
    // static constexpr auto TEAL = tcod::ColorRGB{0, 255, 255}; // color
  }
}

void RenderEngine::RoomFill(ScreenPos upleft, ScreenPos lowright, char c_floor, char c_wall) {
  int width = this->GetWidth();
  int height = this->GetHeight();
  for (int x = upleft.x; x <= lowright.x; x++) {
    for (int y = upleft.y; y <= lowright.y; y++) {
      if ((x >= 0 && y >= 0) && (x < width && y < height)) {
        if (x == upleft.x || x == lowright.x || y == upleft.y || y == lowright.y) { // assumes valid edges given
          TCOD_console_put_char(console_,x,y,c_wall, TCOD_BKGND_DEFAULT);
        } else {
          TCOD_console_put_char(console_,x,y,c_floor, TCOD_BKGND_DEFAULT);
        }
      }
    }
  }
}

void RenderEngine::RoomFillCol(ScreenPos upleft, ScreenPos lowright, char c_floor, char c_wall, TCOD_ColorRGB col_floor, TCOD_ColorRGB col_wall) {
  int width = this->GetWidth();
  int height = this->GetHeight();
  for (int x = upleft.x; x <= lowright.x; x++) {
    for (int y = upleft.y; y <= lowright.y; y++) {
      if ((x >= 0 && y >= 0) && (x < width && y < height)) {
        if (x == upleft.x || x == lowright.x || y == upleft.y || y == lowright.y) { // assumes valid edges gvn
          TCOD_console_put_char(console_,x,y,c_wall, TCOD_BKGND_DEFAULT);
          TCOD_console_set_char_foreground(console_, x, y, col_wall);
        } else {
          TCOD_console_put_char(console_,x,y,c_floor, TCOD_BKGND_DEFAULT);
          TCOD_console_set_char_foreground(console_, x, y, col_floor);
        }
      }
    }
  }
}

void RenderEngine::Print(ScreenPos pos, std::string str) {
  int width = this->GetWidth();
  int height = this->GetHeight();
  if ((pos.x >= 0 && pos.x < width) && (pos.y >= 0 && pos.y < height)) {
    tcod::print(*console_, {pos.x, pos.y}, str, TCOD_white, std::nullopt);
  }
}

void RenderEngine::Print(ScreenPos pos, std::string str, TCOD_ColorRGB col) {
  int width = this->GetWidth();
  int height = this->GetHeight();
  if ((pos.x >= 0 && pos.x < width) && (pos.y >= 0 && pos.y < height)) {
    tcod::print(*console_, {pos.x, pos.y}, str, col, std::nullopt);
  }
}

void RenderEngine::DrawRect(ScreenPos upleft, int width, int height, char c, TCOD_ColorRGB fore, TCOD_ColorRGB back) {
  tcod::draw_rect(*this->console_, {upleft.x, upleft.y, width, height}, c, fore, back);
}
