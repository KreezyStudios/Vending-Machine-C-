#pragma once

#include <iostream>
#include <string>

#include "item.h"

class VendingMachine {
    public:
	  VendingMachine();

	  void Init();
	  void Reset();
	  void Manager();

	  void PrintAllItems();

	  void AddCategory(std::string id, std::string name);
	  void AddItem(std::string id, std::string name, std::string categoryID, int price); // Add stock limit?

	  void SelectItem(int i);
	  void SetBalance(int cents);

	  std::string FormatBalance(int cents);

	  bool BalanceChecker();

	  void PrintLine(std::string str, bool center = false);
	  void NewLine();

	  void PrintFullLine();

	  int GetInt();

    private:
	  std::map<std::string, std::string> _categories;
	  std::map<int, Item::ItemData> _items;

	  int _balance;
	  int _curCount;

	  Item::ItemData _selectedItem;
};