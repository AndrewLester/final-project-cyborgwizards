#include "Entity.hpp"

Entity::Entity(LevelPos init_pos, int width, int height) : position_(init_pos), width_(width), height_(height) {}

Entity::~Entity() {}

void Entity::UploadEvent(Event event) { EventListener::Instance().BroadcastEvent(event); }

void Entity::RegisterListen(std::string event_type) { EventListener::Instance().RegisterListener(this, event_type); }

LevelPos Entity::GetPosition() { return this->position_; }

LevelPos Entity::GetCenterPosition() {
  LevelPos center{position_.x + (width_ / 2), position_.y + (height_ / 2), position_.level};
  return center;
}
