#include "StunEvent.hpp"

StunEvent::StunEvent(Entity* emitter, LevelPos start, LevelPos end) :
    Event("StunEvent", emitter), start(start), end(end) {}