#include "../../header/game/PlayerData.h"
#include "../../header/game/GameSettings.h"

#define max(a, b) (a > b ? a : b)

long double PlayerData::cookies = 0, PlayerData::cookies_produced = 0, PlayerData::click_amount = 1;

unsigned long long PlayerData::cursors = 0;
unsigned long long PlayerData::grandmas = 0;
unsigned long long PlayerData::farms = 0;
unsigned long long PlayerData::mines = 0;
unsigned long long PlayerData::factories = 0;
unsigned long long PlayerData::banks = 0;
unsigned long long PlayerData::temples = 0;
unsigned long long PlayerData::wizard_towers = 0;
unsigned long long PlayerData::shipments = 0;
unsigned long long PlayerData::alchemy_labs = 0;
unsigned long long PlayerData::portals = 0;
unsigned long long PlayerData::time_machines = 0;
unsigned long long PlayerData::antimatter_condensers = 0;
unsigned long long PlayerData::prisms = 0;
unsigned long long PlayerData::chance_makers = 0;

long double PlayerData::cookies_produced_cursors = 0;
long double PlayerData::cookies_produced_grandmas = 0;
long double PlayerData::cookies_produced_farms = 0;
long double PlayerData::cookies_produced_mines = 0;
long double PlayerData::cookies_produced_factories = 0;
long double PlayerData::cookies_produced_banks = 0;
long double PlayerData::cookies_produced_temples = 0;
long double PlayerData::cookies_produced_wizard_towers = 0;
long double PlayerData::cookies_produced_shipments = 0;
long double PlayerData::cookies_produced_alchemy_labs = 0;
long double PlayerData::cookies_produced_portals = 0;
long double PlayerData::cookies_produced_time_machines = 0;
long double PlayerData::cookies_produced_antimatter_condensers = 0;
long double PlayerData::cookies_produced_prisms = 0;
long double PlayerData::cookies_produced_chance_makers = 0;

std::vector<unsigned long long*> PlayerData::amounts;
std::vector<long double*> PlayerData::seperate_produced;

void PlayerData::init() {

	amounts.push_back(&cursors);
	amounts.push_back(&grandmas);
	amounts.push_back(&farms);
	amounts.push_back(&mines);
	amounts.push_back(&factories);
	amounts.push_back(&banks);
	amounts.push_back(&temples);
	amounts.push_back(&wizard_towers);
	amounts.push_back(&shipments);
	amounts.push_back(&alchemy_labs);
	amounts.push_back(&portals);
	amounts.push_back(&time_machines);
	amounts.push_back(&antimatter_condensers);
	amounts.push_back(&prisms);
	amounts.push_back(&chance_makers);

	seperate_produced.push_back(&cookies_produced_cursors);
	seperate_produced.push_back(&cookies_produced_grandmas);
	seperate_produced.push_back(&cookies_produced_farms);
	seperate_produced.push_back(&cookies_produced_mines);
	seperate_produced.push_back(&cookies_produced_factories);
	seperate_produced.push_back(&cookies_produced_banks);
	seperate_produced.push_back(&cookies_produced_temples);
	seperate_produced.push_back(&cookies_produced_wizard_towers);
	seperate_produced.push_back(&cookies_produced_shipments);
	seperate_produced.push_back(&cookies_produced_alchemy_labs);
	seperate_produced.push_back(&cookies_produced_portals);
	seperate_produced.push_back(&cookies_produced_time_machines);
	seperate_produced.push_back(&cookies_produced_antimatter_condensers);
	seperate_produced.push_back(&cookies_produced_prisms);
	seperate_produced.push_back(&cookies_produced_chance_makers);

}

double PlayerData::percentage(int index) {

	if (*seperate_produced[index] == 0.0) {

		return 0.0;

	}

	return max(0, (*seperate_produced[index] / cookies_produced) * 100);

}

unsigned long long PlayerData::getAmounts(std::vector<int> black_list) {

	unsigned long long total = 0;

	for (int i = 0; i < amounts.size(); i++) {

		bool can = true;
		for (auto& j : black_list) {

			if (i == j) {

				can = false;

				break;

			}

		}

		if (can) {

			total += *amounts[i];

		}

	}

	return total;

}