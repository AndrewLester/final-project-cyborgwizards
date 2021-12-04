#include "UnsightedMonster.hpp"

#include "UI.hpp"

#include <cmath>

void UnsightedMonster::OnNotify(Event event) {
  if (event.emitter_ != this && event.GetType() == "SoundEvent") {
    SoundEvent sound_event = *((SoundEvent*)&event);
    int rel_intensity = sound_event.RelativeIntensity(this->position_);
    if (rel_intensity > 90) { // directly change
      this->prev_intensity_ = rel_intensity;
      this->ChangeDestination(sound_event.source);
    } else if (rel_intensity > this->prev_intensity_ && rel_intensity > 20) { // radius
      this->prev_intensity_ = rel_intensity;
      auto rooms = UI::Instance().GetMap()->GetRoomsInRadius(this->position_, (100 - rel_intensity) / 10);
      int rand_idx = static_cast<int>(trunc(rand() * rooms.size()));
      this->ChangeDestination(rooms.at(rand_idx)->GetCenterPosition());
    } // else: too small, don't react
  }
}