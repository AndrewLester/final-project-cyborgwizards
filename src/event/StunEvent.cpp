#include "StunEvent.hpp"

StunEvent::StunEvent(Entity* emitter, LevelPos start, LevelPos end, int stun_period) :
    Event("StunEvent", emitter), start(start), end(end), stun_period(stun_period) {}