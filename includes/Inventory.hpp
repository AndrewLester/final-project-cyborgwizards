#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "Item.hpp"
#include <vector>
class Inventory {
 private:
  std::vector<Item*> inventory;
 
 public:
  void AddItem();
  int GetSize();
  Item* GetItemAt();
};

#endif