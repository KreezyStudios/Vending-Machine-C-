#pragma once

#include <iostream>
#include <string>
#include <map>

class Item {
    public:
	  struct ItemData {
		std::string	    name;
		std::string	    id;
		std::string	    categoryID;
		int		    price;
	  };

	  Item(std::string id);

	  void SetName(std::string name);
	  void SetCategory(std::string categoryID);
	  void SetPrice(int price);

	  ItemData FinishItem();

    private:
	  std::map<int, ItemData> _tempItems;
};