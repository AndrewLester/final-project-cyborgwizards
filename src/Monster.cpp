#include "Monster.hpp"

#include "UI.hpp"

void Monster::Update() {
  if (timer_ == 0) {
    timer_ = this->state_ == MonsterState::Chase ? chase_speed_ : roam_speed_;

    if (this->position_ == this->path_.front()) {
      this->path_.pop();
    }
    LevelPos next_turn = this->path_.front();
    if (next_turn.x == this->position_.x) {
      this->position_.y += next_turn.y > this->position_.y ? 1 : -1;
    } else {
      this->position_.x += next_turn.x > this->position_.x ? 1 : -1;
    }
  } else {
    timer_--;
  }
}

void Monster::ChangeDestination(LevelPos destination) {
  this->destination_ = destination;
  MapRoom* current = UI::Instance().GetMap()->GetRoom(this->position_);
  MapRoom* dest = UI::Instance().GetMap()->GetRoom(this->destination_);

  while (!this->path_.empty()) { // clear past
    this->path_.pop();
  }

  if (current == dest) { // in same room
    this->path_.push({this->position_.x, this->destination_.y, this->position_.level});
    this->path_.push(this->destination_);
  } else { // not in same room
    // first get to the room
    // TODO: find path

    // then go the the place
    LevelPos center = dest->GetCenterPosition();
    this->path_.push({center.x, this->destination_.y, center.level});
    this->path_.push(this->destination_);
  }
}