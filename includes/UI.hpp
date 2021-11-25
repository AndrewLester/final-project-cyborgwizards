#ifndef UI_HPP
#define UI_HPP

#include "Map.hpp"
#include "Monster.hpp"
#include "Player.hpp"
#include "libtcod.hpp"
#include <string>

enum GameState { InProgress, Win, Loss };

class UI {
 private:
  Map* map_;
  Player* player_;
  Monster* monster_;
  GameState state_;

  UI(){};
  ~UI(){};

 public:
  void RenderAll();
  
  Player* GetPlayer();
  Map* GetMap();
  Monster* GetMonster();

  static UI& Instance() {
    static UI* instance = new UI();
    return *instance;
  }
};

#endif
