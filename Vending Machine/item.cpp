#include <iostream>
#include <map>

#include "item.h"

int curCount = 1;

Item::Item(std::string id) {
    ItemData newItem = {
	  id,
    };

    _tempItems[curCount] = newItem;
}

void Item::SetName(std::string name) {
    _tempItems[curCount].name = name;
}

void Item::SetCategory(std::string categoryID) {
    _tempItems[curCount].categoryID = categoryID;
}

void Item::SetPrice(int price) {
    _tempItems[curCount].price = price;
}

Item::ItemData Item::FinishItem() {
    curCount++;
    return _tempItems[curCount - 1];
}