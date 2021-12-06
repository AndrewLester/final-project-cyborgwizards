#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <stdexcept>
#include <vector>

class Item;

class Inventory {
 private:
  std::vector<Item*> inventory;
  size_t max_size_;
  size_t curr_idx_;
 
 public:
  static Inventory* Instance();
  void AddItem(Item* item);
  void RemoveItem(Item* item);
  size_t GetSize();
  size_t GetMaxSize();
  Item* GetItemAt(size_t idx);
  size_t GetCurrIdx();
  void SetCurrIdx(size_t idx);
  Item* GetItemAtCurrIdx();
};

#endif