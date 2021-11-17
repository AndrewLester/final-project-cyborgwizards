#ifndef UI_HPP
#define UI_HPP

#include "Map.hpp"
#include "Monster.hpp"
#include "Player.hpp"

enum GameState { InProgress, Win, Loss };

class UI {
 private:
  Map* map_;
  Player* player_;
  Monster* monster_;
  GameState state_;

 public:
  UI();
  ~UI();
  void RenderAll();

  void GetPlayer();
  void GetMap();
  void GetMonster();

  static UI& Instance() {
    static UI* instance = new UI();
    return *instance;
  }
};

#endif
