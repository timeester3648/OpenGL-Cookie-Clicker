#include "../../header/game/GameSaver.h"
#include "../../header/game/PlayerData.h"
#include "../../header/display/DisplayManager.h"
#include "../../header/game/GameSettings.h"
#include "../../header/handler/UpgradeHandler.h"
#include "../../header/handler/ShopHandler.h"

#include <EOUL\Save.h>
#include <GLFW\glfw3.h>
#include <thread>
#include <iostream>

using namespace EOUL::IO;

std::string GameSaver::path = "game_save.dat";

void GameSaver::load_game() {

	SaveFile file = SaveFile(path);
	std::vector<SaveData> save = file.readData();

	if (save.size() == 52) {

		memcpy(&PlayerData::click_amount, save[0].data.get(), save[0].size);
		memcpy(&PlayerData::cookies, save[1].data.get(), save[1].size);

		memcpy(&PlayerData::cursors, save[2].data.get(), save[2].size);
		memcpy(&PlayerData::grandmas, save[3].data.get(), save[3].size);
		memcpy(&PlayerData::farms, save[4].data.get(), save[4].size);
		memcpy(&PlayerData::mines, save[5].data.get(), save[5].size);
		memcpy(&PlayerData::factories, save[6].data.get(), save[6].size);
		memcpy(&PlayerData::banks, save[7].data.get(), save[7].size);
		memcpy(&PlayerData::temples, save[8].data.get(), save[8].size);
		memcpy(&PlayerData::wizard_towers, save[9].data.get(), save[9].size);
		memcpy(&PlayerData::shipments, save[10].data.get(), save[10].size);
		memcpy(&PlayerData::alchemy_labs, save[11].data.get(), save[11].size);
		memcpy(&PlayerData::portals, save[12].data.get(), save[12].size);
		memcpy(&PlayerData::time_machines, save[13].data.get(), save[13].size);
		memcpy(&PlayerData::antimatter_condensers, save[14].data.get(), save[14].size);
		memcpy(&PlayerData::prisms, save[15].data.get(), save[15].size);
		memcpy(&PlayerData::chance_makers, save[16].data.get(), save[16].size);

		memcpy(&GameSettings::cursor_cps, save[17].data.get(), save[17].size);
		memcpy(&GameSettings::grandma_cps, save[18].data.get(), save[18].size);
		memcpy(&GameSettings::farm_cps, save[19].data.get(), save[19].size);
		memcpy(&GameSettings::mine_cps, save[20].data.get(), save[20].size);
		memcpy(&GameSettings::factory_cps, save[21].data.get(), save[21].size);
		memcpy(&GameSettings::bank_cps, save[22].data.get(), save[22].size);
		memcpy(&GameSettings::temple_cps, save[23].data.get(), save[23].size);
		memcpy(&GameSettings::wizard_tower_cps, save[24].data.get(), save[24].size);
		memcpy(&GameSettings::shipment_cps, save[25].data.get(), save[25].size);
		memcpy(&GameSettings::alchemy_lab_cps, save[26].data.get(), save[26].size);
		memcpy(&GameSettings::portal_cps, save[27].data.get(), save[27].size);
		memcpy(&GameSettings::time_machine_cps, save[28].data.get(), save[28].size);
		memcpy(&GameSettings::antimatter_condenser_cps, save[29].data.get(), save[29].size);
		memcpy(&GameSettings::prism_cps, save[30].data.get(), save[30].size);
		memcpy(&GameSettings::chance_maker_cps, save[31].data.get(), save[31].size);

		memcpy(&PlayerData::cookies_produced_cursors, save[32].data.get(), save[32].size);
		memcpy(&PlayerData::cookies_produced_grandmas, save[33].data.get(), save[33].size);
		memcpy(&PlayerData::cookies_produced_farms, save[34].data.get(), save[34].size);
		memcpy(&PlayerData::cookies_produced_mines, save[35].data.get(), save[35].size);
		memcpy(&PlayerData::cookies_produced_factories, save[36].data.get(), save[36].size);
		memcpy(&PlayerData::cookies_produced_banks, save[37].data.get(), save[37].size);
		memcpy(&PlayerData::cookies_produced_temples, save[38].data.get(), save[38].size);
		memcpy(&PlayerData::cookies_produced_wizard_towers, save[39].data.get(), save[39].size);
		memcpy(&PlayerData::cookies_produced_shipments, save[40].data.get(), save[40].size);
		memcpy(&PlayerData::cookies_produced_alchemy_labs, save[41].data.get(), save[41].size);
		memcpy(&PlayerData::cookies_produced_portals, save[42].data.get(), save[42].size);
		memcpy(&PlayerData::cookies_produced_time_machines, save[43].data.get(), save[43].size);
		memcpy(&PlayerData::cookies_produced_antimatter_condensers, save[44].data.get(), save[44].size);
		memcpy(&PlayerData::cookies_produced_prisms, save[45].data.get(), save[45].size);
		memcpy(&PlayerData::cookies_produced_chance_makers, save[46].data.get(), save[46].size);

		memcpy(&GameSettings::short_numbers, save[47].data.get(), save[47].size);

		memcpy(&ShopHandler::registered, save[48].data.get(), save[48].size);
		memcpy(&ShopHandler::locked, save[49].data.get(), save[49].size);

		for (size_t offset = 0; offset < save[50].size; offset += sizeof(short)) {

			UpgradeHandler::unlocked_ids.push_back(*((short*) (save[50].data.get() + offset)));

		}

		memcpy(&PlayerData::cookies_produced, save[51].data.get(), save[51].size);

	}

}

void GameSaver::save_game() {

	SaveFile file = SaveFile(path);

	file.remove();

	file.save_queued((char*) &PlayerData::click_amount, sizeof(PlayerData::click_amount));
	file.save_queued((char*) &PlayerData::cookies, sizeof(PlayerData::cookies));

	file.save_queued((char*) &PlayerData::cursors, sizeof(PlayerData::cursors));
	file.save_queued((char*) &PlayerData::grandmas, sizeof(PlayerData::grandmas));
	file.save_queued((char*) &PlayerData::farms, sizeof(PlayerData::farms));
	file.save_queued((char*) &PlayerData::mines, sizeof(PlayerData::mines));
	file.save_queued((char*) &PlayerData::factories, sizeof(PlayerData::factories));
	file.save_queued((char*) &PlayerData::banks, sizeof(PlayerData::banks));
	file.save_queued((char*) &PlayerData::temples, sizeof(PlayerData::temples));
	file.save_queued((char*) &PlayerData::wizard_towers, sizeof(PlayerData::wizard_towers));
	file.save_queued((char*) &PlayerData::shipments, sizeof(PlayerData::shipments));
	file.save_queued((char*) &PlayerData::alchemy_labs, sizeof(PlayerData::alchemy_labs));
	file.save_queued((char*) &PlayerData::portals, sizeof(PlayerData::portals));
	file.save_queued((char*) &PlayerData::time_machines, sizeof(PlayerData::time_machines));
	file.save_queued((char*) &PlayerData::antimatter_condensers, sizeof(PlayerData::antimatter_condensers));
	file.save_queued((char*) &PlayerData::prisms, sizeof(PlayerData::prisms));
	file.save_queued((char*) &PlayerData::chance_makers, sizeof(PlayerData::chance_makers));

	file.save_queued((char*) &GameSettings::cursor_cps, sizeof(GameSettings::cursor_cps));
	file.save_queued((char*) &GameSettings::grandma_cps, sizeof(GameSettings::grandma_cps));
	file.save_queued((char*) &GameSettings::farm_cps, sizeof(GameSettings::farm_cps));
	file.save_queued((char*) &GameSettings::mine_cps, sizeof(GameSettings::mine_cps));
	file.save_queued((char*) &GameSettings::factory_cps, sizeof(GameSettings::factory_cps));
	file.save_queued((char*) &GameSettings::bank_cps, sizeof(GameSettings::bank_cps));
	file.save_queued((char*) &GameSettings::temple_cps, sizeof(GameSettings::temple_cps));
	file.save_queued((char*) &GameSettings::wizard_tower_cps, sizeof(GameSettings::wizard_tower_cps));
	file.save_queued((char*) &GameSettings::shipment_cps, sizeof(GameSettings::shipment_cps));
	file.save_queued((char*) &GameSettings::alchemy_lab_cps, sizeof(GameSettings::alchemy_lab_cps));
	file.save_queued((char*) &GameSettings::portal_cps, sizeof(GameSettings::portal_cps));
	file.save_queued((char*) &GameSettings::time_machine_cps, sizeof(GameSettings::time_machine_cps));
	file.save_queued((char*) &GameSettings::antimatter_condenser_cps, sizeof(GameSettings::antimatter_condenser_cps));
	file.save_queued((char*) &GameSettings::prism_cps, sizeof(GameSettings::prism_cps));
	file.save_queued((char*) &GameSettings::chance_maker_cps, sizeof(GameSettings::chance_maker_cps));

	file.save_queued((char*) &PlayerData::cookies_produced_cursors, sizeof(PlayerData::cookies_produced_cursors));
	file.save_queued((char*) &PlayerData::cookies_produced_grandmas, sizeof(PlayerData::cookies_produced_grandmas));
	file.save_queued((char*) &PlayerData::cookies_produced_farms, sizeof(PlayerData::cookies_produced_farms));
	file.save_queued((char*) &PlayerData::cookies_produced_mines, sizeof(PlayerData::cookies_produced_mines));
	file.save_queued((char*) &PlayerData::cookies_produced_factories, sizeof(PlayerData::cookies_produced_factories));
	file.save_queued((char*) &PlayerData::cookies_produced_banks, sizeof(PlayerData::cookies_produced_banks));
	file.save_queued((char*) &PlayerData::cookies_produced_temples, sizeof(PlayerData::cookies_produced_temples));
	file.save_queued((char*) &PlayerData::cookies_produced_wizard_towers, sizeof(PlayerData::cookies_produced_wizard_towers));
	file.save_queued((char*) &PlayerData::cookies_produced_shipments, sizeof(PlayerData::cookies_produced_shipments));
	file.save_queued((char*) &PlayerData::cookies_produced_alchemy_labs, sizeof(PlayerData::cookies_produced_alchemy_labs));
	file.save_queued((char*) &PlayerData::cookies_produced_portals, sizeof(PlayerData::cookies_produced_portals));
	file.save_queued((char*) &PlayerData::cookies_produced_time_machines, sizeof(PlayerData::cookies_produced_time_machines));
	file.save_queued((char*) &PlayerData::cookies_produced_antimatter_condensers, sizeof(PlayerData::cookies_produced_antimatter_condensers));
	file.save_queued((char*) &PlayerData::cookies_produced_prisms, sizeof(PlayerData::cookies_produced_prisms));
	file.save_queued((char*) &PlayerData::cookies_produced_chance_makers, sizeof(PlayerData::cookies_produced_chance_makers));

	file.save_queued((char*) &GameSettings::short_numbers, sizeof(GameSettings::short_numbers));

	file.save_queued((char*) &ShopHandler::registered, sizeof(ShopHandler::registered));
	file.save_queued((char*) &ShopHandler::locked, sizeof(ShopHandler::locked));

	short* upgrade_ids = new short[UpgradeHandler::unlocked_ids.size()];

	size_t i = 0;
	for (auto& id : UpgradeHandler::unlocked_ids) {

		upgrade_ids[i] = id;

		i++;

	}

	file.save_queued((char*) upgrade_ids, sizeof(short) * UpgradeHandler::unlocked_ids.size());
	file.save_queued((char*) &PlayerData::cookies_produced, sizeof(PlayerData::cookies_produced));

	file.save_all_queued();

	delete[] upgrade_ids;

}

void GameSaver::loop() {

	while (!glfwWindowShouldClose(DisplayManager::window)) {

		save_game();

		for (unsigned long long i = 0; i < 10 && !glfwWindowShouldClose(DisplayManager::window); i++) {

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

		}

	}

}