#ifndef UI_HPP
#define UI_HPP

#include "Map.hpp"
#include "Monster.hpp"
#include "Player.hpp"
#include "RenderEngine.hpp"

enum GameState { InProgress, Win, Loss };

class UI {
 private:
  Map* map_;
  Player* player_ = nullptr;
  Monster* monster_;
  GameState state_;

  UI();
  ~UI();

 public:
  void Update();
  void RenderAll();
  void RenderWelcome();
  Player* GetPlayer();
  Map* GetMap();
  Monster* GetMonster();
  void SetState(GameState state);

  static UI& Instance() {
    static UI* instance = new UI();
    return *instance;
  }

};

#endif
