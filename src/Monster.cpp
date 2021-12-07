#include "Monster.hpp"

#include <algorithm>

#include "UI.hpp"
#include "SoundEvent.hpp"

Monster::Monster(LevelPos pos, int roam_sound, int chase_sound):
  Entity(pos, 1, 1), kRoamSound(roam_sound), kChaseSound(chase_sound) {}

void Monster::Update() {
  if (timer_ == 0) {
    if (this->path_.empty()) return; // no node on path

    timer_ = this->state_ == MonsterState::Chase ? chase_speed_ : roam_speed_;
    if (this->position_ == this->path_.front()) {
      this->path_.pop_front();
    }
    
    if (this->path_.empty()) return; // last node on path
    LevelPos next_turn = this->path_.front();
    if (next_turn.x == this->position_.x) {
      this->position_.y += next_turn.y > this->position_.y ? 1 : -1;
    } else if (next_turn.y == this->position_.y) {
      this->position_.x += next_turn.x > this->position_.x ? 1 : -1;
    } else {
      std::cout << "pathfind error!" << std::endl;
      return;
    }

    if (!this->path_.empty() && this->position_ != this->path_.front())
      std::cout << "Current: " << position_.ToString() << ", Intended: " << path_.front().ToString() << std::endl;

    SoundEvent se(this, this->position_, this->state_ == MonsterState::Chase ? kChaseSound : kRoamSound);
    EventListener::Instance().BroadcastEvent(&se);
  } else {
    timer_--;
  }
}

void Monster::ChangeDestination(LevelPos destination) {
  std::cout << "Current Destination: (" << destination.x << ", " << destination.y << ")" << std::endl;
  this->destination_ = destination;
  MapShape* curr = UI::Instance().GetMap()->GetMapShape(this->position_);
  MapShape* dest = UI::Instance().GetMap()->GetMapShape(this->destination_);

  while (!this->path_.empty()) { // clear past
    this->path_.pop_front();
  }

  if (curr == dest) { // in same shape
    this->path_.push_back({this->position_.x, this->destination_.y, this->position_.level});
    this->path_.push_back(this->destination_);
  } else { // not in same room
    // first go to the center of current room
    LevelPos start_center = curr->GetCenterPosition();
    if (this->position_ != start_center) {
      this->path_.push_back({this->position_.x, start_center.y, start_center.level});
      if (this->position_.x != start_center.x) this->path_.push_back(start_center);
    }

    std::cout << "Going to center";
    for (LevelPos& pos : this->path_) {
      std::cout << "(" << pos.x << ", " << pos.y << "), ";
    }
    std::cout << std::endl;

    // then get to the room
    auto map_info = UI::Instance().GetMap()->GetRelations();
    std::set<MapShape*> visited;
    bool found = false;
    this->FindPath(map_info, visited, curr, dest, found);
    if (!found) {
      throw std::runtime_error("Pathfind for Monster error!");
    }
    std::cout << "Pathfind to room";
    for (LevelPos& pos : this->path_) {
      std::cout << "(" << pos.x << ", " << pos.y << "), ";
    }
    std::cout << std::endl;

    // then go the the place
    LevelPos center = dest->GetCenterPosition();
    if (center == destination) return;
    else if (center.x == destination.x || center.y == destination.y) {
      this->path_.push_back(this->destination_);
    } else {
      this->path_.push_back({center.x, this->destination_.y, center.level});
      this->path_.push_back(this->destination_);
    }
    std::cout << "Final";
    for (LevelPos& pos : this->path_) {
      std::cout << "(" << pos.x << ", " << pos.y << "), ";
    }
    std::cout << std::endl;
  }
}

void Monster::FindPath(const AdjacentList& map, std::set<MapShape*>& visited, MapShape* curr, MapShape* dest, bool& found) {
  if (curr == dest) {
    found = true;
    return;
  }

  visited.insert(curr);
  auto& edges = map.at(curr);
  LevelPos curr_center = curr->GetCenterPosition();
  for (MapShape* shape : edges) { // iterate all connected rooms
    if (visited.find(shape) == visited.end()) { // not visited
      if (!path_.empty() && shape->GetCenterPosition().x != path_.front().x && shape->GetCenterPosition().y != path_.front().y)
        std::cout << "Regular push" << std::endl;

      // corridor to corridor special test
      bool corner_required = false;
      LevelPos next_center = shape->GetCenterPosition();
      if (curr_center.x != next_center.x && curr_center.y != next_center.y) {
        LevelPos corner = {curr_center.x, next_center.y, curr_center.level};
        auto curr_points = curr->GetPositions();
        if (std::find(curr_points.begin(), curr_points.end(), corner) == curr_points.end()) {
          corner = {next_center.x, curr_center.y, curr_center.level};
        }
        if (!path_.empty() && corner.x != path_.front().x && corner.y != path_.front().y)
          std::cout << "Corner push" << std::endl;
        this->path_.push_back(corner);

        corner_required = true;
      }

      this->path_.push_back(next_center);

      this->FindPath(map, visited, shape, dest, found);
      if (found) return;
      if (corner_required) this->path_.pop_back();
      this->path_.pop_back();
      visited.erase(shape);
    }
  }
}