#include "Monster.hpp"

void Monster::Update() {
  if (timer_ == 0) {
    timer_ = this->state_ == MonsterState::Chase ? chase_speed_ : roam_speed_;

    // TODO go one step
  } else {
    timer_--;
  }
}