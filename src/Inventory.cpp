#include "Inventory.hpp"
#include <iostream>
void Inventory::AddItem(Item* item) {
	inventory.push_back(item);
}

size_t Inventory::GetSize() {
	return inventory.size();
}
size_t Inventory::GetMaxSize() {
	return max_size_;
}
void Inventory::SetMaxSize(size_t size) {
	this->max_size_ = size;
}

Item* Inventory::GetItemAt(size_t idx) {
	if(idx < 0 || idx >= inventory.size()) {
		throw std::out_of_range("invalid index");
	}
	return inventory.at(idx);
}

void Inventory::RemoveItem(Item* item) {
	size_t idx = 0;
    std::cout << "here" << std::endl;
	for(Item* i: inventory) {
		if(i == item) {
            // std::cout << "in this if" << std::endl;
			inventory.erase(inventory.begin() + idx);
			break;
		}
		idx++;
	}
}

size_t Inventory::GetCurrIdx() {
	return curr_idx_;
}
void Inventory::SetCurrIdx(size_t idx) {
	if(idx < inventory.size() && idx < max_size_) {
		curr_idx_ = idx;
	}
}
Item* Inventory::GetItemAtCurrIdx() {
	try {
		return inventory.at(curr_idx_);
	} catch (std::out_of_range err) {
		return nullptr;
	}
}