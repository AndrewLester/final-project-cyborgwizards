#include "Inventory.hpp"

void Inventory::AddItem(Item* item) {
    inventory.push_back(item);
}
size_t Inventory::GetSize() {
    return inventory.size();
}
size_t Inventory::GetMaxSize() {
    return max_size_;
}
Item* Inventory::GetItemAt(size_t idx) {
    if(idx < 0 || idx >= inventory.size()) {
        throw std::out_of_range("invalid index");
    }
    return inventory.at(idx);
}

void Inventory::RemoveItem(Item* item) {
    size_t idx = 0;
    for(Item* i: inventory) {
        if(i == item) {
            inventory.erase(inventory.begin() + idx);
            break;
        }
        idx++;
    }
}