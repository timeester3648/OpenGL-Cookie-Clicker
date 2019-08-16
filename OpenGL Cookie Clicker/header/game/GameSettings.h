#pragma once

#include <vector>

class GameSettings {

	public:

		static constexpr long double price_increase = 1.15;
		static constexpr long double sell_multiplier = .5;

		static constexpr unsigned long long updatePerSecond = 60;

		static constexpr float scroll_speed = 20;

		static long double cursor_cps;
		static long double grandma_cps;
		static long double farm_cps;
		static long double mine_cps;
		static long double factory_cps;
		static long double bank_cps;
		static long double temple_cps;
		static long double wizard_tower_cps;
		static long double shipment_cps;
		static long double alchemy_lab_cps;
		static long double portal_cps;
		static long double time_machine_cps;
		static long double antimatter_condenser_cps;
		static long double prism_cps;
		static long double chance_maker_cps;

		static bool short_numbers;

		static std::vector<long double*> amounts;

	private:

		GameSettings() = default;
		GameSettings(const GameSettings& other) = delete;
		GameSettings(GameSettings&&) = delete;

	public:

		static void init();

};