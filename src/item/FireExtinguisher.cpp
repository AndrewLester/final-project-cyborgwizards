#include "FireExtinguisher.hpp"
#include "StunEvent.hpp"

FireExtinguisher::FireExtinguisher(LevelPos pos):
    Item(pos, "Fire Extinguisher") {}

void FireExtinguisher::Draw(ScreenPos top_left) {
    RenderEngine::Instance().SetChar(top_left, 'f');
}

void FireExtinguisher::Use() {
    if(num_uses_ == 0) {
        Drop();
        return;
    }
    num_uses_--;
    Player* play = GetPlayer();
    if(play->GetFacingDir() == Facing::N) {
        LevelPos start{play->GetPosition().x, play->GetPosition().y, play->GetPosition().level};
        LevelPos end{play->GetPosition().x, play->GetPosition().y + 2, play->GetPosition().level};

        StunEvent stun = StunEvent(play, start, end, stun_period_);
    } else if(play->GetFacingDir() == Facing::S) {
        LevelPos start{play->GetPosition().x, play->GetPosition().y, play->GetPosition().level};
        LevelPos end{play->GetPosition().x, play->GetPosition().y - 2, play->GetPosition().level};

        StunEvent stun = StunEvent(play, start, end, stun_period_);
    } else if(play->GetFacingDir() == Facing::E) {
        LevelPos start{play->GetPosition().x, play->GetPosition().y, play->GetPosition().level};
        LevelPos end{play->GetPosition().x + 2, play->GetPosition().y, play->GetPosition().level};

        StunEvent stun = StunEvent(play, start, end, stun_period_);
    } else {
        LevelPos start{play->GetPosition().x, play->GetPosition().y, play->GetPosition().level};
        LevelPos end{play->GetPosition().x - 2, play->GetPosition().y, play->GetPosition().level};

        StunEvent stun = StunEvent(play, start, end, stun_period_);
    }
}