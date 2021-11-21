#include "Item.hpp"
#include "Inventory.hpp"
#include <vector>

void Item::Drop() {
    if(UI::Instance().GetMap().GetItem(UI::Instance().GetPlayer().GetPosition()) == nullptr) {
        Inventory::Instance().RemoveItem(*this);
    } else {
        Coord* removed_coord = CheckNearestOpenPos();
        if(removed_coord == nullptr) {
            //handle case
        }
    }
}


void Item::Pick() {
    //assuming that player.OnNotify(Event event) will handle removing the item from the board
    if(Inventory::Instance().GetSize() + 1 < Inventory::Instance().GetMaxSize()) {
        Inventory::Instance().AddItem(*this);
    } else {
        //need to emit message that player cannot pick up item because inventory is full
    }

}
int Item::GetInventoryIdx() {
    return inventory_idx_;
}

Coord* Inventory::CheckNearestOpenPos() {
    Coord* curr_pos = UI::Instance().GetPlayer().GetPosition();
    Coord* remove_cord;
    std::vector<Coord*> neighbors;
    for(int i = 0; i < 3; i++) {
        neighbors.push_back(new Coord(curr_pos.GetX() + i, curr_pos.GetY() + i));
        neighbors.push_back(new Coord(curr_pos.GetX() + i, curr_pos.GetY()));
        neighbors.push_back(new Coord(curr_pos.GetX() + i, curr_pos.GetY() - i));
        neighbors.push_back(new Coord(curr_pos.GetX(), curr_pos.GetY() + i));
        neighbors.push_back(new Coord(curr_pos.GetX(), curr_pos.GetY() - i));
        neighbors.push_back(new Coord(curr_pos.GetX() - i, curr_pos.GetY() + i));
        neighbors.push_back(new Coord(curr_pos.GetX() - i, curr_pos.GetY()));
        neighbors.push_back(new Coord(curr_pos.GetX() - i, curr_pos.GetY() - i));

        for(size_t j = 0; j < neighboars.size(); j++) {
            if(neighbors.at(i).GetX() != -1 && neighbors.at(i).GetY() != -1) {
                if(UI::Instance().GetMap().GetItem(neighboars.at(i)) == nullptr) {
                    Inventory::Instance().RemoveItem(*this);
                    return neighbors.at(i);
                }
            }
        }
    }
    return nullptr;
}