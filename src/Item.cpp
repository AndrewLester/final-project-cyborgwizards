#include "Item.hpp"
#include "Inventory.hpp"
#include "UI.hpp"
#include <vector>

Item::Item(LevelPos pos, std::string name): 
    Entity(pos, 1, 1), name_(name), in_inventory_(false) {}

void Item::Drop() {
    if(UI::Instance().GetMap()->GetItem(UI::Instance().GetPlayer()->GetPosition()) == nullptr) {
        player_->GetInventory()->RemoveItem(this);
    } else {
        LevelPos removed_coord = CheckNearestOpenPos();
        if(removed_coord.x == -1 && removed_coord.y == -1) {
            //handle case
        }
    }
    in_inventory_ = false;
    player_ = nullptr;
}

void Item::OnNotify(Event* event) {
    std::string event_type = event->GetType();
}

void Item::Pick(Player* player) {
    player_ = player;
    //assuming that player.OnNotify(Event event) will handle removing the item from the board
    if(player_->GetInventory()->GetSize() + 1 < player_->GetInventory()->GetMaxSize()) {
        player_->GetInventory()->AddItem(this);
    } else {
        //need to emit message that player cannot pick up item because inventory is full
    }
    in_inventory_ = true;
}


LevelPos Item::CheckNearestOpenPos() {
    LevelPos curr_pos = player_->GetPosition();
    std::vector<LevelPos> neighbors;
    for(int i = 0; i < 3; i++) {
        neighbors.push_back({curr_pos.x + i, curr_pos.y + i, curr_pos.level});
        neighbors.push_back({curr_pos.x + i, curr_pos.y, curr_pos.level});
        neighbors.push_back({curr_pos.x + i, curr_pos.y - i, curr_pos.level});
        neighbors.push_back({curr_pos.x, curr_pos.y + i, curr_pos.level});
        neighbors.push_back({curr_pos.x, curr_pos.y - i, curr_pos.level});
        neighbors.push_back({curr_pos.x - i, curr_pos.y + i, curr_pos.level});
        neighbors.push_back({curr_pos.x - i, curr_pos.y, curr_pos.level});
        neighbors.push_back({curr_pos.x - i, curr_pos.y - i, curr_pos.level});

        for(size_t j = 0; j < neighbors.size(); j++) {
            if(neighbors.at(i).x != -1 && neighbors.at(i).y != -1) {
                if (UI::Instance().GetMap()->IsReachable(neighbors.at(i)) && UI::Instance().GetMap()->GetItem(neighbors.at(i)) == nullptr) {
                    player_->GetInventory()->RemoveItem(this);
                    return neighbors.at(i);
                }
            }
        }
    }
    return {-1, -1, -1};
}

bool Item::InInventory(){
    return in_inventory_;
}

Player* Item::GetPlayer() {
    return player_;
}

std::string Item::GetName() {
    return name_;
}
