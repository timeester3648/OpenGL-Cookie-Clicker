#pragma once

#include "../../header/shop/ShopTile.h"

#include <vector>

class Shop {

	public:

		static std::vector<ShopTile*> tiles;

	private:

		static void registerTile(std::string name, bool locked = false);

	public:

		static void init();
		static void update();
		static void registerTile(int index);

};