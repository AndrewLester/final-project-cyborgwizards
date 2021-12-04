#include "Monster.hpp"

#include "UI.hpp"

void Monster::Update() {
  if (timer_ == 0) {
    timer_ = this->state_ == MonsterState::Chase ? chase_speed_ : roam_speed_;

    if (this->position_ == this->path_.front()) {
      this->path_.pop_front();
    }
    LevelPos next_turn = this->path_.front();
    if (next_turn.x == this->position_.x) {
      this->position_.y += next_turn.y > this->position_.y ? 1 : -1;
    } else {
      this->position_.x += next_turn.x > this->position_.x ? 1 : -1;
    }
  } else {
    timer_--;
  }
}

void Monster::ChangeDestination(LevelPos destination) {
  this->destination_ = destination;
  MapRoom* current = UI::Instance().GetMap()->GetRoom(this->position_);
  MapRoom* dest = UI::Instance().GetMap()->GetRoom(this->destination_);

  while (!this->path_.empty()) { // clear past
    this->path_.pop_front();
  }

  if (current == dest) { // in same room
    this->path_.push_back({this->position_.x, this->destination_.y, this->position_.level});
    this->path_.push_back(this->destination_);
  } else { // not in same room
    // first get to the room
    auto map_info = UI::Instance().GetMap()->GetRelations();
    std::set<MapRoom*> visited;
    bool found = false;
    this->FindPath(map_info, visited, current, dest, found);
    if (!found) {
      throw std::runtime_error("Pathfind for Monster error!");
    }

    // then go the the place
    LevelPos center = dest->GetCenterPosition();
    this->path_.push_back({center.x, this->destination_.y, center.level});
    this->path_.push_back(this->destination_);
  }
}

void Monster::FindPath(const AdjacentList& map, std::set<MapRoom*>& visited, MapRoom* curr, MapRoom* dest, bool& found) {
  if (curr == dest) {
    found = true;
    return;
  }
  if (found) return;

  visited.insert(curr);
  auto& edges = map.at(curr);
  LevelPos start = curr->GetCenterPosition();
  for (auto it = edges.begin(); it != edges.end(); it++) {
    if (visited.find(it->first) == visited.end()) { // new room
      LevelPos end = it->first->GetCenterPosition();
      LevelPos corner = {end.x, start.y, start.level};
      auto first_corridor_points = it->second.first->GetPositions();
      if (std::find(first_corridor_points.begin(), first_corridor_points.end(), corner) == first_corridor_points.end()) {
        corner = {start.x, end.y, start.level};
      }
      this->path_.push_back(corner);
      this->path_.push_back(end);

      this->FindPath(map, visited, it->first, dest, found);

      this->path_.pop_back();
      this->path_.pop_back();
    }
  }
  visited.erase(curr);
}