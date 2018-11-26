#include "../../header/shop/ShopPrices.h"
#include "../../header/game/GameSettings.h"
#include "../../header/game/PlayerData.h"

#include <string>

long double ShopPrices::start_cursor = 15;
long double ShopPrices::start_grandma = 100;
long double ShopPrices::start_farm = 1100;
long double ShopPrices::start_mine = 12000;
long double ShopPrices::start_factory = 130000;
long double ShopPrices::start_bank = 1400000;
long double ShopPrices::start_temple = 20000000;
long double ShopPrices::start_wizard_tower = 330000000;
long double ShopPrices::start_shipment = 5100000000;
long double ShopPrices::start_alchemy_lab = 75000000000;
long double ShopPrices::start_portal = 1000000000000;
long double ShopPrices::start_time_machine = 14000000000000;
long double ShopPrices::start_antimatter_condenser = 170000000000000;
long double ShopPrices::start_prism = 2100000000000000;
long double ShopPrices::start_chance_maker = 26000000000000000;

std::vector<long double> ShopPrices::prices = std::vector<long double>();

long double ShopPrices::getPrice(int index, unsigned long long amount) {

	long double val = 0;

	for (unsigned long long i = 0; i < amount; i++) {

		val += customGetPrice(index, *PlayerData::amounts[index] + i);

	}

	return val;

}

long double ShopPrices::customGetPrice(int index, unsigned long long custom_amount) {

	long double mult = pow(GameSettings::price_increase, custom_amount);
	std::string tmp = std::to_string(ceil(prices[index] * mult));

	for (size_t i = tmp.length() - 1; i >= 0 && i != -1; i--) {

		if (tmp.at(i) == '.') {

			return std::stold(tmp.substr(0, i));

		}

	}

	return std::stold(tmp);

}

void ShopPrices::init() {

	prices.push_back(start_cursor);
	prices.push_back(start_grandma);
	prices.push_back(start_farm);
	prices.push_back(start_mine);
	prices.push_back(start_factory);
	prices.push_back(start_bank);
	prices.push_back(start_temple);
	prices.push_back(start_wizard_tower);
	prices.push_back(start_shipment);
	prices.push_back(start_alchemy_lab);
	prices.push_back(start_portal);
	prices.push_back(start_time_machine);
	prices.push_back(start_antimatter_condenser);
	prices.push_back(start_prism);
	prices.push_back(start_chance_maker);

}