#include "Item.hpp"
#include "Inventory.hpp"
#include <vector>

void Item::Drop() {
    if(UI::Instance().GetMap().GetItem(UI::Instance().GetPlayer().GetPosition()) == nullptr) {
        player_->GetInventory()->RemoveItem(this);
    } else {
        LevelPos* removed_coord = CheckNearestOpenPos();
        if(removed_coord == nullptr) {
            //handle case
        }
    }
    player_ = nullptr;
}


void Item::Pick(Player* player) {
    player_ = player;
    //assuming that player.OnNotify(Event event) will handle removing the item from the board
    if(player_->GetInventory()->GetSize() + 1 < player_->GetInventory()->GetMaxSize()) {
        player_->GetInventory()->AddItem(this);
    } else {
        //need to emit message that player cannot pick up item because inventory is full
    }

}


LevelPos* Item::CheckNearestOpenPos() {
    LevelPos curr_pos = UI::Instance().GetPlayer().GetPosition();
    LevelPos* remove_cord;
    std::vector<LevelPos*> neighbors;
    for(int i = 0; i < 3; i++) {
        neighbors.push_back(new LevelPos(curr_pos.x + i, curr_pos.GetY() + i));
        neighbors.push_back(new LevelPos(curr_pos.GetX() + i, curr_pos.GetY()));
        neighbors.push_back(new LevelPos(curr_pos.GetX() + i, curr_pos.GetY() - i));
        neighbors.push_back(new LevelPos(curr_pos.GetX(), curr_pos.GetY() + i));
        neighbors.push_back(new LevelPos(curr_pos.GetX(), curr_pos.GetY() - i));
        neighbors.push_back(new LevelPos(curr_pos.GetX() - i, curr_pos.GetY() + i));
        neighbors.push_back(new LevelPos(curr_pos.GetX() - i, curr_pos.GetY()));
        neighbors.push_back(new LevelPos(curr_pos.GetX() - i, curr_pos.GetY() - i));

        for(size_t j = 0; j < neighbors.size(); j++) {
            if(neighbors.at(i).GetX() != -1 && neighbors.at(i).GetY() != -1) {
                if(UI::Instance().GetMap().GetItem(neighbors.at(i)) == nullptr) {
                    player_->GetInventory()->RemoveItem(this);
                    return neighbors.at(i);
                }
            }
        }
    }
    return nullptr;
}