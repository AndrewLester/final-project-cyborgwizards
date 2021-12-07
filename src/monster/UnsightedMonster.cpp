#include "UnsightedMonster.hpp"

#include "UI.hpp"
#include "RenderEngine.hpp"

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
    if (rel_intensity > 97) { // directly change
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
  }
}