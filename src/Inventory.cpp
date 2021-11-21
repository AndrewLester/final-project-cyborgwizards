#include "Inventory.hpp"

static Inventory* Inventory::Instance() {
    return *this;
}

static void Inventory::AddItem(Item* item) {
    inventory.push_back(item);
}
static size_t GetSize() {
    return inventory.size();
}
static size_t GetMaxSize() {
    return max_size_;
}
static Item* GetItemAt(size_t idx) {
    if(idx < 0 || idx >= inventory.size()) {
        throw std::out_of_range("invalid index");
    }
    return inventory.at(idx);
}

void Inventory::RemoveItem(Item* item) {
    size_t idx = 0;
    for(Item i: inventory) {
        if(i == item) {
            inventory.erase(inventory.begin() + idx);
            break;
        }
        idx++;
    }
}