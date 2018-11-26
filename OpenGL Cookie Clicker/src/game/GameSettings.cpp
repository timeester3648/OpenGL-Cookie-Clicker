#include "../../header/game/GameSettings.h"

long double GameSettings::cursor_cps = .1;
long double GameSettings::grandma_cps = 1;
long double GameSettings::farm_cps = 8;
long double GameSettings::mine_cps = 47;
long double GameSettings::factory_cps = 260;
long double GameSettings::bank_cps = 1400;
long double GameSettings::temple_cps = 7800;
long double GameSettings::wizard_tower_cps = 44000;
long double GameSettings::shipment_cps = 260000;
long double GameSettings::alchemy_lab_cps = 1600000;
long double GameSettings::portal_cps = 10000000;
long double GameSettings::time_machine_cps = 65000000;
long double GameSettings::antimatter_condenser_cps = 430000000;
long double GameSettings::prism_cps = 2900000000;
long double GameSettings::chance_maker_cps = 21000000000;

bool GameSettings::short_numbers = true;

std::vector<long double*> GameSettings::amounts;

void GameSettings::init() {

	amounts.push_back(&cursor_cps);
	amounts.push_back(&grandma_cps);
	amounts.push_back(&farm_cps);
	amounts.push_back(&mine_cps);
	amounts.push_back(&factory_cps);
	amounts.push_back(&bank_cps);
	amounts.push_back(&temple_cps);
	amounts.push_back(&wizard_tower_cps);
	amounts.push_back(&shipment_cps);
	amounts.push_back(&alchemy_lab_cps);
	amounts.push_back(&portal_cps);
	amounts.push_back(&time_machine_cps);
	amounts.push_back(&antimatter_condenser_cps);
	amounts.push_back(&prism_cps);
	amounts.push_back(&chance_maker_cps);

}