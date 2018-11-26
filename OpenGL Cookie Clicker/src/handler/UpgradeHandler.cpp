#include "../../header/handler/UpgradeHandler.h"
#include "../../header/handler/ShopHandler.h"
#include "../../header/handler/InteractableHandler.h"
#include "../../header/shop/Shop.h"
#include "../../header/game/PlayerData.h"
#include "../../header/Main.h"

#include <algorithm>

std::vector<UpgradeHandler::UpgradeData> UpgradeHandler::loaded_upgrades;
std::vector<Upgrade*> UpgradeHandler::upgrades;
std::vector<short> UpgradeHandler::unlocked_ids;
bool UpgradeHandler::expanded_upgrades = false;
bool UpgradeHandler::go_sort = false;

void UpgradeHandler::addUpgrade(short id, std::string name, std::string description, std::string lore, long double cost, Vec2 icon_offset) {

	if (upgrades.size() == 0) {

		Vec2 pos = { .84, .35f - .14f + .14f };

		upgrades.push_back(new Upgrade(id, pos - Vec2(.35f * .8f + .01875f * .5f - (.07f - .01875f * .5f) * 2.0f * .75f, -.01875f * 1.5f), cost, icon_offset, name, description, lore, (int) upgrades.size()));

	} else if (upgrades.size() < 5 || upgrades.size() % 5 != 0) {

		upgrades.push_back(new Upgrade(id, upgrades[upgrades.size() - 1]->position + Vec2(upgrades[upgrades.size() - 1]->icon->scale.x * 2, 0), cost, icon_offset, name, description, lore, (int) upgrades.size()));

	} else if (upgrades.size() % 5 == 0) {

		upgrades.push_back(new Upgrade(id, upgrades[upgrades.size() - 5]->position + Vec2(0, -upgrades[upgrades.size() - 5]->icon->scale.y * 2.0f), cost, icon_offset, name, description, lore, (int) upgrades.size()));

	}

}

void UpgradeHandler::deleteUpgrade(Upgrade* upgrade) {

	size_t i = 0;
	for (auto& up : UpgradeHandler::upgrades) {

		if (up == upgrade) {

			delete upgrade;

			upgrades.erase(upgrades.begin() + i);

		}

		i++;

	}

	shift();

}

void UpgradeHandler::sort(bool bypass) {

	if (!go_sort && !bypass) {

		return;

	} else {

		go_sort = false;

		for (size_t i = 0; i < upgrades.size(); i++) {

			upgrades[i]->need_sort = false;

		}

	}

	std::vector<Vec2> positions;

	for (size_t i = 0; i < upgrades.size(); i++) {

		positions.push_back(upgrades[i]->position);

	}

	std::sort(upgrades.begin(), upgrades.end(), [](Upgrade* a, Upgrade* b) {

		return a->cost < b->cost;

	});

	for (size_t i = 0; i < upgrades.size(); i++) {

		upgrades[i]->setPos(positions[i]);
		upgrades[i]->info_pane->setPos({ upgrades[i]->info_pane->position.x, upgrades[i]->position.y - upgrades[i]->scale.y });

		bool tmp = upgrades[i]->other_row;
		bool tmp_ = (i < 5);

		if (tmp && tmp_) {

			upgrades[i]->other_row = false;
			upgrades[i]->addOverlays();

		} else if (!tmp && !tmp_) {

			upgrades[i]->other_row = true;
			upgrades[i]->removeOverlays();

		}

	}

}

void UpgradeHandler::shift() {

	size_t j = 0;
	for (size_t i = 0; i < upgrades.size(); i++) {

		if (i == 0) {

			Vec2 pos = { .84, upgrades[0]->position.y };

			upgrades[i]->setPos(pos - Vec2(.35f * .8f + .01875f * .5f - (.07f - .01875f * .5f) * 2.0f * .75f, 0.0f));

		} else if (j != 5) {

			upgrades[i]->setPos(upgrades[i - 1]->position + Vec2(upgrades[i - 1]->icon->scale.x * 2, 0));
			
		} else if (j == 5) {

			upgrades[i]->setPos(upgrades[i - 5]->position + Vec2(0, -upgrades[i - 5]->icon->scale.y * 2.0f));

			j = 0;

		}

		upgrades[i]->info_pane->setPos({ upgrades[i]->info_pane->position.x, upgrades[i]->position.y - upgrades[i]->scale.y });

		if (i < 5) {

			upgrades[i]->other_row = false;

		} else {

			upgrades[i]->other_row = true;

		}

		j++;

	}

}

void UpgradeHandler::update() {

	for (auto& upgrade : upgrades) {

		if (upgrade->need_sort) {

			go_sort = true;

			break;

		}

	}

	sort();

	int i = 0;
	for (auto& upgrade : upgrades) {

		upgrade->index = i;

		upgrade->update();

		i++;

	}

	static bool expanded = false;

	if (expanded_upgrades && upgrades.size() > 5 && !expanded) {

		// y panel_2: .35f + .07f + .02f - .14f
		// y highest tile: .35f - .14f
		// first row upgrades: .35f - .14f + .14f - -.01875f * 1.5f

		shift();

		expanded = true;

		panel_2->position.y = upgrades[upgrades.size() - 1]->position.y - abs((.35f - .14f + .14f - -.01875f * 1.5f) - (.35f + .07f + .02f - .14f));
		Shop::tiles[0]->setPos({ Shop::tiles[0]->position.x, panel_2->position.y - abs((.35f - .14f) - (.35f + .07f + .02f - .14f)) });

		for (size_t i = 1; i < Shop::tiles.size(); i++) {

			Shop::tiles[i]->setPos({ Shop::tiles[i]->position.x, Shop::tiles[0]->position.y - i * .14f });

		}

	} else if (upgrades.size() <= 5 && upgrades.size() > 0 || !expanded_upgrades && expanded) {

		shift();

		expanded = false;
		
		panel_2->position.y = upgrades[0]->position.y - abs((.35f - .14f + .14f - -.01875f * 1.5f) - (.35f + .07f + .02f - .14f));
		Shop::tiles[0]->setPos({ Shop::tiles[0]->position.x, panel_2->position.y - abs((.35f - .14f) - (.35f + .07f + .02f - .14f)) });

		for (size_t i = 1; i < Shop::tiles.size(); i++) {

			Shop::tiles[i]->setPos({ Shop::tiles[i]->position.x, Shop::tiles[0]->position.y - i * .14f });

		}

	}

}

void UpgradeHandler::update_upgrades() {

	for (auto& data : loaded_upgrades) {

		bool can = true;
		for (auto& upgrade : upgrades) {

			if (upgrade->id == data.id) {

				can = false;

				break;

			}

		}

		for (auto& id : unlocked_ids) {

			if (id == data.id) {

				can = false;

				break;

			}

		}

		if (can) {

			for (auto& requirement : data.unlock_requirements) {

				if (*PlayerData::amounts[requirement.first] < requirement.second) {

					can = false;

					break;

				}

			}

		}

		if (can) {

			addUpgrade(data.id, data.name, data.description.name, data.description.lore, data.cost, data.offset);

		}

	}

	sort(true);

}

unsigned long long UpgradeHandler::has(std::vector<short> ids) {

	unsigned long long tmp = 0;

	for (auto& id : ids) {

		if (has(id)) {

			tmp++;

		}

	}

	return tmp;

}

bool UpgradeHandler::has(short id) {

	for (auto& id_ : unlocked_ids) {

		if (id_ == id) {

			return true;

		}

	}

	return false;

}