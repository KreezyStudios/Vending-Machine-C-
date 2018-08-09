#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>

#include "vendingMachine.h"
#include "item.h"
#include "config.h" // might aswell :P

VendingMachine::VendingMachine() {
    Init();
}

void VendingMachine::Init() {
    _curCount = 1;

    // Register categories:
    AddCategory("chips", "Chips");
    AddCategory("beer_drinks", "Beer and Drinks");
    AddCategory("toys", "Toys");

    // Register items:
    AddItem("doritos", "Dorito Bag", "chips", 150);
    AddItem("cheetos", "Hot Cheetos", "chips", 150);
    AddItem("takis", "Takis", "chips", 169);

    AddItem("budweiser", "Bud Weiser", "beer_drinks", 225);
    AddItem("budlight", "Bud Light", "beer_drinks", 225);
    AddItem("coke", "Coca-Cola", "beer_drinks", 175);
    AddItem("sprite", "Sprite", "beer_drinks", 175);
    AddItem("capri", "Caprisun", "beer_drinks", 50);

    AddItem("gun", "BB Gun", "toys", 1500);
    AddItem("supersoaker", "Super Soaker", "toys", 1000);
    AddItem("barbie", "Barbie Doll", "toys", 499);

    PrintFullLine();
    NewLine();

    std::string title = MENU_TITLE;

    PrintLine("Welcome to my Vending Machine!", true);
    PrintLine("You can purcahse an item by inputting its ID (the number it follows) and depositing the price!", true);

    NewLine();

    PrintLine("Here is a list of all items and categories:");

    PrintAllItems();
    NewLine();
    PrintFullLine();

    Manager();
}

void VendingMachine::Reset() {
    system("CLS");
    Init();
}

void VendingMachine::Manager() {
    std::cout << std::endl; // new line
    std::cout << "Please enter an item ID to purchase it: ";

    int itemID = GetInt();

    while (_items.find(itemID) == _items.end()) {
	  std::cout << std::endl;

	  std::cout << "That was an invalid id! Please enter a valid one: ";
	  itemID = GetInt();
    }

    SelectItem(itemID);
}

void VendingMachine::SelectItem(int i) {
    _selectedItem = _items[i];

    std::cout << "You've selected " << _selectedItem.name << "! Please deposit " << FormatBalance(_selectedItem.price) << " in cents to purchase: ";

    int deposit = GetInt();

    while (deposit <= 0) {
	  std::cout << "Please deposit more than 0 cents: ";
	  deposit = GetInt();
    }

    SetBalance(deposit);

    if (BalanceChecker()) {
	  std::cout << "Your item has been withdrawn and your change is " << FormatBalance(_balance - _selectedItem.price) << "!" << std::endl;
	  std::cout << "Thanks for your business!";

	  Sleep(5000);
	  Reset();
    }
}

void VendingMachine::SetBalance(int cents) {
    _balance = cents;
}

bool VendingMachine::BalanceChecker() {
    if (_balance < _selectedItem.price) {
	  std::cout << "Please deposit " << FormatBalance(_selectedItem.price - _balance) << " more to purchase this item: ";
	  int deposit = GetInt();

	  SetBalance(_balance + deposit);

	  if (_balance < _selectedItem.price) {
		std::cout << "Incorrect amount, we are no longer interested in doing business with you. Goodbye!";

		Sleep(5000);
		Reset();

		return false;
	  }

	  return true;
    }

    return true;
}

void VendingMachine::PrintAllItems() {
    for (auto it = _categories.cbegin(); it != _categories.cend(); it++) {
	  PrintLine("- " + it->second + ":");

	  for (int i = 1; i < _items.size(); i++) {
		Item::ItemData curItem = _items[i];

		if (curItem.categoryID == it->first) {
		    PrintLine("    " + std::to_string(i) + ") " + curItem.name + ": " + FormatBalance(curItem.price));
		}
	  }
    }
}

void VendingMachine::AddCategory(std::string id, std::string name) {
    _categories[id] = name;
}

void VendingMachine::AddItem(std::string id, std::string name, std::string categoryID, int price) {
    if (_categories.find(categoryID) == _categories.end()) {
	  std::cout << "(ERROR) Invalid category input: " << categoryID << std::endl;
	  return;
    }

    Item newItem(id);
    
    newItem.SetName(name);
    newItem.SetCategory(categoryID);
    newItem.SetPrice(price);

    _items[_curCount] = newItem.FinishItem();
    _curCount++;
}

void VendingMachine::PrintLine(std::string str, bool center) {
    std::cout << "#";

    if (center) {
	  int spaceBetween = (MENU_WIDTH - str.length()) / 2;

	  // Bad method of doing this but I'll figure something out :D
	  for (int i = 1; i < spaceBetween; i++) {
		std::cout << " ";
	  }

	  std::cout << str;

	  for (int i = 1; i < spaceBetween; i++) {
		std::cout << " ";
	  }
    } else {
	  std::cout << " " << str;

	  int spaceAfter = MENU_WIDTH - str.length() - 2;

	  for (int i = 1; i < spaceAfter; i++) {
		std::cout << " ";
	  }
    }

    std::cout << "#" << std::endl;
}

void VendingMachine::NewLine() {
    std::cout << "#";

    for (int i = 2; i < MENU_WIDTH; i++) {
	  std::cout << " ";
    }

    std::cout << "#" << std::endl;
}

void VendingMachine::PrintFullLine() {
    for (int i = 0; i < MENU_WIDTH; i++) {
	  std::cout << "#";
    }

    std::cout << std::endl;
}

std::string VendingMachine::FormatBalance(int cents) {
    int dollars = cents / 100;
    int _cents = cents - (dollars * 100);

    std::string formatted = MONEY_CURRENCY + std::to_string(dollars) + "." + std::to_string(_cents);

    return formatted;
}

int VendingMachine::GetInt() {
    // Copied from: http://www.cplusplus.com/forum/beginner/58833/ 

    int ret_integer;
    std::string str_number;

    while (true) {
	  std::getline(std::cin, str_number); //get string input
	  std::stringstream convert(str_number); //turns the string into a stream

							     //checks for complete conversion to integer and checks for minimum value
	  if (convert >> ret_integer && !(convert >> str_number)) return ret_integer;

	  std::cin.clear(); //just in case an error occurs with cin (eof(), etc)
	  std::cerr << "Input must be a number. Please try again: ";
    }
}