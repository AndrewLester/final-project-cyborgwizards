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
      std::cout << "Pathfind error!" << std::endl;
      return;
    }

    SoundEvent se(this, this->position_, this->state_ == MonsterState::Chase ? kChaseSound : kRoamSound);
    EventListener::Instance().BroadcastEvent(&se);
  } else {
    timer_--;
  }
}

void Monster::ChangeDestination(LevelPos destination) {
  this->destination_ = destination;
  MapShape* curr = UI::Instance().GetMap()->GetMapShape(this->position_);
  MapShape* dest = UI::Instance().GetMap()->GetMapShape(this->destination_);

  while (!this->path_.empty()) { // clear past
    this->path_.pop_front();
  }
  this->paths_.clear();

  if (curr == dest) { // in same shape
    this->path_.push_back({this->position_.x, this->destination_.y, this->position_.level});
    this->path_.push_back(this->destination_);
  } else { // not in same room
    // Find room-to-room shortest path
    auto map_info = UI::Instance().GetMap()->GetRelations();
    std::set<MapShape*> visited;
    this->FindPath(map_info, visited, curr, dest);
    std::sort(this->paths_.begin(), this->paths_.end(),
              [](std::deque<LevelPos>& p1, std::deque<LevelPos>& p2){ return p1.size() < p2.size(); });
    this->path_ = this->paths_.at(0);

    // Find path to start of room-to-room path
    LevelPos start_pos = this->path_.front();
    LevelPos corner = {this->position_.x, start_pos.y, start_pos.level};
    auto points = curr->GetPositions();
    if (std::find(points.begin(), points.end(), corner) == points.end()) {
      corner = {start_pos.x, this->position_.y, start_pos.level};
    }
    this->path_.push_front(corner);

    // then go the the place
    LevelPos center = dest->GetCenterPosition();
    if (center == destination) return;
    else if (center.x == destination.x || center.y == destination.y) {
      this->path_.push_back(this->destination_);
    } else {
      this->path_.push_back({center.x, this->destination_.y, center.level});
      this->path_.push_back(this->destination_);
    }
  }
}

void Monster::FindPath(const AdjacentList& map, std::set<MapShape*>& visited, MapShape* curr, MapShape* dest) {
  if (curr == dest) {
    this->paths_.push_back(this->path_);
    return;
  }

  visited.insert(curr);
  auto& edges = map.at(curr);
  LevelPos curr_center = curr->GetCenterPosition();
  for (MapShape* shape : edges) { // iterate all connected rooms
    if (visited.find(shape) == visited.end()) { // not visited
      // corridor to corridor special test
      bool corner_required = false;
      LevelPos next_center = shape->GetCenterPosition();
      if (curr_center.x != next_center.x && curr_center.y != next_center.y) {
        LevelPos corner = {curr_center.x, next_center.y, curr_center.level};
        auto curr_points = curr->GetPositions();
        if (std::find(curr_points.begin(), curr_points.end(), corner) == curr_points.end()) {
          corner = {next_center.x, curr_center.y, curr_center.level};
        }
        this->path_.push_back(corner);

        corner_required = true;
      }

      this->path_.push_back(next_center);

      this->FindPath(map, visited, shape, dest);
      if (corner_required) this->path_.pop_back();
      this->path_.pop_back();
      visited.erase(shape);
    }
  }
}