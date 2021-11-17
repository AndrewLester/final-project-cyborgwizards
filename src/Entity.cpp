#include "Entity.hpp"

Entity::Entity(Coord init_pos): position_(init_pos) {}

void Entity::ReportEvent(Event event) {
  EventListener::Instance().BroadcastEvent(event);
}

void Entity::RegisterListen(std::string event_type) {
  EventListener::Instance().RegisterListener(this, event_type);
}

Coord Entity::GetPosition() {
  return this->position_;
}