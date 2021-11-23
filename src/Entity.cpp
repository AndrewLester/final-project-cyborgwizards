#include "Entity.hpp"

Entity::Entity(LevelPos init_pos): position_(init_pos) {}

Entity::~Entity() {}

void Entity::UploadEvent(Event event) {
  EventListener::Instance().BroadcastEvent(event);
}

void Entity::RegisterListen(std::string event_type) {
  EventListener::Instance().RegisterListener(this, event_type);
}

LevelPos Entity::GetPosition() {
  return this->position_;
}