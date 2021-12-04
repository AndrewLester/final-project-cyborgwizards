#include "FireExtinguisher.hpp"
#include "StunEvent.hpp"


void FireExtinguisher::Draw(ScreenPos top_left) {
    int x = top_left.x;
    int y = top_left.y;
    x++;
    y++;
}
void FireExtinguisher::Use() {
    if(num_uses == 0) {
        Drop();
        return;
    }
    num_uses--;
    Player* play = GetPlayer();
    if(play->GetFacingDir() == Facing::N) {
        LevelPos start{play->GetPosition().x, play->GetPosition().y, play->GetPosition().level};
        LevelPos end{play->GetPosition().x, play->GetPosition().y + 2, play->GetPosition().level};

        StunEvent stun = StunEvent(play, start, end);
    } else if(play->GetFacingDir() == Facing::S) {
        LevelPos start{play->GetPosition().x, play->GetPosition().y, play->GetPosition().level};
        LevelPos end{play->GetPosition().x, play->GetPosition().y - 2, play->GetPosition().level};

        StunEvent stun = StunEvent(play, start, end);
    } else if(play->GetFacingDir() == Facing::E) {
        LevelPos start{play->GetPosition().x, play->GetPosition().y, play->GetPosition().level};
        LevelPos end{play->GetPosition().x + 2, play->GetPosition().y, play->GetPosition().level};

        StunEvent stun = StunEvent(play, start, end);
    } else {
        LevelPos start{play->GetPosition().x, play->GetPosition().y, play->GetPosition().level};
        LevelPos end{play->GetPosition().x - 2, play->GetPosition().y, play->GetPosition().level};

        StunEvent stun = StunEvent(play, start, end);
    }
}