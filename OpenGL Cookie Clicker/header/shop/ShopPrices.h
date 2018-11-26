#pragma once

#include <vector>

class ShopPrices {

	private:

		static long double start_cursor;
		static long double start_grandma;
		static long double start_farm;
		static long double start_mine;
		static long double start_factory;
		static long double start_bank;
		static long double start_temple;
		static long double start_wizard_tower;
		static long double start_shipment;
		static long double start_alchemy_lab;
		static long double start_portal;
		static long double start_time_machine;
		static long double start_antimatter_condenser;
		static long double start_prism;
		static long double start_chance_maker;

		static std::vector<long double> prices;

	private:

		static long double customGetPrice(int index, unsigned long long custom_amount);

	public:

		static long double getPrice(int index, unsigned long long amount = 1);

		static void init();

};