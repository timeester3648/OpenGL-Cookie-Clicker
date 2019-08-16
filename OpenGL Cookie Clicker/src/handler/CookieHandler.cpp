#include "../../header/handler/CookieHandler.h"
#include "../../header/handler/UpgradeHandler.h"
#include "../../header/game/GameSettings.h"
#include "../../header/game/PlayerData.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/handler/EffectHandler.h"
#include "../../header/Main.h"

#include <EOUL\Maths.hpp>
#include <fstream>
#include <iostream>

using namespace EOUL::Math;

long double CookieHandler::cps[15];

void CookieHandler::init() {

	cps[0] = GameSettings::cursor_cps;
	cps[1] = GameSettings::grandma_cps;
	cps[2] = GameSettings::farm_cps;
	cps[3] = GameSettings::mine_cps;
	cps[4] = GameSettings::factory_cps;
	cps[5] = GameSettings::bank_cps;
	cps[6] = GameSettings::temple_cps;
	cps[7] = GameSettings::wizard_tower_cps;
	cps[8] = GameSettings::shipment_cps;
	cps[9] = GameSettings::alchemy_lab_cps;
	cps[10] = GameSettings::portal_cps;
	cps[11] = GameSettings::time_machine_cps;
	cps[12] = GameSettings::antimatter_condenser_cps;
	cps[13] = GameSettings::prism_cps;
	cps[14] = GameSettings::chance_maker_cps;

}

void CookieHandler::update() {

	long double old_cookies = PlayerData::cookies;

	static long double add_cursor = 0.0;
	static long double add_grandma = 0.0;
	static long double add_farm = 0.0;
	static long double add_mine = 0.0;
	static long double add_factories = 0.0;
	static long double add_bank = 0.0;
	static long double add_temple = 0.0;
	static long double add_wizard_tower = 0.0;
	static long double add_shipment = 0.0;
	static long double add_alchemy_lab = 0.0;
	static long double add_portal = 0.0;
	static long double add_time_machine = 0.0;
	static long double add_antimatter_condenser = 0.0;
	static long double add_prism = 0.0;
	static long double add_chance_maker = 0.0;

	add_cursor += process_cps(0, (GameSettings::cursor_cps * PlayerData::cursors) / GameSettings::updatePerSecond);

	if (add_cursor >= 1.0) {

		PlayerData::cookies += floor(add_cursor);
		PlayerData::cookies_produced_cursors += floor(add_cursor); 

		add_cursor -= floor(add_cursor);

	}

	add_grandma += process_cps(1, (GameSettings::grandma_cps * PlayerData::grandmas) / GameSettings::updatePerSecond);

	if (add_grandma >= 1.0) {

		PlayerData::cookies += floor(add_grandma);
		PlayerData::cookies_produced_grandmas += floor(add_grandma); 

		add_grandma -= floor(add_grandma);

	}

	add_farm += process_cps(2, (GameSettings::farm_cps * PlayerData::farms) / GameSettings::updatePerSecond);

	if (add_farm >= 1.0) {

		PlayerData::cookies += floor(add_farm);
		PlayerData::cookies_produced_farms += floor(add_farm);

		add_farm -= floor(add_farm);

	}

	add_mine += process_cps(3, (GameSettings::mine_cps * PlayerData::mines) / GameSettings::updatePerSecond);

	if (add_mine >= 1.0) {

		PlayerData::cookies += floor(add_mine);
		PlayerData::cookies_produced_mines += floor(add_mine);

		add_mine -= floor(add_mine);

	}

	add_factories += process_cps(4, (GameSettings::factory_cps * PlayerData::factories) / GameSettings::updatePerSecond);

	if (add_factories >= 1.0) {

		PlayerData::cookies += floor(add_factories);
		PlayerData::cookies_produced_factories += floor(add_factories);

		add_factories -= floor(add_factories);

	}

	add_bank += process_cps(5, (GameSettings::bank_cps * PlayerData::banks) / GameSettings::updatePerSecond);

	if (add_bank >= 1.0) {

		PlayerData::cookies += floor(add_bank);
		PlayerData::cookies_produced_banks += floor(add_bank);

		add_bank -= floor(add_bank);

	}

	add_temple += process_cps(6, (GameSettings::temple_cps * PlayerData::temples) / GameSettings::updatePerSecond);

	if (add_temple >= 1.0) {

		PlayerData::cookies += floor(add_temple);
		PlayerData::cookies_produced_temples += floor(add_temple);

		add_temple -= floor(add_temple);

	}

	add_wizard_tower += process_cps(7, (GameSettings::wizard_tower_cps * PlayerData::wizard_towers) / GameSettings::updatePerSecond);

	if (add_wizard_tower >= 1.0) {

		PlayerData::cookies += floor(add_wizard_tower);
		PlayerData::cookies_produced_wizard_towers += floor(add_wizard_tower);

		add_wizard_tower -= floor(add_wizard_tower);

	}

	add_shipment += process_cps(8, (GameSettings::shipment_cps * PlayerData::shipments) / GameSettings::updatePerSecond);

	if (add_shipment >= 1.0) {

		PlayerData::cookies += floor(add_shipment);
		PlayerData::cookies_produced_shipments += floor(add_shipment);

		add_shipment -= floor(add_shipment);

	}

	add_alchemy_lab += process_cps(9, (GameSettings::alchemy_lab_cps * PlayerData::alchemy_labs) / GameSettings::updatePerSecond);

	if (add_alchemy_lab >= 1.0) {

		PlayerData::cookies += floor(add_alchemy_lab);
		PlayerData::cookies_produced_alchemy_labs += floor(add_alchemy_lab);

		add_alchemy_lab -= floor(add_alchemy_lab);

	}

	add_portal += process_cps(10, (GameSettings::portal_cps * PlayerData::portals) / GameSettings::updatePerSecond);

	if (add_portal >= 1.0) {

		PlayerData::cookies += floor(add_portal);
		PlayerData::cookies_produced_portals += floor(add_portal);

		add_portal -= floor(add_portal);

	}

	add_time_machine += process_cps(11, (GameSettings::time_machine_cps * PlayerData::time_machines) / GameSettings::updatePerSecond);

	if (add_time_machine >= 1.0) {

		PlayerData::cookies += floor(add_time_machine);
		PlayerData::cookies_produced_time_machines += floor(add_time_machine);

		add_time_machine -= floor(add_time_machine);

	}

	add_antimatter_condenser += process_cps(12, (GameSettings::antimatter_condenser_cps * PlayerData::antimatter_condensers) / GameSettings::updatePerSecond);

	if (add_antimatter_condenser >= 1.0) {

		PlayerData::cookies += floor(add_antimatter_condenser);
		PlayerData::cookies_produced_antimatter_condensers += floor(add_antimatter_condenser);

		add_antimatter_condenser -= floor(add_antimatter_condenser);

	}

	add_prism += process_cps(13, (GameSettings::prism_cps * PlayerData::prisms) / GameSettings::updatePerSecond);

	if (add_prism >= 1.0) {

		PlayerData::cookies += floor(add_prism);
		PlayerData::cookies_produced_prisms += floor(add_prism);

		add_prism -= floor(add_prism);

	}

	add_chance_maker += process_cps(14, (GameSettings::chance_maker_cps * PlayerData::chance_makers) / GameSettings::updatePerSecond);

	if (add_chance_maker >= 1.0) {

		PlayerData::cookies += floor(add_chance_maker);
		PlayerData::cookies_produced_chance_makers += floor(add_chance_maker);

		add_chance_maker -= floor(add_chance_maker);

	}

	long double diff = PlayerData::cookies - old_cookies;

	if (diff > 0.0) {

		PlayerData::cookies_produced += diff;

	}

}

long double CookieHandler::get_main_cps() {

	long double cps = 0.0;

	cps += process_cps(0, (GameSettings::cursor_cps * PlayerData::cursors));
	cps += process_cps(1, (GameSettings::grandma_cps * PlayerData::grandmas));
	cps += process_cps(2, (GameSettings::farm_cps * PlayerData::farms));
	cps += process_cps(3, (GameSettings::mine_cps * PlayerData::mines));
	cps += process_cps(4, (GameSettings::factory_cps * PlayerData::factories));
	cps += process_cps(5, (GameSettings::bank_cps * PlayerData::banks));
	cps += process_cps(6, (GameSettings::temple_cps * PlayerData::temples));
	cps += process_cps(7, (GameSettings::wizard_tower_cps * PlayerData::wizard_towers));
	cps += process_cps(8, (GameSettings::shipment_cps * PlayerData::shipments));
	cps += process_cps(9, (GameSettings::alchemy_lab_cps * PlayerData::alchemy_labs));
	cps += process_cps(10, (GameSettings::portal_cps * PlayerData::portals));
	cps += process_cps(11, (GameSettings::time_machine_cps * PlayerData::time_machines));
	cps += process_cps(12, (GameSettings::antimatter_condenser_cps * PlayerData::antimatter_condensers));
	cps += process_cps(13, (GameSettings::prism_cps * PlayerData::prisms));
	cps += process_cps(14, (GameSettings::chance_maker_cps * PlayerData::chance_makers));

	return cps;

}

long double CookieHandler::get_mouse_click() {

	return process_cps(0, PlayerData::click_amount);

}

long double CookieHandler::process_cps(int index, long double cps_multiplied) {

	long double value = cps_multiplied;

	switch (index) {

		case 0:

			value *= 2.0 * (long double) UpgradeHandler::has({ 0, 1, 2 });

			if (UpgradeHandler::has(3)) {

				value += .1 * PlayerData::getAmounts({ 0 });

			}

			if (UpgradeHandler::has(4)) {

				value += .5 * PlayerData::getAmounts({ 0 });

			}

			if (UpgradeHandler::has(5)) {

				value += 5 * PlayerData::getAmounts({ 0 });

			}

			if (UpgradeHandler::has(6)) {

				value += 50 * PlayerData::getAmounts({ 0 });

			}

			if (UpgradeHandler::has(43)) {

				value += 500 * PlayerData::getAmounts({ 0 });

			}

			if (UpgradeHandler::has(82)) {

				value += 5000 * PlayerData::getAmounts({ 0 });

			}

			if (UpgradeHandler::has(109)) {

				value += 50000 * PlayerData::getAmounts({ 0 });

			}

			if (UpgradeHandler::has(188)) {

				value += 500000 * PlayerData::getAmounts({ 0 });

			}

			if (UpgradeHandler::has(189)) {

				value += 5e6 * PlayerData::getAmounts({ 0 });

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 1:

			value *= 2.0 * (long double) UpgradeHandler::has({ 7, 8, 9, 44, 110, 192, 294, 307, 428, 480, 506, 57, 58, 59, 250, 251, 252, 60, 61, 62, 63, 103, 180, 415 });

			return (value < cps_multiplied ? cps_multiplied : value);

		case 2:

			value *= 2.0 * (long double) UpgradeHandler::has({ 10, 11, 12, 45, 11, 193, 295, 308, 429, 481, 507 });

			if (UpgradeHandler::has(57)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[2];

			}

			if (UpgradeHandler::has(369)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[11];

			}

			if (UpgradeHandler::has(370)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[6];

			}

			if (UpgradeHandler::has(380)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[7];

			}

			if (UpgradeHandler::has(385)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[10];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 3:

			value *= 2.0 * (long double) UpgradeHandler::has({ 16, 17, 18, 47, 113, 195, 296, 309, 430, 482, 508 });

			if (UpgradeHandler::has(58)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[3]) - ((*PlayerData::amounts[3]) % 2)) * .5;

			}

			if (UpgradeHandler::has(371)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[7];

			}

			if (UpgradeHandler::has(372)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[8];

			}

			if (UpgradeHandler::has(381)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[8];

			}

			if (UpgradeHandler::has(383)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[9];

			}

			if (UpgradeHandler::has(424)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[14];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 4:

			value *= 2.0 * (long double) UpgradeHandler::has({ 13, 14, 15, 46, 112, 194, 297, 310, 431, 483, 509 });

			if (UpgradeHandler::has(59)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[4]) - ((*PlayerData::amounts[4]) % 3)) / 3;

			}

			if (UpgradeHandler::has(373)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[12];

			}

			if (UpgradeHandler::has(374)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[11];

			}

			if (UpgradeHandler::has(376)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[5];

			}

			if (UpgradeHandler::has(382)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[8];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 5:

			value *= 2.0 * (long double) UpgradeHandler::has({ 232, 233, 234, 235, 236, 237, 298, 311, 432, 484, 510 });

			if (UpgradeHandler::has(250)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[5]) - ((*PlayerData::amounts[5]) % 4)) / 4;

			}

			if (UpgradeHandler::has(375)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[10];

			}

			if (UpgradeHandler::has(384)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[8];

			}

			if (UpgradeHandler::has(389)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[12];

			}

			if (UpgradeHandler::has(376)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[4];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 6:

			value *= 2.0 * (long double) UpgradeHandler::has({ 238, 239, 240, 241, 242, 243, 299, 312, 433, 485, 511 });

			if (UpgradeHandler::has(251)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[6]) - ((*PlayerData::amounts[6]) % 5)) / 5;

			}

			if (UpgradeHandler::has(377)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[10];

			}

			if (UpgradeHandler::has(378)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[12];

			}

			if (UpgradeHandler::has(392)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[13];

			}

			if (UpgradeHandler::has(370)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[2];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 7:

			value *= 2.0 * (long double) UpgradeHandler::has({ 244, 245, 256, 247, 248, 249, 300, 313, 434, 486, 512 });

			if (UpgradeHandler::has(252)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[7]) - ((*PlayerData::amounts[7]) % 6)) / 6;

			}

			if (UpgradeHandler::has(379)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[12];

			}

			if (UpgradeHandler::has(391)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[12];

			}

			if (UpgradeHandler::has(371)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[3];

			}

			if (UpgradeHandler::has(380)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[2];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 8:

			value *= 2.0 * (long double) UpgradeHandler::has({ 19, 20, 21, 48, 114, 196, 301, 314, 435, 487, 513 });

			if (UpgradeHandler::has(60)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[8]) - ((*PlayerData::amounts[8]) % 7)) / 7;

			}

			if (UpgradeHandler::has(387)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[11];

			}

			if (UpgradeHandler::has(372)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[3];

			}

			if (UpgradeHandler::has(381)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[3];

			}

			if (UpgradeHandler::has(382)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[4];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 9:

			value *= 2.0 * (long double) UpgradeHandler::has({ 22, 23, 24, 49, 115, 197, 302, 315, 436, 488, 514 });

			if (UpgradeHandler::has(61)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[9]) - ((*PlayerData::amounts[9]) % 8)) / 8;

			}

			if (UpgradeHandler::has(390)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[12];

			}

			if (UpgradeHandler::has(379)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[7];

			}

			if (UpgradeHandler::has(383)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[3];

			}

			if (UpgradeHandler::has(384)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[5];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 10:

			value *= 2.0 * (long double) UpgradeHandler::has({ 25, 26, 27, 50, 116, 198, 303, 316, 437, 489, 515 });

			if (UpgradeHandler::has(62)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[10]) - ((*PlayerData::amounts[10]) % 9)) / 9;

			}

			if (UpgradeHandler::has(386)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[13];

			}

			if (UpgradeHandler::has(375)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[5];

			}

			if (UpgradeHandler::has(377)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[6];

			}

			if (UpgradeHandler::has(384)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[2];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 11:

			value *= 2.0 * (long double) UpgradeHandler::has({ 28, 29, 30, 51, 117, 199, 304, 317, 438, 490, 516 });

			if (UpgradeHandler::has(63)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[11]) - ((*PlayerData::amounts[11]) % 10)) / 10;

			}

			if (UpgradeHandler::has(388)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[13];

			}

			if (UpgradeHandler::has(369)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[2];

			}

			if (UpgradeHandler::has(374)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[4];

			}

			if (UpgradeHandler::has(387)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[8];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 12:

			value *= 2.0 * (long double) UpgradeHandler::has({ 99, 100, 101, 102, 118, 200, 305, 318, 439, 491, 517 });

			if (UpgradeHandler::has(103)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[12]) - ((*PlayerData::amounts[12]) % 11)) / 11;

			}

			if (UpgradeHandler::has(443)) {

				value += value * 0.05 * (long double) *PlayerData::amounts[14];

			}

			if (UpgradeHandler::has(373)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[4];

			}

			if (UpgradeHandler::has(378)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[6];

			}

			if (UpgradeHandler::has(389)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[5];

			}

			if (UpgradeHandler::has(390)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[9];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 13:

			value *= 2.0 * (long double) UpgradeHandler::has({ 175, 176, 177, 178, 179, 201, 306, 319, 440, 492, 518 });

			if (UpgradeHandler::has(180)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[13]) - ((*PlayerData::amounts[13]) % 12)) / 12;

			}

			if (UpgradeHandler::has(386)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[10];

			}

			if (UpgradeHandler::has(388)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[11];

			}

			if (UpgradeHandler::has(391)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[7];

			}

			if (UpgradeHandler::has(392)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[6];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		case 14:

			value *= 2.0 * (long double) UpgradeHandler::has({ 416, 417, 418, 419, 420, 421, 422, 423, 441, 493, 519 });

			if (UpgradeHandler::has(415)) {

				value += value * 0.01 * (long double) ((*PlayerData::amounts[14]) - ((*PlayerData::amounts[14]) % 13)) / 13;

			}

			if (UpgradeHandler::has(424)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[3];

			}

			if (UpgradeHandler::has(443)) {

				value += value * 0.01 * (long double) *PlayerData::amounts[12];

			}

			return (value < cps_multiplied ? cps_multiplied : value);

		default:

			throw std::runtime_error("Wtf, Is You DUMB?");

	}

}