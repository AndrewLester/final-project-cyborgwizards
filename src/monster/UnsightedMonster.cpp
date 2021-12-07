#include "UnsightedMonster.hpp"

#include "UI.hpp"
#include "RenderEngine.hpp"
#include "StunEvent.hpp"

#include <cmath>

UnsightedMonster::UnsightedMonster(LevelPos pos):
  Monster(pos, 1, 2) {}

void UnsightedMonster::Draw(ScreenPos pos) {
  RenderEngine::Instance().SetChar(pos, '#');
}

void UnsightedMonster::OnNotify(Event* event) {
  if (event->emitter_ != this && event->GetType() == "SoundEvent") {
    SoundEvent sound_event = *dynamic_cast<SoundEvent*>(event);
    int rel_intensity = sound_event.RelativeIntensity(this->position_);
    if (rel_intensity > 80) { // directly change
      this->prev_intensity_ = rel_intensity;
      this->ChangeDestination(sound_event.source);
      this->state_ = MonsterState::Chase;
    } else if (rel_intensity > this->prev_intensity_ && rel_intensity > 20) { // uncertain
      this->prev_intensity_ = rel_intensity;
      auto rooms = UI::Instance().GetMap()->GetRoomsInRadius(this->position_, (100 - rel_intensity) / 10);
      if (rooms.size() == 0) return;
      auto target = rooms.at(rand() % rooms.size());
      this->ChangeDestination(target->GetCenterPosition());
      this->state_ = MonsterState::Roam;
    } // else: too small, don't react
  } else if (event->GetType() == "StunEvent") {
    StunEvent stun_event = *dynamic_cast<StunEvent*>(event);
    if (position_.x >= stun_event.start.x && position_.y >= stun_event.start.y &&
        position_.x <= stun_event.end.x && position_.y <= stun_event.end.y &&
        stun_cooldown_ == 0) {
      stun_cooldown_ = kStunCooldown;
      timer_ += stun_event.stun_period;
    }
  }
}