#ifndef UI_HPP
#define UI_HPP

#include "Map.hpp"
#include "Player.hpp"
#include "Monster.hpp"

enum GameState {
  InProgress,
  Win,
  Loss
};

class UI {
 private:
  static UI* instance_;
  Map* map_;
  Player* player_;
  Monster* monster_;
  GameState state_;

 public:
  UI();
  ~UI();
  static UI* Instance();
  void RenderAll();
  
  void GetPlayer();
  void GetMap();
  void GetMonster();
};

#endif