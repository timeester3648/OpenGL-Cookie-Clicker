#pragma once

#include <vector>

class PlayerData {

	public:

		static long double cookies, click_amount, cookies_produced;

		static unsigned long long cursors;
		static unsigned long long grandmas;
		static unsigned long long farms;
		static unsigned long long mines;
		static unsigned long long factories;
		static unsigned long long banks;
		static unsigned long long temples;
		static unsigned long long wizard_towers;
		static unsigned long long shipments;
		static unsigned long long alchemy_labs;
		static unsigned long long portals;
		static unsigned long long time_machines;
		static unsigned long long antimatter_condensers;
		static unsigned long long prisms;
		static unsigned long long chance_makers;

		static long double cookies_produced_cursors;
		static long double cookies_produced_grandmas;
		static long double cookies_produced_farms;
		static long double cookies_produced_mines;
		static long double cookies_produced_factories;
		static long double cookies_produced_banks;
		static long double cookies_produced_temples;
		static long double cookies_produced_wizard_towers;
		static long double cookies_produced_shipments;
		static long double cookies_produced_alchemy_labs;
		static long double cookies_produced_portals;
		static long double cookies_produced_time_machines;
		static long double cookies_produced_antimatter_condensers;
		static long double cookies_produced_prisms;
		static long double cookies_produced_chance_makers;

		static std::vector<unsigned long long*> amounts;
		static std::vector<long double*> seperate_produced;

	private:

		PlayerData() = default;
		PlayerData(const PlayerData& other) = delete;
		PlayerData(PlayerData&&) = delete;

	public:

		static void init();

		static unsigned long long getAmounts(std::vector<int> black_list);
		static double percentage(int index);

};