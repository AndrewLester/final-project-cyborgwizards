#include "Player.hpp"

#include "KeyboardEvent.hpp"
#include "SoundEvent.hpp"
#include "UI.hpp"

Player::Player(LevelPos init_pos) : Entity(init_pos, 1, 1) {}

void Player::Draw(ScreenPos top_left) {
  RenderEngine::Instance().SetChar(top_left, '@');
}

void Player::OnNotify(Event* event) {
  if (event->GetType() == "KeyboardEvent") {
    KeyboardEvent* key_ptr = dynamic_cast<KeyboardEvent*>(event);
    KeyboardEvent& ke = *key_ptr;
    KeyType key = ke.key;
    if (ke.keyup) {  // key released, only care about moving
      if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        this->state_ = PlayerState::Stop;
      }
    } else {
      if (key == 'w' || key == 'a' || key == 's' || key == 'd') {  // start moving
        this->state_ = ke.shift ? PlayerState::Run : PlayerState::Walk;
        switch (key) {
          case 'w':
            this->facing_ = Facing::N;
            break;
          case 'a':
            this->facing_ = Facing::W;
            break;
          case 's':
            this->facing_ = Facing::S;
            break;
          case 'd':
            this->facing_ = Facing::E;
            break;
        }
      } else if (key == 'f') { // pick up item
        Item* item = UI::Instance().GetMap()->GetItem(this->position_);
        if (item != nullptr) {
          item->Pick(this);
        }
      } else if (key == 'e') { // use item
        this->inventory_->GetItemAtCurrIdx()->Use();
      } else if (key >= '0' && key <= '9') {
        int idx = (key == '0') ? 9 : static_cast<int>(key - '0') - 1;
        this->inventory_->SetCurrIdx(idx);
      }
    }
  }
}

void Player::Update() {
  if (this->timer_ == 0) {
    if (this->state_ == PlayerState::Run || this->state_ == PlayerState::Walk) {
      LevelPos next_pos = this->position_;
      if (this->facing_ == Facing::E)
        next_pos.x++;
      else if (this->facing_ == Facing::W)
        next_pos.x--;
      else if (this->facing_ == Facing::S)
        next_pos.y++;
      else
        next_pos.y--;

      if (UI::Instance().GetMap()->IsReachable(next_pos)) {
        bool running = this->state_ == PlayerState::Run;
        this->position_ = next_pos;
        this->timer_ = running ? this->run_speed_ : this->walk_speed_;
        SoundEvent se(this, this->position_, running ? kRunSound : kWalkSound);
        EventListener::Instance().BroadcastEvent(&se);
      } else {
        this->state_ = PlayerState::Stop;
      }
    }
  } else if (this->timer_ > 0) {
    this->timer_--;
  }
}

Inventory* Player::GetInventory() { return inventory_; }

int Player::GetHp() { return hp_; }

Facing Player::GetFacingDir() { return this->facing_; }
