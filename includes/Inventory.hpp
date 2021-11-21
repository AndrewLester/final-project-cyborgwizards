#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "Item.hpp"
#include <stdexcept>
#include <vector>
class Inventory {
 private:
  std::vector<Item*> inventory;
  size_t max_size_;
 
 public:
  static Inventory* Instance();
  void AddItem(Item* item);
  void RemoveItem(Item* item);
  size_t GetSize();
  size_t GetMaxSize();
  Item* GetItemAt(size_t idx);
};

#endif